#!/bin/bash

alsactl monitor | while read -r line; do
    if [[ "$line" == *"Headphone Playback Switch"* ]]; then
        if amixer get Headphone | grep -q '\[off\]'; then
            echo "Headphones unplugged, pausing MPD..."
            mpc pause
        else
            echo "Headphones plugged in, resuming MPD..."
            mpc play
        fi
    fi
done
