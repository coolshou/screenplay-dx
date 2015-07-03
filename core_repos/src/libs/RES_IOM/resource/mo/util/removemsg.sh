#!/bin/sh 




function usageinfo()
{
        echo "Remove msgid+msgstr from .po file"
	echo "Remove From *.po  $0 \"msg string\""
        echo "Remove From cht.po $0 \"Video\" cht.po"
}


if [ $# -gt 0 ]; then
 	srcid=$1
        pos="$2 $3 $4 $5 $6 $7 $8 $9"
	if [ $# -eq 1 ]; then
	pos="*.po"
	fi
	
	files=`grep  -e "\"$1\"" ${pos}|awk -F":" '{ print $1}'`
	for f in $files
	do
	  echo -e "Remove msgid \"${srcid}\"\nmsgstr "...." from [${f}]"
	  sed -i "/msgid/N;s#msgid \"${srcid}\"\nmsgstr.*##" $f
	done
else
	usageinfo
fi
