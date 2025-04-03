#!/usr/bin/bash

display() {
  local scrolling_title="$1"
  local status="$2"

  if [ "$status" = "[paused]" ]; then
    status2="paused"
    echo "{\"text\": \"⏸${scrolling_title}\",\"tooltip\": \"song is ${status2}\"}"
  elif [[ "$status" = "[playing]" ]]; then
    status2="playing"
    echo "{\"text\": \"𝄞${scrolling_title}\",\"tooltip\": \"song is ${status2}\"}"
  fi
}


while true; do
  title=$(mpc current --format "%title% - %artist%")
  if [ -z "$title" ]; then
    title="________________/\____"
  fi

  status=$(mpc status | grep -Eo '\[playing\]|\[paused\]')
  scrolling_title="${title}       "

  for ((i=0;i<${#title};i++));do
    scrolling_title="${scrolling_title:1}${scrolling_title:0:1}"
    display "${scrolling_title:0:20}" "$status"
    sleep 0.5
    new_title=$(mpc current --format "%title% - %artist%")
    new_status=$(mpc status | grep -Eo '\[playing\]|\[paused\]')
    if [ "$new_title" != "$title" ] || [ "$new_status" != "$status" ]; then
      break
    fi
  done
done
