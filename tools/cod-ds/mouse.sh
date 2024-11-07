#!/usr/bin/zsh

oldX=0
oldY=0

while true; do
    eval $(xdotool getmouselocation --shell)
    
    if [ "$X" != "$oldX" ] || [ "$Y" != "$oldY" ]; then
        xte "mousedown 1"

        oldX=$X
        oldY=$Y
    else
        xte "mouseup 1"
    fi

    sleep 0.05
done

