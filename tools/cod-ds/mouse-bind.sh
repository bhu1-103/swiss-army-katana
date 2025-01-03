#!/bin/bash

X1=1500
Y1=200
X2=2400
Y2=1200

xdotool mousedown 1
while true; do

    eval $(xdotool getmouselocation --shell)
	BUTTON_STATE=$(xdotool getmouselocation --shell | grep BUTTONS | cut -d= -f2)
	if [[ $BUTTON_STATE == *"1"* ]]; then
		xdotool key q
    fi

    if [ "$X" -lt "$X1" ]; then
        xdotool mousemove $X1 $Y
    elif [ "$X" -gt "$X2" ]; then
        xdotool mousemove $X2 $Y
    fi

    if [ "$Y" -lt "$Y1" ]; then
        xdotool mousemove $X $Y1
    elif [ "$Y" -gt "$Y2" ]; then
        xdotool mousemove $X $Y2
    fi

    sleep 0.01
done
