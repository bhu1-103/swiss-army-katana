#!/usr/bin/zsh

function handle_brightness {
  dark=$(echo "l($latest_brightness) / l(1.004)" | bc -l)
  echo $dark
  if [ $(echo "$latest_brightness == 0" | bc -l) -eq 1 ]; then
    brightnessctl sset 1
  else
    brightnessctl sset $dark
  fi
}

while true; do
    if [ -f "/home/bhu2/dev/bin/light_values.txt" ]; then
        latest_brightness=$(grep "Light changed" /home/bhu2/dev/bin/light_values.txt | tail -n 1 | awk '{print $3}')
        handle_brightness "$latest_brightness"
    else
        echo "light_values.txt file not found."
    fi

    sleep 1
done

