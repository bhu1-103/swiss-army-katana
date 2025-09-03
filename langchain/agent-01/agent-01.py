import requests
from bs4 import BeautifulSoup
from langchain_community.chat_models.ollama import ChatOllama
from langchain_community.embeddings import OllamaEmbeddings
from langchain_community.vectorstores import FAISS
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.chains import RetrievalQA
from langchain.schema import Document

llm = ChatOllama(model="gemma3n:e2b", verbose=True)
embeddings = OllamaEmbeddings(model="nomic-embed-text")

url = "https://en.wikipedia.org/wiki/Persona_5"
response = requests.get(url)
soup = BeautifulSoup(response.text, "html.parser")
paragraphs = soup.find_all("p")
text = "\n".join([p.get_text() for p in paragraphs if p.get_text().strip() != ""])
docs = [Document(page_content=text, metadata={"source": url})]

text_splitter = RecursiveCharacterTextSplitter(chunk_size=500, chunk_overlap=50)
chunks = text_splitter.split_documents(docs)

vectorstore = FAISS.from_documents(chunks, embeddings)
retriever = vectorstore.as_retriever(search_kwargs={"k": 3})

qa_chain = RetrievalQA.from_chain_type(
    llm=llm,
    chain_type="stuff",
    retriever=retriever
)

query = "What is the main theme of Persona 5?"
answer = qa_chain.run(query)
print(answer)
