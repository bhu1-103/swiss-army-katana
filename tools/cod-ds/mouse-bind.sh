#!/bin/bash

X1=500
Y1=500
X2=1000
Y2=800

while true; do
    eval $(xdotool getmouselocation --shell)

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
