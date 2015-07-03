#!/bin/sh
echo Loading llad.ko
export LLAD_PARAMS="max_dmapool_memory_size=0x800000 max_dmabuffer_log2_size=19"
insmod /lib/modules/llad.ko ${LLAD_PARAMS}

unload_imat.sh;
xlu_unload_t3.sh -i -u;
xlu_load_t3.sh -i -u;

insmod /lib/modules//em8xxx.ko

echo "firmware reload succesful"
