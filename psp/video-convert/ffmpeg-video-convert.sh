#!/usr/bin/zsh

ffmpeg -i $1 -vcodec libx264 -b:v 750k -s 480x272 -aspect 16:9 -profile:v main -level:v 2.1 -x264-params ref=3:bframes=1 -acodec aac -b:a 128k -ac 2 -movflags +faststart $2
