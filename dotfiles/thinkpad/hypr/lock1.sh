#!/usr/bin/zsh

grim /tmp/lockscreen.png
swaylock --clock --effect-pixelate 6 --effect-vignette 0.2:0.7 \
  --text-color 00ff99 --ring-color 005f5f --inside-color 001111aa \
  --indicator-radius 140 --indicator-thickness 6 \
  --image /tmp/lockscreen.png --scaling fill
