#!/bin/bash

input="$1"
output="${1%.*}-re-encoded.mp4"
ffmpeg -i "$input" -c:v libx265 -crf 28 -preset slow -c:a aac -b:a 128k "$output"
echo "Re-encoded file saved as: $output"
