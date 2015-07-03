#!/bin/bash
#===============================================================================
#
#          FILE:  cscope.sh
# 
#         USAGE:  ./cscope.sh 
# 
#   DESCRIPTION:  Generate cscope files for dmax project
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#          BUGS:  ---
#         NOTES:  ---
#        AUTHOR:  Joshua Lee (), Joshua_Lee@alphanetworks.com
#       COMPANY:  AlphaNetworks INC.
#       VERSION:  1.0
#       CREATED:  08/04/2008 04:48:38 PM CST
#      REVISION:  ---
#===============================================================================

PWD=`pwd`
find $PWD/{src/cas,src/misc,src/osd,src/mediaplayer,src/renderer,src/util} -iname "*.[ch]" >cscope.files
cscope -bqv
echo 'export CSCOPE_DB=$PWD/cscope.out' >cscope.env
