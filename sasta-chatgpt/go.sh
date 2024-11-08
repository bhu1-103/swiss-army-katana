#!/bin/bash

INPUT_PROMPT=$1

curl -s http://localhost:11434/api/generate -d '{
  "model": "mistral",
  "prompt": "'"$INPUT_PROMPT"'",
  "stream": false
}' | jq -r '.response' | fold -w 50

