#!/bin/bash
STATE_FILE="/tmp/waybar_player_mode"

if [ ! -f "$STATE_FILE" ]; then
    echo "mpd" > "$STATE_FILE"
fi

CURRENT_STATE=$(cat "$STATE_FILE")

if [ "$CURRENT_STATE" = "mpd" ]; then
  echo "mpris" > "$STATE_FILE"
else
  echo "mpd" > "$STATE_FILE"
fi

# Send a signal to Waybar to refresh custom modules (SIGRTMIN+8)
pkill -RTMIN+8 waybar
