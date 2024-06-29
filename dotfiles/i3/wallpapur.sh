#! /bin/bash


wallpaper_folder="/home/bhu2/Pictures/wallpapers"
wallpaper=$(ls $wallpaper_folder | sort -R | tail -1)
wal -i "$wallpaper_folder/$wallpaper"


