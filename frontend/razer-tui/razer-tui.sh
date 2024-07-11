#!/bin/bash

options=("1" "Brightness"
         "2" "Mode"
         "3" "Polling Rate")

choice=$(dialog --clear --title "Razer DeathAdder Settings" --menu "Choose an option:" 15 40 4 "${options[@]}" 2>&1 >/dev/tty)

case $choice in
    1)
        echo "Adjust Brightness"
        ;;
    2)
        echo "Select Mode"
        ;;
    3)
        echo "Set Polling Rate"
        ;;
    *)
        echo "Cancelled"
        ;;
esac

