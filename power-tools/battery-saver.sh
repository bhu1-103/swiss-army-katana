#!/usr/bin/zsh

pacman -S cpupower tlp
cpupower frequency-set -d 400MHz -u 1.0GHz
systemctl enable tlp
system disable bluetooth
