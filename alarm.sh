#!/bin/bash
export DISPLAY=":0"
echo "I AM ALIVE" >> log.txt
#/home/user/ALARM_EXTEND/alarm -f /home/user/ALARM_EXTEND/alarm.ini>> log.txt
./alarm -f /home/user/ALARM_EXTEND_A_B/alarm.ini>> log.txt
