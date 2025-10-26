#!/usr/bin/zsh

selected_file=$(find library/lyrics -type f -not -name "*-hiragana.txt" | fzf)

echo "$selected_file" | python ../kanji-simplify.py

base_name="${selected_file%.*}"
wrong_hiragana_path="${base_name}-hiragana.txt"

original_basename=$(basename "$selected_file" .txt)
hiragana_filename="${original_basename}-hiragana.txt"
correct_hiragana_path="library/lyrics-hiragana/${hiragana_filename}"

if [ -f "$wrong_hiragana_path" ]; then
    mkdir -p library/lyrics-hiragana
    mv "$wrong_hiragana_path" "$correct_hiragana_path"
fi

if [ -f "$correct_hiragana_path" ]; then
    cp "$correct_hiragana_path" .
fi

song="$(ls *.txt | grep -v "config")"
./display $song
rm $song
