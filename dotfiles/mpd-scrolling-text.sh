#!/usr/bin/zsh

max_length=25
delay=0.5

while true; do
    mpd_status=$(mpc status | grep -Eo '\[playing\]|\[paused\]')
    song=$(mpc current --format "%title% - %artist%")

    song="🎵 Now Playing: $song"

    if [[ ${#song} -le $max_length ]]; then
        json_output="{\"text\": \"$song\", \"tooltip\": \"$song\"}"
        echo "$json_output" | jq -r '.text'
        sleep 1
    else
        song="   $song   "
        full_length=${#song}

        for i in {1..$((full_length - max_length + 1))}; do
            new_status=$(mpc status | grep -Eo '\[playing\]|\[paused\]')
            new_song=$(mpc current --format "%title% - %artist%")

            song="🎵 Now Playing: $new_song"

            scroll_text=${song[$i,$((i + max_length - 1))]}
            json_output="{\"text\": \"$scroll_text\", \"tooltip\": \"$song\"}"
            echo "$json_output" | jq -r '.text'
            sleep $delay
        done
    fi
done
