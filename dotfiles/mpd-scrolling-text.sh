#!/usr/bin/zsh

max_length=25
delay=0.5

while true; do
    song=$(mpc current --format "%title% - %artist%")
    
    if [[ -z "$song" ]]; then
        sleep 1
        continue
    fi

    song="   $song   "
    full_length=${#song}

    for ((i = 0; i <= full_length - max_length; i++)); do
        scroll_text=${song[i,max_length]}
        echo "$scroll_text"
        sleep $delay
    done
done
