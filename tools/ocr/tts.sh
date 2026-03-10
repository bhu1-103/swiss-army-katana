#!/usr/bin/zsh

TMP=$(mktemp)

xclip -selection clipboard -o > "$TMP" 2>/dev/null

sleep 0.2
xdotool key ctrl+c

TEXT=$(xclip -o -selection clipboard)

[ -z "$TEXT" ] && exit 0

curl -s -X POST "http://127.0.0.1:50021/audio_query" \
  --get \
  --data-urlencode "speaker=66" \
  --data-urlencode "text=$TEXT" \
  > query.json

jq '.speedScale=0.95 | .intonationScale=1.3 | .pitchScale=0.0' query.json > query2.json

curl -s -X POST "http://127.0.0.1:50021/synthesis?speaker=66" \
  -H "Content-Type: application/json" \
  -d @query2.json \
  > voice.wav

mpv voice.wav

xclip -selection clipboard < "$TMP"
