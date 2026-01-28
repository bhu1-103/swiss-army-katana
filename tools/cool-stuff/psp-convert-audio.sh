#!/usr/bin/env zsh
set -euo pipefail

if [[ $# -ne 2 ]]; then
  echo "Usage: $0 <input-audio> <output-mp3>"
  exit 1
fi

INPUT="$1"
OUTPUT="$2"

lame -V2 --vbr-new --add-id3v2 "$INPUT" "$OUTPUT"

echo "Created: $OUTPUT"
