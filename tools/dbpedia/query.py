import ollama
import httpx
import json

DBPEDIA_SPARQL_ENDPOINT = "https://dbpedia.org/sparql"

class Planner:
    def __init__(self, model="qwen2.5:0.5b"):
        self.model = model

    def create_plan(self, question):
        prompt = f"""
You are a strictly logical task planner for a DBpedia QA system.
Break down the user's question into a JSON array of steps.

CRITICAL RULES:
1. ONLY use words that appear in the USER QUESTION. 
2. DO NOT copy words, entities, or relations from the EXAMPLES.
3. Keep the plan to 2 or 3 steps maximum.

AVAILABLE ACTIONS:
- "find_entity": Use this first to find the main subject (target).
- "get_property": Use this to find a specific trait or relationship.

EXAMPLES (DO NOT COPY THESE):
Q: "Who wrote the book 1984?"
[
    {{"action": "find_entity", "target": "1984"}},
    {{"action": "get_property", "property": "author"}}
]

Q: "What is the population of Canada?"
[
    {{"action": "find_entity", "target": "Canada"}},
    {{"action": "get_property", "property": "population"}}
]

Q: "Who is the mayor of Berlin?"
[
    {{"action": "find_entity", "target": "Berlin"}},
    {{"action": "get_property", "property": "mayor"}}
]

USER QUESTION: "{question}"
OUTPUT ONLY VALID JSON:
"""
        response = ollama.generate(model=self.model, prompt=prompt)
        text = response['response'].strip()
        if "```json" in text:
            text = text.split("```json")[1].split("```")[0].strip()
        elif "```" in text:
            text = text.split("```")[1].split("```")[0].strip()
        
        try:
            plan = json.loads(text)
            print(f"DEBUG: Generated Plan: {json.dumps(plan, indent=2)}")
            return plan
        except:
            print(f"DEBUG: Planner failed to generate JSON. Raw: {text}")
            return []

class Worker:
    def __init__(self, model="qwen2.5:0.5b"):
        self.model = model

    def execute_sparql(self, query):
        params = {"query": query, "format": "application/sparql-results+json"}
        try:
            with httpx.Client() as client:
                resp = client.get(DBPEDIA_SPARQL_ENDPOINT, params=params, timeout=20.0)
                return resp.json()
        except Exception as e:
            print(f"DEBUG: SPARQL Error: {e}")
            return None

    def search_dbpedia(self, target):
        query = f"""
        PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
        SELECT ?s WHERE {{
          ?s rdfs:label "{target}"@en .
          FILTER (!STRSTARTS(STR(?s), "http://dbpedia.org/resource/Category:"))
          FILTER (!isLiteral(?s))
        }} LIMIT 1"""
        print(f"DEBUG: Searching for entity '{target}'...")
        res = self.execute_sparql(query)
        try:
            uri = f"<{res['results']['bindings'][0]['s']['value']}>"
            print(f"DEBUG: Found entity: {uri}")
            return uri
        except:
            print(f"DEBUG: Entity '{target}' not found.")
            return None

    def query_property(self, entity, prop, original_question):
        print(f"DEBUG: Querying property '{prop}' for entity {entity}...")
        
        # 1. Discover actual, semantic properties (Filter noise)
        disc_query = f"""
        SELECT DISTINCT ?p WHERE {{ 
            {entity} ?p ?o . 
            FILTER(STRSTARTS(STR(?p), 'http://dbpedia.org/ontology/') || 
                   STRSTARTS(STR(?p), 'http://dbpedia.org/property/'))
            FILTER(!CONTAINS(STR(?p), "wikiPage"))
        }}
        """
        res = self.execute_sparql(disc_query)
        if not res: 
            print("DEBUG: Property discovery failed (no results).")
            return None
        
        props = [b['p']['value'] for b in res['results']['bindings']]
        short_names = [p.split('/')[-1].split('#')[-1] for p in props]
        print(f"DEBUG: Discovered {len(props)} semantic properties.")
        
        # 2. Match with LLM (Hardened Prompt)
        prompt = f"""
Task: Pick the ONE best property from the Available List to answer the Question.

Question: "{original_question}"
Target Concept: "{prop}"

Available List:
{", ".join(short_names[:60])}

CRITICAL RULES:
1. You must output EXACTLY ONE property name from the list.
2. Do not include commas, explanations, or multiple choices.
3. If nothing matches, output exactly: None

Match:"""
        match_resp = ollama.generate(model=self.model, prompt=prompt)['response'].strip().split('\n')[0].strip()
        print(f"DEBUG: LLM chose match: '{match_resp}'")
        
        if match_resp.lower() == "none":
            return None

        matched_uri = None
        for p in props:
            if p.endswith(f"/{match_resp}") or p.endswith(f"#{match_resp}"):
                matched_uri = p
                break
        
        if not matched_uri: 
            print(f"DEBUG: Could not resolve '{match_resp}' to a full URI.")
            return None
        
        print(f"DEBUG: Resolved to URI: <{matched_uri}>")
        
        # 3. Execute final query
        final_q = f"SELECT ?o WHERE {{ {entity} <{matched_uri}> ?o . }} LIMIT 1"
        print(f"DEBUG: Final SPARQL: {final_q}")
        final_res = self.execute_sparql(final_q)
        try:
            val = final_res['results']['bindings'][0]['o']
            result = f"<{val['value']}>" if val['type'] == 'uri' else val['value']
            print(f"DEBUG: Query result: {result}")
            return result
        except:
            print("DEBUG: Final query returned no bindings.")
            return None

class MultiHopAgent:
    def __init__(self):
        self.planner = Planner()
        self.worker = Worker()

    def answer_question(self, user_question):
        print(f"\n=== Question: {user_question} ===")
        task_queue = self.planner.create_plan(user_question)
        if not task_queue: return "Failed to create plan."
        
        print(f"DEBUG: Plan has {len(task_queue)} steps.")
        return self._execute_step(task_queue, current_subject=None, original_question=user_question)

    def _execute_step(self, task_queue, current_subject, original_question):
        if not task_queue:
            return current_subject

        current_task = task_queue.pop(0)
        action = current_task.get("action")
        
        print(f"DEBUG: Step -> Action: {action} | Subject: {current_subject}")

        if action == "find_entity":
            new_subject = self.worker.search_dbpedia(current_task["target"])
        elif action == "get_property":
            new_subject = self.worker.query_property(current_subject, current_task["property"], original_question)
        else:
            return f"Unknown action: {action}"

        if not new_subject:
            return f"Chain broken at {action}."

        return self._execute_step(task_queue, current_subject=new_subject, original_question=original_question)

if __name__ == "__main__":
    import sys
    q = " ".join(sys.argv[1:]) if len(sys.argv) > 1 else "What is the capital of France?"
    print(f"FINAL ANSWER: {MultiHopAgent().answer_question(q)}")
