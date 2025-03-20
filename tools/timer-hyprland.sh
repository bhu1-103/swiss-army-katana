#!/usr/bin/zsh

time=$1
workspace=$2
minute=60 #if no 3rd input parameter is passed, it automatically sets it to 60
minute=$3

for (( x=$time;x>0;x-- )); do
	sleep 1
	if (( x % minute == 0 )); then
		dunstify "hey, $minute seconds has passed" "time left: $(($x/$minute*$minute)) seconds"
		if (( x == 60 )); then
			dunstify "almost done cooking" "less than 1 minute left"
		fi
	fi
done

for (( x=0;x<5;x++ ));do
    razer-cli -b 5
    sleep 1
    razer-cli -b 100
done
hyprctl dispatch workspace $workspace
