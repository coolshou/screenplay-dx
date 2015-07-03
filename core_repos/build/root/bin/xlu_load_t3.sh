#!/bin/sh
set -e

video_tag=0xbbbbbbbb
audio_tag=0xaaaaaaaa
demux_tag=0xdddddddd
ios_tag=0x00105105
export RUAFW_DIR=/lib/firmware
lrroxenv_location=0x61d00 #$(gbus_read_uint32 0x61a00)
lrroxenv_size=628
isprod="prod"

has_audio0=y
has_audio1=n
has_audio2=n
has_video0=y
has_video1=n
has_demux0=y
has_demux1=n
has_ipu=y
has_demux1=y

cert12="83c4b39beb4963951e384fde4bc67e39d14b965810"
cert13="91cbeca790e94e119c3fd7fcfbcf6806dd27795311"
cert14="dc35da137bd6a684ab3bd8b18f3358d1f63b61c012"
cert15="d43069fc20bbac0913d298613374ad04cbef841013"
cert16="a7308012f5b4a6d83bf4acb3244f3aea796f774b14"
cert17="94b7504f25a1cc4ff3739457aed2aa44bf64e4b215"
cert18="14e5f8da47e42b3f6ec76910ba3af107b7c8df1c16"
cert19="6ff5bee67576692fc2d009a68e15c93dbddd7d5b17"

gbus_read_bin_to_file 0x61d00 0x274 /tmp/lrro.xenv
bc04=$(genxenv2 l /tmp/lrro.xenv 2>/dev/null | grep -e " bc04 " | sed -e's/.*bc04\s*//' | sed -e's/ *//g')
echo bc04 is $bc04


SMP86XX_CHIP_CERTID="unknown"
stra=$cert12
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert13
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert14
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert15
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert16
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert17
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert18
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

stra=$cert19
echo stra is $stra
echo $stra > /tmp/certid
dd if=/tmp/certid of=/tmp/certid40 bs=1 count=40
dd if=/tmp/certid of=/tmp/certid42 bs=1 count=2 skip=40
strb=`cat /tmp/certid40`
echo strb is $strb
if [ x${bc04} == x$strb ]; then
	strc=`cat /tmp/certid42`
	export SMP86XX_CHIP_CERTID="0x${strc}"
	echo SMP86XX_CHIP_CERTID=$SMP86XX_CHIP_CERTID
fi

real_label="noreal"

if [ ${SMP86XX_CHIP_CERTID} == "0x10" ]; then
	dts_label="nodts"
	echo dts = $dts_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x11" ]; then
	dts_label="dts44"
	echo dts = $dts_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x12" ]; then
	dts_label="dts42"
	echo dts = $dts_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x13" ]; then
	dts_label="dts54"
	echo dts = $dts_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x14" ]; then
	dts_label="dts52"
	echo dts = $dts_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x15" ]; then
	dts_label="nodts"
	real_label="real"
	echo dts = $dts_label
	echo real = $real_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x17" ]; then
	dts_label="dts54"
	real_label="real"
	echo dts = $dts_label
	echo real = $real_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x18" ]; then
	dts_label="dts42"
	real_label="real"
	echo dts = $dts_label
	echo real = $real_label
fi
if [ ${SMP86XX_CHIP_CERTID} == "0x19" ]; then
	dts_label="dts52"
	real_label="real"
	echo dts = $dts_label
	echo real = $real_label
fi

if [ x$dts_label == "x" ]; then
	dts_label="dts"
	echo dts = $dts_label
fi

if [ ${dts_label} == "nodts" ]; then  
	echo "no dts"  
else  
	/bin/touch /tmp/has_dts 
fi

if [ ${real_label} != "real" ]; then
	echo "no real"  
else  
	/bin/touch /tmp/has_real
fi

if [ ! -e ${RUAFW_DIR}/audio_microcode_t3iptv_prod_${dts_label}.xload ]; then
	dts_label=${SMP86XX_CHIP_CERTID}_${dts_label}
	video_xload=${RUAFW_DIR}/video_microcode_t3iptv_prod_${real_label}.xload
else
	video_xload=${RUAFW_DIR}/video_microcode_t3iptv_prod.xload
fi

audio_xload=${RUAFW_DIR}/audio_microcode_t3iptv_prod_${dts_label}.xload
demux_xload=${RUAFW_DIR}/demuxpsf_microcode_t3iptv_prod.xload
ios_xload=$RUAFW_DIR/ios.bin.gz_t3iptv_prod.xload

DA=`rmmalloc 0 2340777`
echo Using scratch=$DA

echo Loading video ucode: ${video_xload}
xkc xload ${video_tag} ${video_xload} $DA 0

echo Loading audio ucode: ${audio_xload}
xkc xload ${audio_tag} ${audio_xload} $DA 0

	if [ ${IS_DTCP} == "y" ]; then
		echo Loading xtask_drm_dtcp-1_5-t3_8644_ES1_prod_0007.xload
		xkc xload 0xd7cbd7cb /lib/xtask_drm_dtcp-1_5-t3_8644_ES1_prod_0007.xload $DA
	fi

echo Loading demuxpsf ucode: ${demux_xload}
xkc xload ${demux_tag} ${demux_xload} $DA 0

rmfree 0 $DA

if [ "${has_demux0}" == "y" ]; then
	echo "Staring demux0..."
	xkc ustart ${demux_tag} d || (echo failed; exit 1)
fi
if [ "${has_demux1}" == "y" ]; then
	echo "Staring demux1..."
	xkc ustart ${demux_tag} D || (echo failed; exit 1)
fi
if [ "${has_video0}" == "y" ]; then
	echo "Staring video0..."
	xkc ustart ${video_tag} v || (echo failed; exit 1)
fi
if [ "${has_video1}" == "y" ]; then
	echo "Staring video1..."
	xkc ustart ${video_tag} V || (echo failed; exit 1)
fi
if [ "${has_audio0}" == "y" ]; then
	echo "Staring audio0..."
	xkc ustart ${audio_tag} a || (echo failed; exit 1)
fi
if [ "${has_audio1}" == "y" ]; then
	echo "Staring audio1..."
	xkc ustart ${audio_tag} A || (echo failed; exit 1;)
fi
if [ "${has_audio2}" == "y" ]; then
	echo "Staring audio2..."
	xkc ustart ${audio_tag} @ || (echo failed; exit 1)
fi

echo Loading ios: ${ios_xload}
xkc xload ${ios_tag} ${ios_xload}

if [ "${real_label}" == "real" ]; then
	enable_realvideo.sh;
fi
