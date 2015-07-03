#!/bin/sh

rm -f /tmp/format_sata_done

dd if=/dev/zero of=$1 bs=1048576 count=1

cat /bin/fdisk_cmd | fdisk $1 > /dev/console

part=1
mkfs.xfs -f -l lazy-count=0 -L "WDTVLiveHub" $1$part > /dev/console

touch /tmp/format_sata_done

