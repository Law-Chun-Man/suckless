#!/bin/bash

output=$(jupyter lab list | grep -Eo 'http://[^ ]+')

if [ -n "$output" ]; then
    firefox "$output"
else
    jupyter lab --notebook-dir=~/linux_computer/jupyter_file &
fi
