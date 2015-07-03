#!/bin/sh

. ./sysconfig

# Dump tmp meta file to fasten the I/O speed for many dd operations
META_TMP_SIZE=1024
OFFSET_PARTITION_META=`expr $SYSCONF_FIRMWARE_MTD_SIZE - $META_TMP_SIZE`
OFFSET_FWSIGN=`expr $META_TMP_SIZE - 4`
OFFSET_FWMAGIC=`expr $META_TMP_SIZE - 8`
OFFSET_FWCOUNTER=`expr $META_TMP_SIZE - 18`


#function func_dump_partition_meta(){
#	echo ""
#	echo "	=> Dump partition meta from: $1"
#	dd if=$1  of=/tmp/meta bs=1024 count=1 skip=`expr $SYSCONF_FIRMWARE_MTD_SIZE / $META_TMP_SIZE - 1`
#	dd if=/tmp/meta  of=/tmp/fw_sign bs=1 count=4 skip=$OFFSET_FWSIGN
#	dd if=/tmp/meta  of=/tmp/fw_magic bs=1 count=4 skip=$OFFSET_FWMAGIC
#	dd if=/tmp/meta  of=/tmp/fw_counter bs=1 count=4 skip=$OFFSET_FWCOUNTER
#	VAR0=`cat /tmp/fw_sign`
#	VAR1=`cat /tmp/fw_magic`
#	VAR2=`cat /tmp/fw_counter`
#	echo "	=> variables = { $VAR0, $VAR1, $VAR2 }"
#	echo ""
#}

# Get 1st partition meta
#func_dump_partition_meta $SYSCONF_FIRMWARE_MTD_PARTITION
	echo ""
	echo "	=> Dump partition meta from: $SYSCONF_FIRMWARE_MTD_PARTITION"
	dd if=$SYSCONF_FIRMWARE_MTD_PARTITION  of=/tmp/meta bs=1024 count=1 skip=`expr $SYSCONF_FIRMWARE_MTD_SIZE / $META_TMP_SIZE - 1`
	dd if=/tmp/meta  of=/tmp/fw_sign bs=1 count=4 skip=$OFFSET_FWSIGN
	dd if=/tmp/meta  of=/tmp/fw_magic bs=1 count=4 skip=$OFFSET_FWMAGIC
	dd if=/tmp/meta  of=/tmp/fw_counter bs=1 count=4 skip=$OFFSET_FWCOUNTER
	VAR0=`cat /tmp/fw_sign`
	VAR1=`cat /tmp/fw_magic`
	VAR2=`cat /tmp/fw_counter`
	echo "	=> variables = { $VAR0, $VAR1, $VAR2 }"
	echo ""
FW_SIGN_0=$VAR0
FW_MAGIC_0=$VAR1
if [ x$FW_MAGIC_0 == xdmax ]; then
	FW_COUNTER_0=$VAR2
else
	FW_COUNTER_0=0000
fi

# Get mirror partition meta
#func_dump_partition_meta $SYSCONF_FIRMWARE_MTD_MIRROR_PARTITION
	echo ""
	echo "	=> Dump partition meta from: $SYSCONF_FIRMWARE_MTD_MIRROR_PARTITION"
	dd if=$SYSCONF_FIRMWARE_MTD_MIRROR_PARTITION  of=/tmp/meta bs=1024 count=1 skip=`expr $SYSCONF_FIRMWARE_MTD_SIZE / $META_TMP_SIZE - 1`
	dd if=/tmp/meta  of=/tmp/fw_sign bs=1 count=4 skip=$OFFSET_FWSIGN
	dd if=/tmp/meta  of=/tmp/fw_magic bs=1 count=4 skip=$OFFSET_FWMAGIC
	dd if=/tmp/meta  of=/tmp/fw_counter bs=1 count=4 skip=$OFFSET_FWCOUNTER
	VAR0=`cat /tmp/fw_sign`
	VAR1=`cat /tmp/fw_magic`
	VAR2=`cat /tmp/fw_counter`
	echo "	=> variables = { $VAR0, $VAR1, $VAR2 }"
	echo ""
FW_SIGN_1=$VAR0
FW_MAGIC_1=$VAR1
if [ x$FW_MAGIC_1 == xdmax ]; then
	FW_COUNTER_1=$VAR2
else
	FW_COUNTER_1=0000
fi

# Get the okok partition
if [ x$FW_SIGN_0 == xf1f1 ] || [ x$FW_SIGN_0 == xsisi ]; then
	echo "	=> 1st partition sign is $FW_SIGN_0, goto mass production mode"
	FW_BOOT_FROM=0
elif [ x$FW_SIGN_0 == xokok ] && [ x$FW_SIGN_1 != xokok ] ; then
	echo "	=> Only 1st partition sign is $FW_SIGN_0, boot from 1st partition"
	FW_BOOT_FROM=0
elif [ x$FW_SIGN_0 != xokok ] && [ x$FW_SIGN_1 == xokok ] ; then
	echo "	=> Only 2nd partition sign is $FW_SIGN_1, boot from 2nd partition"
	FW_BOOT_FROM=1
elif [ x$FW_SIGN_0 == xokok ] && [ x$FW_SIGN_1 == xokok ] ; then
	echo "	=> Both partitions sign are okok, compare its version: $FW_COUNTER_0 vs. $FW_COUNTER_1"
	if [ $FW_COUNTER_0 -ge $FW_COUNTER_1 ]; then
		FW_BOOT_FROM=0
	else
		FW_BOOT_FROM=1
	fi
else
	echo "	=> Neither partitions sign are okok ($FW_SIGN_0 vs $FW_SIGN_1), goto fail safe mode"
	FW_BOOT_FROM=none
fi
echo "	=> Boot from $FW_BOOT_FROM "

# Select correct FW_SIGN and SYSCONF_BOOT_ROMFS_PARTITION
if [ x$FW_BOOT_FROM == x0 ]; then
	SYSCONF_BOOT_ROMFS_PARTITION=$SYSCONF_FIRMWARE_MTD_PARTITION
	FW_SIGN=$FW_SIGN_0
elif [ x$FW_BOOT_FROM == x1 ]; then
	SYSCONF_BOOT_ROMFS_PARTITION=$SYSCONF_FIRMWARE_MTD_MIRROR_PARTITION
	FW_SIGN=$FW_SIGN_1
else
	SYSCONF_BOOT_ROMFS_PARTITION=$SYSCONF_FIRMWARE_MTD_PARTITION
	FW_SIGN=not_ok
fi
echo "	=> Boot from:$SYSCONF_BOOT_ROMFS_PARTITION , FW_SIGN is :$FW_SIGN "

export SYSCONF_BOOT_ROMFS_PARTITION
export FW_SIGN
