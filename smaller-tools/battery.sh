#!/usr/bin/zsh

export DISPLAY=:0
export DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/$(id -u)/bus"
battery_level=$(acpi | head -n 1 | tail -n 1 | awk '{print $4}' | tr -d ',%')

if [ "$battery_level" -gt 75 ]; then
	dunstify "Unplug charger" "Current battery level is $battery_level%"
fi

if [ "$battery_level" -lt 45 ]; then
	dunstify "Battery Level" "Critical $battery_level%"
fi
