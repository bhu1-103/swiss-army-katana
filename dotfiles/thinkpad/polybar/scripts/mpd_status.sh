#!/bin/bash
icon=" "
max_length=20
scroll_speed=1

track=$(mpc current --format="%title%")
[ -z "$track" ] && track=$(mpc current --format="%file%" | sed 's|.*/||; s|\....$||')

padded_track="  ${track}  "
track_length=${#padded_track}

if (( track_length > max_length )); then
    position_file="/tmp/polybar-mpd-scroll-position"
    [ -f "$position_file" ] && position=$(cat "$position_file") || position=0

    new_position=$(( (position + scroll_speed) % (track_length - max_length + 1) ))

    echo "$new_position" > "$position_file"

    visible_part="${padded_track:position:max_length}"
else
    visible_part="$padded_track"
fi

echo "$icon${visible_part}"
