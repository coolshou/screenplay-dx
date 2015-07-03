#!/bin/sh 




function usageinfo()
{
        echo "Remove msgid+msgstr from .po file"
	echo "$0 FILE \"msg string\""
        echo "$0 en.po \"Video\""
}

rm -f tmp
if [ $# -eq 1 ]; then
 	srcid=$1
	files=`ls *.po`
	for f in $files
	do
          echo -e -n "${f/.po/}\t" >> tmp
	  sed -n "/msgid/N;s#msgid \"${srcid}\"\nmsgstr \(.*\)#\1#p" $f >> tmp
          cat tmp
	done
else
	usageinfo
fi
