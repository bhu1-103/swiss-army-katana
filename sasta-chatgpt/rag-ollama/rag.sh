#!/usr/bin/zsh

cd dev/projects/rag-ollama
a=$(date)
python3.12 wiki.py
b=$(date)
echo $a
echo $b
