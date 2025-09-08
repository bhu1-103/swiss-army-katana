#!/usr/bin/bash

STATE_FILE="/tmp/waybar_player_mode"
if [ "$(cat "$STATE_FILE" 2>/dev/null)" != "mpris" ]; then
    echo "{}"
    exit
fi

MAX_LEN=20

PLAYER_STATUS=$(playerctl status 2>/dev/null)
if [ $? -ne 0 ] || [ "$PLAYER_STATUS" = "Stopped" ]; then
  echo '{"text": "", "tooltip": "No player is active"}'
  exit
fi

title=$(playerctl metadata --format "{{ title }} - {{ artist }}" 2>/dev/null)

if [ -z "$title" ]; then
  echo '{"text": "", "tooltip": "Playing"}'
  exit
fi

if [ "${#title}" -lt $MAX_LEN ]; then
    printf '{"text": "% -*s", "tooltip": "%s"}\n' "$MAX_LEN" "$title" "$title"
    exit
fi

long_title="$title   -   $title"
offset=$(( $(date +%s) % (${#title} + 7) ))
scrolling_title="${long_title:offset:MAX_LEN}"

printf '{"text": "%s", "tooltip": "%s"}\n' "$scrolling_title" "$title"
