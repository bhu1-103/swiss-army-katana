#!/usr/bin/zsh

for file in ../chapters/*.txt
do
    ./kokoro-tts $file --voice "af_nicole:100,af_kore:20"
done
