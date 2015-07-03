#!/bin/sh
set -e

memsize=0x4000
token=0x4ea17de0
xmem=''
loaded=''
started=''
success=''

devprod="prod"
xtask=${RUAFW_DIR}/xtask_enable_realvideo-*$devprod*.xload

logerr() {
	echo -e "\e[0;31mError(realvideo_enable): $@\e[0m"
}

enable_realvideo() {
	audio_engines=$1
	video_engines=$2
	if [ -z "$audio_engines" ]; then audio_engines=0; fi
	if [ -z "$video_engines" ]; then audio_engines=0; fi

	xmem=`xkc xpalloc $memsize`
	if [ $? -ne 0 ] || [ "$xmem" == "0x00000000" ]; then
		logerr "failed to allocate xpu memory."
		exit 1;
	fi
	echo "Allocated memory for realvideo xtask ($xmem)"
	echo "Loading realvideo xtask"
	xkc xload $token $xtask $xmem
	if [ $? -ne 0 ]; then
		logerr "loading realvideo xtask"
		exit 1;
	fi
	loaded='yes'
	echo "Starting realvideo xtask"
	xkc xstart $token $token $audio_engines $video_engines 0 0 
	if [ $? -ne 0 ]; then
		logerr "starting realvideo xtask"
		exit 1;
	fi
	started='yes'

	# wait (a while) give the xtask a chance to complete 

	i=0
	while [ $i -lt 10 ]; do
	       	sleep 1;
		i=`expr $i + 1`;
		xkc xunload $token
		if [ $? -eq 0 ]; then
			started=''
			loaded=''
			break;
		fi
       	done

	if [ $i -eq 10 ]; then
		logerr "unable to unload xtask!"
	fi
}

enable_realvideo 1 1
echo "RealVideo enabled."

