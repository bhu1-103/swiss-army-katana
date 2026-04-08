#!/usr/bin/zsh

IMG1="$HOME/.local/cache/lock1.png"
IMG2="$HOME/.local/cache/lock2.png"

rm $IMG1 $IMG2
scrot $IMG1
magick $IMG1 -fx "r>g && r>b ? u : (r+g+b)/3" $IMG2
i3lock -i $IMG2
