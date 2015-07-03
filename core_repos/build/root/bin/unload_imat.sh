#!/bin/sh
#set -e
echo "Killing splashscreen"
ikc kill 0x597a0000

echo "Unloading splashscreen"
ikc unload 0x0000597a

echo "Killing iloader (ok to fail)"
ikc kill 0x10ad0000 

echo "Unloading iloader"
ikc unload 0x000010ad

echo "free mem" 
lrrenv2_location=0x61a00
echo "free mem" 
lrrenv2_size=628
echo "free mem" 
zxenv2_location=`gbus_read_uint32 0x61994`
echo "free mem" 
echo "$zxenv2_location" 
zxenv2_size=16384
echo "Freeing splashscreen buffer"
gbus_read_bin_to_file ${lrrenv2_location} ${lrrenv2_size} /tmp/xenv.bin
echo "free mem" 
splash_buf0_tmp=`genxenv2 l /tmp/xenv.bin 2>/dev/null | grep splash_buf0`
echo "free mem" 
splash_buf0=`echo $splash_buf0_tmp | cut -d ' ' -f 4`
echo "splash_buf0=$splash_buf0" 
splash_buf0_mm=1
echo "free mem" 
echo rmfree $splash_buf0_mm $splash_buf0
echo "free mem" 
rmfree $splash_buf0_mm $splash_buf0
echo "free mem" 

echo "Freeing imat romfs buffer"
gbus_read_bin_to_file ${zxenv2_location} ${zxenv2_size} /tmp/xenv.bin
imat_romfs_buf_tmp=`genxenv2 l /tmp/xenv.bin 2>/dev/null | grep imat_romfs_buf`
imat_romfs_buf=`echo $imat_romfs_buf_tmp | cut -d ' ' -f 4`
echo "imat_romfs_buf=$imat_romfs_buf" 
imat_romfs_buf_mm=1
echo "free mem" 
echo rmfree $imat_romfs_buf_mm $imat_romfs_buf
rmfree $imat_romfs_buf_mm $imat_romfs_buf
echo "free mem" 


