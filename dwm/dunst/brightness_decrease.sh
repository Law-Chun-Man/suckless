#!/bin/bash

file="/sys/class/backlight/"*"/brightness"
CURRENT_BRIGHTNESS=$(cat $file)
BRIGHTNESS=$((CURRENT_BRIGHTNESS - 3))

echo "$BRIGHTNESS" | sudo tee $file >/dev/null

dunstify -r 1235 -h int:value:"$BRIGHTNESS" -I ~/.config/dwm/dunst/display-brightness.png -t 3000 "$BRIGHTNESS%"
