#!/usr/bin/bash

STATE_FILE="/tmp/waybar_player_mode"
if [ ! -f "$STATE_FILE" ] || [ "$(cat "$STATE_FILE")" != "mpd" ]; then
    echo "{}"
    exit
fi

MAX_LEN=20

title=$(mpc current --format "%title% - %artist%")
if [ -z "$title" ]; then
  title="Stopped"
fi

if [ ${#title} -gt $MAX_LEN ]; then
    pos=$(( $(date +%s) % ${#title} ))
    scrolling_title=$(printf "% -20s" "${title:pos:20}")
else
    scrolling_title=$title
fi

scrolling_title=$(echo "$scrolling_title" | sed 's/"/\\"/g' | sed 's/\\/\\\\/g')

echo "{\"text\": \"$scrolling_title\", \"tooltip\": \"MPD\"}"
