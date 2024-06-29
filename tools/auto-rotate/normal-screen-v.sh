#!/usr/bin/zsh
xrandr --output eDP-1 --rotate left

touch=($(xsetwacom --list devices | grep TOUCH | awk '{print $9}'))
pen=($(xsetwacom --list devices | grep STYLUS | awk '{print $9}'))
eraser=($(xsetwacom --list devices | grep ERASER | awk '{print $9}'))

echo $touch $pen $eraser
xsetwacom --set "$touch" Rotate 2
xsetwacom --set "$pen" Rotate 2
xsetwacom --set "$eraser" Rotate 2
