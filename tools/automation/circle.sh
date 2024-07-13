#!/usr/bin/zsh

for (( x=3; x<100; x++ )); do
    y=$((x+1))
    make; sleep 1;
    ./pls-work &
    pls_work_pid=$!
    sleep 1
    scrot --focused --border
    if ps -p $pls_work_pid > /dev/null; then
        kill $pls_work_pid
    fi
    sed -i "s/circle_resolution = $x/circle_resolution = $y/g" source/main.cpp
    dunstify "done"
done

