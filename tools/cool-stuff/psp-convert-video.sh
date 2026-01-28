#!/usr/bin/env zsh

set -euo pipefail

if [[ -z "${1:-}" ]]; then
  echo "Usage: $0 <video-file>"
  exit 1
fi

INPUT="$1"
BASENAME="${INPUT:t}"
NAME="${BASENAME:r}"

PSP_DIR="./MP_ROOT/100MNV01"
mkdir -p "$PSP_DIR"

# Find next PSP-style filename
count=$(ls "$PSP_DIR"/M4V*.MP4(N) | wc -l)
printf -v PSP_NAME "M4V%05d.MP4" $((count + 1))

OUTPUT="$PSP_DIR/$PSP_NAME"

ffmpeg -i "$INPUT" \
-vf "scale=480:272:force_original_aspect_ratio=decrease,pad=480:272:(ow-iw)/2:(oh-ih)/2" \
-c:v libx264 \
-profile:v baseline \
-level 3.0 \
-pix_fmt yuv420p \
-x264-params "ref=2:bframes=0:cabac=0" \
-b:v 1400k \
-maxrate 1500k \
-bufsize 2M \
-movflags +faststart \
-c:a aac \
-b:a 160k \
-ar 44100 \
-ac 2 \
"$OUTPUT"

echo "Created PSP video: $OUTPUT"
