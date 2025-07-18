#!/bin/bash

choice=$(echo -e "Dual monitor\nExternal monitor\nLaptop monitor\nLaptop monitor (1920x1080)" | dmenu -i -p "Choose an option: ")

[ -z "$choice" ] && exit 0

case $choice in
    "Dual monitor")
        xrandr --output HDMI-A-0 --mode 1920x1080 --primary --output eDP --auto --below HDMI-A-0
        sleep 5
        xrandr --output HDMI-A-0 --brightness 0.4 
        ;;
    "External monitor")
        xrandr --output HDMI-A-0 --mode 1920x1080 --output eDP --off
        sleep 5
        xrandr --output HDMI-A-0 --brightness 0.4 
        ;;
    "Laptop monitor")
        xrandr --output HDMI-A-0 --off --output eDP --auto
        ;;
    "Laptop monitor (1920x1080)")
        xrandr --output HDMI-A-0 --off --output eDP --mode 1920x1080
        ;;
esac

