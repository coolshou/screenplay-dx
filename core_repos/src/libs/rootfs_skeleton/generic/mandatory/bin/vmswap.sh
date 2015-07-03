#!/bin/sh

echo "Memory Swapping launcher v0.1"

while true
do
    HDD_PREFIX="/tmp/media/usb/Local"
    MOUNT_LOC=`cat /proc/mounts | grep $HDD_PREFIX | cut -d ' ' -f 2`
    if [ "$MOUNT_LOC" != "" ]; then
	case "$1" in
	    on)
		if [ ! -f /tmp/vmswap ]; then
		    echo "Creating a 200M memory swapping file..."
		    dd if=/dev/zero of=$MOUNT_LOC/swapfile bs=1024k count=200
		    echo "Format memory swapping file..."
		    mkswap $MOUNT_LOC/swapfile
		    echo "Turn on memory swapping..."
		    swapon $MOUNT_LOC/swapfile
		    touch /tmp/vmswap
		fi
		;;
	    *)
		if [ -f /tmp/vmswap ]; then
		    echo "Turn off memory swapping..."
		    swapoff $MOUNT_LOC/swapfile
		    echo "Remove memory swapping file..."
		    rm -f $MOUNT_LOC/swapfile
		    rm -f /tmp/vmswap
		fi
		;;
	esac
	break;
    fi
    sleep 10
done

