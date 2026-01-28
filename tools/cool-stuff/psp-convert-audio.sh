#!/usr/bin/env zsh
set -euo pipefail

if [[ -z "${1:-}" ]]; then
  echo "Usage: $0 <audio-file>"
  exit 1
fi

INPUT="$1"
DIR="${INPUT:h}"
BASE="${INPUT:t:r}"
OUTPUT="$DIR/$BASE.mp3"

lame -V2 --vbr-new --add-id3v2 "$INPUT" "$OUTPUT"

echo "Converted: $OUTPUT"
