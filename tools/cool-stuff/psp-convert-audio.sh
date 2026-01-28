#!/usr/bin/env zsh

set -euo pipefail

if [[ -z "${1:-}" ]]; then
  echo "Usage: $0 <audio-file>"
  exit 1
fi

INPUT="$1"
BASENAME="${INPUT:t}"
NAME="${BASENAME:r}"

OUTDIR="./PSP_MUSIC"
mkdir -p "$OUTDIR"

OUTPUT="$OUTDIR/$NAME.mp3"

ffmpeg -y -i "$INPUT" -vn -ac 2 -ar 44100 -f wav /tmp/psp_audio_temp.wav
lame -V2 /tmp/psp_audio_temp.wav "$OUTPUT"
rm /tmp/psp_audio_temp.wav

echo "Created PSP audio: $OUTPUT"
