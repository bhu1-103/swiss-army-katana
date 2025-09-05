#!/usr/bin/bash

MAX_LEN=20

title=$(mpc current --format "%title% - %artist%")
if [ -z "$title" ]; then
  title="Stopped"
fi

# Scrolling Logic
if [ ${#title} -gt $MAX_LEN ]; then
    pos=$(( $(date +%s) % ${#title} ))
    scrolling_title=$(printf "% -20s" "${title:pos:20}")
else
    scrolling_title=$title
fi

# Escape JSON special characters
scrolling_title=$(echo "$scrolling_title" | sed 's/"/\"/g' | sed 's/\\/\\\\/g')

echo "{\"text\": \"$scrolling_title\", \"tooltip\": \"MPD\"}"
