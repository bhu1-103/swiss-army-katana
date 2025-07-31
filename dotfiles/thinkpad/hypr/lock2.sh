#!/usr/bin/zsh

grim /tmp/lockscreen.png
swaylock --clock --effect-blur 10x6 --effect-vignette 0.3:0.6 --effect-scale 1.05 \
  --text-color 00ff99 --ring-color 005f5f --inside-color 001111aa \
  --indicator-radius 140 --indicator-thickness 6 \
  --image /tmp/lockscreen.png --scaling fill
