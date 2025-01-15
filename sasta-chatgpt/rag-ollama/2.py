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
        page = next(iter(data["query"]["pages"].values()))  # Get the first page
        if "extract" in page:
            return page["extract"]
        else:
            return "Page not found."
    else:
        return "An error occurred while fetching the page."

# Example usage:
wiki_full_content = get_wikipedia_full_content("Artificial intelligence")
print(wiki_full_content)
