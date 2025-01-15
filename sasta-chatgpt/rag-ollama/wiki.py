import requests

def get_wikipedia_full_content(title):
    url = f"https://en.wikipedia.org/w/api.php"
    params = {
        "action": "query",
        "prop": "extracts",
        "explaintext": True,
        "titles": title,
        "format": "json"
    }
    response = requests.get(url, params=params)
    if response.status_code == 200:
        data = response.json()
        page = next(iter(data["query"]["pages"].values()))
        if "extract" in page:
            return page["extract"]
        else:
            return "Page not found."
    else:
        return "An error occurred while fetching the page."

wiki_content = get_wikipedia_full_content("2024_United_States_drone_sightings")
print(wiki_content)

def chunk_text(text, max_tokens=512):
    words = text.split()
    chunks = []
    current_chunk = []

    for word in words:
        current_chunk.append(word)
        if len(current_chunk) >= max_tokens:
            chunks.append(" ".join(current_chunk))
            current_chunk = []

    if current_chunk:
        chunks.append(" ".join(current_chunk))

    return chunks

chunks = chunk_text(wiki_content, max_tokens=512)
print(chunks)

from sentence_transformers import SentenceTransformer, util

model = SentenceTransformer('all-MiniLM-L6-v2')

chunk_embeddings = model.encode(chunks, convert_to_tensor=True)
question = "tell me about drone sightings in new jersey in 2024, based on the context provided."
question_embedding = model.encode(question, convert_to_tensor=True)

scores = util.cos_sim(question_embedding, chunk_embeddings)[0]
top_k = min(3, len(scores))  # Use the smaller of 3 or the number of scores
top_chunks = [chunks[i] for i in scores.topk(top_k).indices]  # Retrieve only available chunks
#top_chunks = [chunks[i] for i in scores.topk(3).indices]  # Top 3 chunks

print(top_chunks)
def construct_prompt(chunks, question):
    context = "\n\n".join(chunks)
    return f"Context:\n{context}\n\nQuestion: {question}\nAnswer:"

prompt = construct_prompt(top_chunks, question)
print(prompt)

import requests
import json

def query_mistral(prompt):
    url = "http://localhost:11434/api/generate"
    payload = {
        "model": "mistral",
        "prompt": prompt,
        "stream": False
    }
    headers = {"Content-Type": "application/json"}
    
    response = requests.post(url, data=json.dumps(payload), headers=headers)
    return response.json().get("response", "No response")

response = query_mistral(prompt)
print(response)


