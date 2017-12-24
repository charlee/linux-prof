#!/bin/bash
read -n 1 -t 5 -p "Press any key in 5 seconds to cancel autorun..."

if [ "$?" != "0" ]; then
    if [ -f "kernel-version.tmp" ]; then
        make tar
        sleep 5
        mv output.tar.gz output-$(cat kernel-version.tmp).tar.gz
    fi
    python switch_kernel.py
fi
