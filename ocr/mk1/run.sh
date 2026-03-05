#!/usr/bin/zsh
#
export TESSDATA_PREFIX=~/tts
IMG=$HOME/.local/cache/tts-screenshot-2.png

dir=$HOME/.local/cache/
cd "$dir"
rm tts-screenshot*
#scrot --select --freeze --line mode=edge tts-screenshot.png
maim -s tts-screenshot-1.png
magick tts-screenshot-1.png -colorspace Gray -resize 200% -level 60%,100% "$IMG"
TEXT=$(tesseract "$IMG" stdout -l jpn+jpn_vert --psm 6 | tr -d ' \n')
dunstify "TTS Processing... $TEXT" -i "$IMG" -r 1919
echo -n "$TEXT" | xclip -selection clipboard

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
