#!/bin/sh

while true; do
	ret=0
	for slist in pool.ntp.org us.pool.ntp.org time.windows.com ; do
		echo '/bin/ntpdate ' $slist
		/bin/ntpdate $slist 2> /dev/null ;
		if [ $? -eq 0 ]; then
			ret=1
			touch "/tmp/ntpdate-success"
			echo 'Use NTP server' $slist 'successfully.'
			break
		fi
	done
	
	if [ $ret -eq 1 ]; then
		echo 'Update Network Time is done'
		break
	fi
    sleep 3
done
