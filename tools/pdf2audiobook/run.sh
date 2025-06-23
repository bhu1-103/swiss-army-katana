#!/usr/bin/zsh

echo "[1] Extracting pages..."
./scripts/extract_pages.sh || exit 1

echo "[2] Cleaning headers/footers..."
./scripts/cleanup_headers.sh || exit 1

echo "[3] Splitting into chapters..."
python3 scripts/chapters.py || exit 1

echo "[4] Generating audio..."
./scripts/tts_generate.sh || exit 1

echo "[5] Compressing audio..."
./scripts/compress_audio.sh || exit 1

echo "Done! All output in 'final/'"
