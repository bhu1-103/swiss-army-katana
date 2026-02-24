#!/bin/bash

export LC_ALL=en_US.UTF-8

STATE_FILE="/tmp/polybar-player-backend"
SCROLL_FILE="/tmp/polybar-player-scroll"

ICON_PREV=""
ICON_NEXT=""
ICON_PLAY=""
ICON_PAUSE="󰏦"
ICON_MPD="󰔢"
ICON_MPRIS="󰨚"

MAX_LENGTH=20
SCROLL_SPEED=1
PADDING="    "

# -------------------------------
# Normalize width:
# Pad single-byte (ASCII) chars
# so they visually match CJK width
# -------------------------------
normalize_width() {
    local input="$1"
    local output=""
    local char

    while IFS= read -r -n1 char; do
        if [ "${#char}" -eq 1 ]; then
            output+="$char "
        else
            output+="$char"
        fi
    done <<< "$input"

    echo "$output"
}

# -------------------------------

[ -f "$STATE_FILE" ] || echo "mpd" > "$STATE_FILE"
BACKEND=$(cat "$STATE_FILE")

get_mpd_status() {
    mpc status 2>/dev/null | sed -n '2p'
}

get_mpd_title() {
    mpc current --format="%title%" 2>/dev/null
}

get_mpris_status() {
    playerctl status 2>/dev/null
}

get_mpris_title() {
    playerctl metadata title 2>/dev/null
}

cmd_play_pause() {
    if [ "$BACKEND" = "mpd" ]; then
        mpc toggle
    else
        playerctl play-pause
    fi
}

cmd_next() {
    if [ "$BACKEND" = "mpd" ]; then
        mpc next
    else
        playerctl next
    fi
}

cmd_prev() {
    if [ "$BACKEND" = "mpd" ]; then
        mpc prev
    else
        playerctl previous
    fi
}

toggle_backend() {
    if [ "$BACKEND" = "mpd" ]; then
        echo "mpris" > "$STATE_FILE"
    else
        echo "mpd" > "$STATE_FILE"
    fi
}

case "$1" in
    toggle) cmd_play_pause; exit ;;
    next) cmd_next; exit ;;
    prev) cmd_prev; exit ;;
    backend) toggle_backend; exit ;;
esac

# -------------------------------
# Get title + status
# -------------------------------

if [ "$BACKEND" = "mpd" ]; then
    STATUS_RAW=$(get_mpd_status)
    TITLE=$(get_mpd_title)

    if [[ "$STATUS_RAW" == *"[playing]"* ]]; then
        STATUS="playing"
    else
        STATUS="paused"
    fi

    ICON_BACK="$ICON_MPD"
else
    STATUS_RAW=$(get_mpris_status)
    TITLE=$(get_mpris_title)

    if [ "$STATUS_RAW" = "Playing" ]; then
        STATUS="playing"
    else
        STATUS="paused"
    fi

    ICON_BACK="$ICON_MPRIS"
fi

[ -z "$TITLE" ] && TITLE="No media"

# 🔥 Normalize BEFORE scrolling
TITLE=$(normalize_width "$TITLE")

SCROLL_TEXT="${TITLE}${PADDING}"
LEN=${#SCROLL_TEXT}

[ -f "$SCROLL_FILE" ] && POS=$(cat "$SCROLL_FILE") || POS=0
POS=$((POS % LEN))

VISIBLE=""
for ((i=0; i<MAX_LENGTH; i++)); do
    IDX=$(((POS + i) % LEN))
    VISIBLE+="${SCROLL_TEXT:IDX:1}"
done

NEW_POS=$(( (POS + SCROLL_SPEED) % LEN ))
echo "$NEW_POS" > "$SCROLL_FILE"

if [ "$STATUS" = "playing" ]; then
    ICON_PP="$ICON_PAUSE"
else
    ICON_PP="$ICON_PLAY"
fi

echo "%{A1:$0 prev:}$ICON_PREV%{A} %{A1:$0 toggle:}$ICON_PP%{A} %{A1:$0 next:}$ICON_NEXT%{A} %{A1:$0 backend:}$ICON_BACK%{A}  $VISIBLE"
