#!/usr/bin/zsh

wl-paste > 1.png; tesseract 1.png output -l jpn; tr -d ' ' < output.txt > output_clean.txt; python kanji-simplify.py

rm 1.png
rm output.txt
rm output_clean.txt
