#!/usr/bin/env bash

DIR="/tmp/mangaocr"
IMG="$DIR/shot-$(date +%s%N).png"

mkdir -p "$DIR"

maim -s "$IMG"

sleep 0.35

TEXT=$(xclip -o -selection clipboard)

[ -z "$TEXT" ] && exit 0

dunstify "TTS Processing..." "$TEXT" -i "$IMG" -r 1919

curl -s -X POST "http://127.0.0.1:50021/audio_query" \
  --get \
  --data-urlencode "speaker=66" \
  --data-urlencode "text=$TEXT" \
  > query.json

jq '.speedScale=0.95 | .intonationScale=1.3 | .pitchScale=-0.08' query.json > query2.json

curl -s -X POST "http://127.0.0.1:50021/synthesis?speaker=4" \
  -H "Content-Type: application/json" \
  -d @query2.json \
  > voice.wav

mpv voice.wav
