#!/bin/sh

if [ -f /tmp/conf/dcchdlog.cfg ]; then
	export ENABLE_DEV_SUPPORT=1
	export DCCHD_LOG_CFG=/tmp/conf/dcchdlog.cfg
fi

while [ 1 ]; do
	cd /osd;
	dmaosd $1 $2 $3;
if [ -f /tmp/STOP_REBOOT ]; then
	sleep 3;
else
	reboot;
fi
done

