#!/bin/bash

STATE_FILE="/tmp/waybar_player_mode"
PLAYER_MODE=$(cat "$STATE_FILE" 2>/dev/null)

if [ -z "$PLAYER_MODE" ]; then
    PLAYER_MODE="mpd"
fi

PLAYER_STATUS="Stopped"
ICON_PAUSE=""
ICON_PLAY=""
ICON_STOP=""

if [ "$PLAYER_MODE" = "mpris" ]; then
    STATUS_OUTPUT=$(playerctl status 2>/dev/null)
    if [[ "$STATUS_OUTPUT" == "Playing" || "$STATUS_OUTPUT" == "Paused" ]]; then
        PLAYER_STATUS=$STATUS_OUTPUT
    fi
elif [ "$PLAYER_MODE" = "mpd" ]; then
    if command -v mpc &> /dev/null; then
        if mpc status | grep -q "playing"; then
            PLAYER_STATUS="Playing"
        elif mpc status | grep -q "paused"; then
            PLAYER_STATUS="Paused"
        fi
    fi
fi

if [ "$PLAYER_STATUS" = "Playing" ]; then
    ICON=$ICON_PLAY
elif [ "$PLAYER_STATUS" = "Paused" ]; then
    ICON=$ICON_PAUSE
else
    ICON=$ICON_STOP
fi

printf '{"text": " %s ", "tooltip": "Active Player: %s (%s)"}\n' "$ICON" "$PLAYER_MODE" "$PLAYER_STATUS"
