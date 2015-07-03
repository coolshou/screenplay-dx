#!/bin/sh

files=`ls *.po`

for f in $files
do
   echo "_______________svn diff [$f]____________________"
   svn diff $f
done
