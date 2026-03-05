#!/usr/bin/env bash

DIR="/tmp/mangaocr"

mkdir -p "$DIR"
rm -f "$DIR"/*

echo "Starting MangaOCR daemon..."
echo "Watching $DIR"

manga_ocr -r "$DIR" -w clipboard
