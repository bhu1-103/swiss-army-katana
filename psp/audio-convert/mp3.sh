#!/usr/bin/env bash

set -euo pipefail

SRC="$HOME/hdd/flacs"
MP3_DST="$HOME/hdd/mp3"

echo "Starting conversion..."
echo

find "$SRC" -type f -iname "*.flac" -exec bash -c '

file="$1"

rel="${file#$SRC/}"

mp3_out="$MP3_DST/${rel%.flac}.mp3"

mkdir -p "$(dirname "$mp3_out")"

echo "Processing:"
echo "$rel"
echo

if [[ ! -f "$mp3_out" ]]; then

    echo " -> MP3 V2"

    ffmpeg -y \
        -hide_banner \
        -loglevel error \
        -i "$file" \
        -map_metadata 0 \
        -map 0:a \
        -map 0:v? \
        -c:v copy \
        -c:a libmp3lame \
        -q:a 2 \
        -id3v2_version 3 \
        "$mp3_out"

else
    echo " -> MP3 exists, skipping"
fi

' _ {} \;

echo "All conversions complete."
