#!/bin/sh

if [ -f /usr/bin/transmission-remote ]; then
    /usr/bin/transmission-remote 127.0.0.1:80 -n admin:admin -t all -s
fi
