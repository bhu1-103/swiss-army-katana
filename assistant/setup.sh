#!/bin/sh

pip install vosk-transcriber
wget https://alphacephei.com/vosk/models/vosk-model-small-en-us-0.15.zip
unzip vosk-model-small-en-us-0.15.zip
wget https://github.com/bhu1-103/swiss-army-katana/blob/main/assistant/assistant.sh
