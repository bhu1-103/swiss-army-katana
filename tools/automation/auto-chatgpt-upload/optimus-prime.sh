#!/usr/bin/zsh
for (( i=57;i<60;i++ )) do
	file_number="case-no-$i.txt"
	bspc desktop -f 2; xdotool mousemove 565 1300; xdotool click 1; sleep 0.5;xdotool mousemove 600 1200; xdotool click 1;
	xdotool mousemove 800 375; xdotool click 3; xdotool key Return
	xdotool type "case-no-$i.txt"
	xdotool key Return;sleep 1;xdotool key Return
	sleep 3
	xdotool key Shift+Escape
	sleep 10
	xdotool key Return
	sleep 70
	xdotool key Ctrl+Shift+semicolon
	sleep 1
	touch /home/bhu2/dev/projects/cases-rolling-release/output-formatted/$i.txt
	xclip -selection clipboard -o > /home/bhu2/dev/projects/cases-rolling-release/output-formatted/$i.txt
	sleep 5


done
