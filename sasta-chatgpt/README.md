# Sasta-ChatGPT

This project is a simple Retrieval-Augmented Generation (RAG) tool that uses a local Large Language Model (LLM) to answer questions about a specific knowledge base.

## How It Works

1.  **Data Retrieval:** The `wiki.py` script fetches content from a source (e.g., a Wikipedia article) and splits it into manageable chunks.
2.  **Embedding:** Each chunk is converted into a vector embedding using the `sentence-transformers` library (`all-MiniLM-L6-v2` model).
3.  **Context Matching:** When a user asks a question, the question is also embedded, and a cosine similarity search is performed to find the most relevant text chunks from the knowledge base.
4.  **Prompt Generation:** The most relevant chunks are combined with the user's question into a single prompt.
5.  **Answer Generation:** This final prompt is sent to a locally running LLM (in this case, `mistral` via Ollama) to generate a final, context-aware answer.

The `rest-api` directory contains a simple PHP-based web interface for interacting with the model.