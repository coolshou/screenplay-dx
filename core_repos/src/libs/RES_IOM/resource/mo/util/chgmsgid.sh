#!/bin/sh



function usageinfo()
{
	echo "$0 FILE  srcid tarid"
        echo " (ex: $0 en.po  \"This\" \"That\")"
}

if [ ! -z "$1" ]; then
   files=`ls $1`
fi

if [  $# -eq 3 ]; then
        srcid=$2
        tarid=$3
        echo "FILES:${files/\n/,/}"
        for f in $files
	do
		echo "[${f}] ${srcid} ==> ${tarid}"
                sed -i "s/msgid \"$srcid\"/msgid \"$tarid\"/" $f
	done

else
	usageinfo
fi



