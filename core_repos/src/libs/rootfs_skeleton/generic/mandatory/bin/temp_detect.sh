#!/bin/sh
echo "HDD temperature detecter v0.2"
sleep 180

# If /bin/smartctl is exist, it's a X2 model
if [ -f /bin/smartctl ]; then
    while true
    do
	MOUNT_LIST=`cat /proc/mounts | grep /tmp/media/usb/Local`
	if [ $? == 0 ]; then
	    HDD=`echo $MOUNT_LIST | cut -d ' ' -f 1`
# Enable S.M.A.R.T for Samsung HDD, its S.M.A.R.T setting is OFF by default
	    TEMP_LIE=`smartctl -d sat,12 -n standby -s on $HDD`
	    TEMP=0
	    TEMP_LINE=`smartctl -d sat,12 -n standby -A $HDD | grep Temperature_Celsius`
	    if [ $? == 0 ]; then
		TEMP=`echo $TEMP_LINE | cut -d ' ' -f 10`
	    fi

	    echo "HDD temperature: $TEMP"

	    if [ $TEMP -ge 65 ]; then
		echo "HDD is over heat!"
		echo "HDD over heat" > /proc/iomega/button
	    else
		if [ $TEMP -ge 60 ]; then
		    echo "HDD is heat!"
		    echo "HDD heat" > /proc/iomega/button
		fi
	    fi
	fi

# Wake up to check HDD temperature per 300 seconds
	sleep 300
    done
fi

