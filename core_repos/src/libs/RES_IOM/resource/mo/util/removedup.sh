#!/bin/sh

#Detect if in Chinese locale
lang=`locale|grep LANG|awk -F"." '{print $2}'`
if [ "${lang}" == "UTF-8" ]; then
	dupstr="重複"
else
	dupstr="duplicate"
fi


#define MO convert tool in linux
MO_CONVERT_TOOL=msgfmt

#
#
#  This script will use msgfmt to format .po 
#  and output error (duplicate line) number to file '2'
#  and replace the duplicate msgid + msgstr with null string (use sed)
#  and reformat .po again
#  so if there is still error print out
#  something 

files=`ls *.po`

for f in $files
do
  echo "file:$f"
  $MO_CONVERT_TOOL $f 2>1
  cat 1| grep $dupstr |awk -F":" '{ print $2 }' > 2
  lines=`cat 2`
  for ll in $lines
  do
	sed -i "${ll}N;s/msgid.*\nmsgstr.*/\n/" $f
  done
  rm -f 1 2
  echo "Reformating ${f} to ${f/po/mo}"
  $MO_CONVERT_TOOL $f -o ${f/po/mo}
done
