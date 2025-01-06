#! /usr/bin/zsh

pactl load-module module-combine-sink sink_name=combined slaves=alsa_output.pci-0000_00_1f.3.analog-stereo,bluez_output.41_42_1C_20_3A_32.1
