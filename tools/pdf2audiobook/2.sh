#!/usr/bin/zsh

directory="extracted-pages"
for file in $directory/*.txt
do
    if grep -qE '\b(Scene|Chapter)\b' "$file"; then
        echo "Processing file: $file"
        perl -i -pe 's/(\b(Scene|Chapter)\b.*)(?!\.)$/\1./' "$file"
        echo "Finished processing $file."
    else
        echo "No 'Scene' or 'Chapter' found in $file. Skipping."
    fi
done
