#!/usr/bin/zsh

pacman -S cpupower tlp
cpupower frequency-set -d 400MHz -u 1.2GHz
#sudo iw dev wlp2s0 set power_save on
systemctl enable tlp
system disable bluetooth
#removed undervolting code as it caused unnecessary heating
