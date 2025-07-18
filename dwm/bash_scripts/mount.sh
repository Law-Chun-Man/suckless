#!/bin/bash

devices=$(lsblk -lp | grep -E "/dev/sd" | awk '$6 == "part" { print $1 } $6 == "disk" { disk[++count] = $1 } END { for (i=1; i<=count; i++) print disk[i] }')
choice=$(echo -e "$devices" | dmenu -i -p "Choose device to mount: ")

[ -z "$choice" ] && exit 0

if sudo cryptsetup isLuks $choice; then
    st -T passphrase -g 60x1+570+500 -e sudo cryptsetup open "$choice" ssd
    folder=$(sudo blkid /dev/mapper/ssd -o value -s UUID)
    dir=/media/$USER/$folder
    sudo mkdir -p $dir
    sudo mount -o uid=$(id -u),gid=$(id -g) /dev/mapper/ssd $dir
    st -T spvifm -g 135x36+80+0 -e vifm $dir
    sudo udisksctl unmount -b /dev/mapper/ssd
    sudo cryptsetup close /dev/mapper/ssd
    sudo udisksctl power-off -b $choice
    sudo rmdir $dir
    dunstify -a "drive" -t 3000 "External drive can be safely unplugged"
else
    folder=$(sudo blkid $choice -o value -s UUID)
    dir=/media/$USER/$folder
    sudo mkdir -p $dir
    sudo mount -o uid=$(id -u),gid=$(id -g) $choice $dir
    st -T spvifm -g 135x36+80+0 -e vifm $dir
    sudo udisksctl unmount -b $choice
    sudo udisksctl power-off -b $choice
    sudo rmdir $dir
    dunstify -a "drive" -t 3000 "External drive can be safely unplugged"
fi
