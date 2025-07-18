#!/bin/bash

file=~/.config/dwm/others/bookmarks.txt
choice=$(cat "$file" | dmenu -fn 'JetBrainsMono:size=15:weight=bold' -l 50 -i -p "Bookmarks: ")

[ -z "$choice" ] && exit 0

firefox-esr $choice
