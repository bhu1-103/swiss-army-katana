#!/usr/bin/zsh
current_dumb_brightness=$(brightnessctl | grep Cu | awk '{print $3}')
#echo $current_dumb_brightness
#new_dumb_brightness=$((current_dumb_brightness * 1.25))
#echo $new_dumb_brightness
#echo $((new_dumb_brightness * 10.6))
if (( current_dumb_brightness < 4 )); then
  new_dumb_brightness=10
else
  new_dumb_brightness=$((current_dumb_brightness * 1.25))
fi
brightnessctl s $((new_dumb_brightness))
