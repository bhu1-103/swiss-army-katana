#!/usr/bin/zsh

function handle_rotation {
    case "$1" in
        "left-up")
            /home/bhu2/dev/bin/normal-screen-v.sh
            ;;
        "right-up")
            /home/bhu2/dev/bin/invert-screen-v.sh
            ;;
        "bottom-up")
            /home/bhu2/dev/bin/invert-screen.sh
            ;;
        "normal")
            /home/bhu2/dev/bin/normal-screen.sh
            ;;
        *) 
            ;;
    esac
}

while true; do
    if [ -f "/home/bhu2/dev/bin/rotation.txt" ]; then
        latest_orientation=$(grep "Accelerometer orientation" /home/bhu2/dev/bin/rotation.txt | tail -n 1 | awk '{print $NF}')
        
        handle_rotation "$latest_orientation"
    else
        echo "rotation.txt file not found."
    fi

    sleep 1
done

