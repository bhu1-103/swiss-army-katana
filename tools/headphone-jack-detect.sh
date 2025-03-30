#!/bin/bash

alsactl monitor | while read -r line; do
    if [[ "$line" == *"Headphone Playback Switch"* ]]; then
        if amixer get Headphone | grep -q '\[off\]'; then
            echo "Headphones unplugged, stopping MPD..."
            mpc stop
        fi
    fi
done
