#!/bin/bash
read -n 1 -t 5 -p "Press any key in 5 seconds to cancel autorun..."

if [ "$?" != "0" ]; then
    if [ -f "kernel-version.tmp" ]; then
        make tar
        mv output.tar.gz output-$(cat kernel-version.tmp).tar.gz
        echo "Test done, will reboot for next kernel after 5 seconds..."
    else
        # Write startup script
        cp contrib/linux-prof-autorun $HOME/.linux-prof-autorun
        echo "Autorun setup done, will reboot after 5 seconds..."
    fi

    sleep 5
    python switch_kernel.py

    # if done
    if [ "$?" == 1 ]; then
        rm $HOME/.linux-prof-autorun
    fi
fi
