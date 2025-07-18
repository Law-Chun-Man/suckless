#!/bin/bash

dir=~/linux_computer/Spanish/words/
files=$(ls -1 $dir)
choice=$(echo -e "train\n$files" | dmenu -i -p "Spanish: ")

[ -z "$choice" ] && exit 0

case $choice in
    "train")
        cd $dir
        st -f "JetBrainsMono:pixelsize=60:antialias=true:autohint=true"
        ;;
    *)
        cd $dir
        st -e nvim $choice
esac
