#!/bin/bash

cal=$(python3 -c "import calendar; c = calendar.TextCalendar(6); print(c.formatmonth($(date +%Y), $(date +%-m)))"); dunstify -t 0 -a "calendar" "$cal"
