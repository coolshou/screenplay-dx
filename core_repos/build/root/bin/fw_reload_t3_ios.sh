#!/bin/sh
#echo Loading llad.ko
rmmod em8xxx

#unload_imat.sh;
#xlu_unload_t3.sh -i -u;
#xlu_load_t3.sh -i -u
#insmod /lib/modules//em8xxx.ko

ikc pause
xkc xload 0x105105 /lib/firmware/ios.bin.gz*.xload
insmod /lib/modules//em8xxx.ko

echo "firmware reload succesful"







