#!/usr/bin/env zsh
set -euo pipefail

if [[ -z "${1:-}" ]]; then
  echo "Usage: $0 <audio-file>"
  exit 1
fi

INPUT="$1"
BASENAME="${INPUT:t:r}"
OUTDIR="/run/media/bhu1/disk/MUSIC"
OUTPUT="$OUTDIR/$BASENAME.mp3"

ffmpeg -y -i "$INPUT" \
  -map 0:a \
  -map "0:v?" \
  -c:a libmp3lame -q:a 2 \
  -c:v copy \
  -id3v2_version 3 \
  "$OUTPUT"

echo "Created: $OUTPUT"
