#!/bin/bash

choice=$(echo -e "Netherland\nJapan\nAmerica\nDisconnect" | dmenu -i -p "VPN: ")

[ -z "$choice" ] && exit 0

case $choice in
    "Disconnect")
        sudo kill $(pgrep openvpn)
        ;;
    *)
        case $choice in
            "Netherland")
                files=( ~/linux_computer/linux_setup/vpn/nl*.ovpn )
                ;;
            "Japan")
                files=( ~/linux_computer/linux_setup/vpn/jp*.ovpn )
                ;;
            "America")
                files=( ~/linux_computer/linux_setup/vpn/us*.ovpn )
                ;;
        esac
        index=$(( RANDOM % ${#files[@]} ))
        
        config="${files[$index]}"
        cred=~/linux_computer/linux_setup/vpn/credentials.txt
        sudo openvpn --config $config --auth-user-pass $cred
        ;;
esac
