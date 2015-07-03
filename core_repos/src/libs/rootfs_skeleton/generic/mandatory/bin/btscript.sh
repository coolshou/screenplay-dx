#!/bin/sh

if [ -f /usr/bin/transmission-daemon ]; then
    
    case "$1" in

	start)
	    BT_PREFIX="/tmp/media/usb/Local /tmp/media/usb/USB1 /tmp/media/usb/USB2 /tmp/media/usb/USB3"
	    BT_DIR=
	    for LOC in $BT_PREFIX
	    do
		MOUNT_LIST=`cat /proc/mounts | grep $LOC | cut -d ' ' -f 2,4`
		if [ "$MOUNT_LIST" != "" ]; then
		    for FIELD in $MOUNT_LIST
		    do
			ATTRIB=`echo $FIELD | cut -d ',' -f 1`
			if [ "$ATTRIB" == "rw" ]; then
			    break;
			fi
			BT_DIR=$FIELD
		    done
		    if [ "$ATTRIB" == "rw" ]; then
			break;
		    fi
		fi
	    done

	    if [ "$ATTRIB" == "rw" ]; then
		echo "Start Transmission BT daemon"
		export HOME=$BT_DIR/transmission
		export TRANSMISSION_WEB_HOME=/usr/share/web
		export TRANSMISSION_HOME=$HOME/.config
		echo "BT_HOME=$HOME"
		echo "BT_WEB_HOME=$TRANSMISSION_WEB_HOME"
		echo "BT_CONFIG_HOME=$TRANSMISSION_HOME"
		mkdir -p $TRANSMISSION_HOME
		if [ ! -f $TRANSMISSION_HOME/settings.json ]; then
		    /usr/bin/transmission-daemon -a *.*.*.* -p 80 -t -M -u admin -v admin
		fi
		if [ -f $TRANSMISSION_HOME/settings.json ]; then
		    /usr/bin/transmission-daemon -g $TRANSMISSION_HOME
		fi
	    fi
	    ;;

	stop)
	    echo "Stop Transmission BT daemon"
	    killall transmission-daemon
	    ;;

	restart)
	    $0 stop
	    sleep 1
	    $0 start
	    ;;

	*)
	    echo "Usage: $0 {start|stop|restart}" 
	    exit 1
	    ;;
    esac
fi
