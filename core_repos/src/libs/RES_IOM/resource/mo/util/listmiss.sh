#!/bin/sh

alias rm='rm'

function usageinfo()
{
   echo "$0 \"Search string\""
   echo "(ex: $0 \"Video\")"
}

if [ ! -z "$1" ]; then
srcstr=$1
ls *.po > all
grep "\"${srcstr}\"" *.po| awk -F":" '{ print $1}' > tmp
echo "====These .po has NO such string===="
diff tmp all |grep ">" | sed 's/>//'
echo "===================================="
rm -f all
rm -f tmp
else
   usageinfo
fi
