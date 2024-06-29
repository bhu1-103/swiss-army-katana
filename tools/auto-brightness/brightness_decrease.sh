#!/usr/bin/zsh

current_dumb_brighness=$(brightnessctl | grep Curr | awk '{print $3}')
echo $current_dumb_brighness
new_dumb_brightness=$((current_dumb_brighness * 0.8))
echo $new_dumb_brightness
brightnessctl s $((new_dumb_brightness))
