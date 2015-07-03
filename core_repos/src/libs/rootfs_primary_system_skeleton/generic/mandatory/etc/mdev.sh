#!/bin/sh

. /sysconfig

if [ -f /etc/ufsd.ko ]; then
	insmod /etc/ufsd.ko;
fi

mount -t tmpfs mdev /dev
mknod /dev/null c 1 3
mkdir /dev/pts
mount -t devpts devpts /dev/pts
echo /sbin/mdev > /proc/sys/kernel/hotplug
sleep 1
mdev -s 
