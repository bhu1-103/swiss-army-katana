#/usr/bin/zsh

for file in audio/*.wav; do
  ffmpeg -i "$file" -q:a 2 "${file%.wav}.mp3"
done
