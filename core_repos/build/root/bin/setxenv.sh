#!/bin/sh

DEVICENAME="mtdblock0"
set -e

SKIP_BLK=
COMMAND=
MODE=
KEY=
VALUE=

if [ "$0" = "/bin/setxenv" ]; then
  if [ $# = 0 ] || [ $# -gt 4 ]; then
echo "Syntax error: $0 <skip_blk> [[-b] <keyname> <value>]|[<keyname>]"
exit -1
  fi

  if [ $1 -lt 0 ] || [ $1 -gt 3 ]; then
    echo "Error: skip_blk = 0, 1, 2, or 3"
    exit -1
  fi
  SKIP_BLK=$1

  if [ $# = 1 ]; then
    COMMAND=listall
  fi
  if [ $# = 2 ]; then
    COMMAND=listone
    KEY=$2
  fi
  if [ $# = 3 ]; then
    COMMAND=addone
    MODE=text
    KEY=$2
    VALUE=$3
  fi
  if [ $# = 4 ]; then
    if [ $2 != "-b" ]; then
echo "Syntax error: $0 <skip_blk> [[-b] <keyname> <value>]|[<keyname>]"
exit -1
    else
      COMMAND=addone
      MODE=binary
      KEY=$3
      VALUE=$4
    fi
  fi

fi

if [ $0 = "/bin/unsetxenv" ]; then
  if [ $# != 2 ]; then
echo "Syntax error: $0 <skip_blk> <keyname>"
exit -1
  fi
  SKIP_BLK=$1

  COMMAND=deleteone
  KEY=$2
fi

#echo skip_blk = "$SKIP_BLK"
#echo command = "$COMMAND"
#echo mode = "$MODE"
#echo key = "$KEY"
#echo value = "$VALUE"

# Scripting arguments ...
# Which block (0 .. 3) to be operate on
# SKIP_BLK=0
# XENV2 program parameters ...
# XENV2_PRG_OPT=

###### Should not need to change bellows ...

# Block size (in KB)
PHY_BLK_SIZE=128

# XENV2 block size (in KB)
XENV2_BLK_SIZE=16

# NAND Block device
#NAND_BDEV=/dev/sigmblk0
NAND_BDEV=/dev/${DEVICENAME}
echo "Open $NAND_BDEV"
# XENV2 operation program
XENV2_PRG=/bin/setxenv2_mipsel

#if [ ! -b "$NAND_BDEV" ]; then
#	echo "$NAND_BDEV not found."
#	exit -1
if [ ! -x "$XENV2_PRG" ]; then
	echo "$XENV2_PRG program not found."
	exit -1
fi

PHY_BLOCK_FILE=`mktemp /tmp/phy_blk.tmp.XXXXXX`
XENV2_TMP_FILE=`mktemp /tmp/xenv.tmp.XXXXXX`
PHY_REST_FILE=`mktemp /tmp/phy_rest.tmp.XXXXXX`

dd if=$NAND_BDEV of=$PHY_BLOCK_FILE bs=${PHY_BLK_SIZE}K skip=$SKIP_BLK count=1
dd if=$PHY_BLOCK_FILE of=$XENV2_TMP_FILE bs=1K count=$XENV2_BLK_SIZE
dd if=$PHY_BLOCK_FILE of=$PHY_REST_FILE bs=1K skip=$XENV2_BLK_SIZE

# Operating on XENV2 block
# $XENV2_PRG $XENV2_PRG_OPT $XENV2_TMP_FILE
case "$COMMAND" in
  listall)
  $XENV2_PRG -f $XENV2_TMP_FILE
  ;;
  listone)
  $XENV2_PRG -f $XENV2_TMP_FILE -k $KEY
  ;;
  addone)
  if [ "$MODE" == "text" ]; then 
    $XENV2_PRG -f $XENV2_TMP_FILE -k $KEY -v "$VALUE"
  else
    $XENV2_PRG -f $XENV2_TMP_FILE -b -k $KEY -v "$VALUE"
  fi
  cat $XENV2_TMP_FILE /dev/zero | dd of=$PHY_BLOCK_FILE bs=1K count=$XENV2_BLK_SIZE
  cat $PHY_REST_FILE >> $PHY_BLOCK_FILE
  dd if=$PHY_BLOCK_FILE of=$NAND_BDEV bs=${PHY_BLK_SIZE}K seek=$SKIP_BLK count=1
  ;;
  deleteone)
  $XENV2_PRG -f $XENV2_TMP_FILE -u -k $KEY
  cat $XENV2_TMP_FILE /dev/zero | dd of=$PHY_BLOCK_FILE bs=1K count=$XENV2_BLK_SIZE
  cat $PHY_REST_FILE >> $PHY_BLOCK_FILE
  dd if=$PHY_BLOCK_FILE of=$NAND_BDEV bs=${PHY_BLK_SIZE}K seek=$SKIP_BLK count=1
  ;;
esac

sync
sync

rm -f $PHY_BLOCK_FILE $XENV2_TMP_FILE $PHY_REST_FILE

exit 0

