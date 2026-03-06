#!/usr/bin/env zsh

DIR="/tmp/mangaocr"

mkdir -p "$DIR"
rm -f "$DIR"/*

echo "Starting MangaOCR daemon..."
echo "Watching $DIR"

source /home/bhu1/games/ocr-gpu/bin/activate
manga_ocr -r "$DIR" -w clipboard
