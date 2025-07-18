#!/bin/bash

# Initial brightness
file="/sys/class/backlight/"*"/brightness"
echo 3 | sudo tee $file >/dev/null &

# Other settings
#feh --no-fehbg --bg-fill ~/.config/dwm/others/black.png &
/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1 &
/usr/lib/x86_64-linux-gnu/libexec/kdeconnectd &
dunst &
nm-applet &
/usr/bin/sudo tlp start &
picom --backend glx --vsync -b &
#xset s off &
pactl get-source-mute @DEFAULT_SOURCE@ | grep -q 'no' && pactl set-source-mute @DEFAULT_SOURCE@ toggle &
xss-lock -- slock &

# Status bar
kill $(pgrep -f ~/.config/dwm/bash_scripts/status_bar.sh)
~/.config/dwm/bash_scripts/status_bar.sh &
