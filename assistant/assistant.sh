#!/usr/bin/zsh

text_file="$HOME/.local/share/speechmodels/transcript.txt"
ffmpeg -y -f alsa -i default -acodec pcm_s16le -ac 1 -ar 44100 -t 4 -f wav ~/.cache/audio.wav

/home/bhu2/.local/bin/vosk-transcriber -m /home/bhu2/.local/share/speechmodels/vosk-model-small-en-us-0.15 -i ~/.cache/audio.wav -o $text_file
cat $text_file

action=$(awk '{print $1}' "$text_file")
arg1=$(awk '{print $2}' "$text_file")

if [[ "$action" == "open" ]]; then
	nohup $arg1 &; dunstify "opening $arg1"
elif [[ "$action" == "run" ]]; then
	nohup alacritty& dunstify "running arg1"; sleep 1;xdotool type $arg1; xdotool key Return
elif [[ "$action" == "update" ]]; then
	nohup alacritty & sleep 1; dunstify "sudo pacman -Syyu"; xdotool type "yes | sudo pacman -Syyu"; xdotool key Return; sleep 0.5; xdotool type "your_password"; xdotool key Return
else
	dunstify "still working on the feature"
fi

