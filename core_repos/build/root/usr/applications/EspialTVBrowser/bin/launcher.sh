#!/bin/sh

# AR/English
#export LANGUAGE=AR
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/AR/favourites.html

# BP
#export LANGUAGE=BP
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/BP/EU/favourites.html
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/BP/NA/favourites.html

# CS
#export LANGUAGE=CS
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/CS/favourites.html

# CT
#export LANGUAGE=CT
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/CT/favourites.html

# CZ
#export LANGUAGE=CZ
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/CZ/favourites.html

# DN
#export LANGUAGE=DN
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/DN/favourites.html

# E
export LANGUAGE=E
export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/E/EU/favourites.html
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/E/NA/favourites.html
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/adobe.html
#export HOMEPAGE=http://www.bing.com/videos/watch/video/tom-and-giseles-christmas-lights/1nw25vl
#export HOMEPAGE=http://kbs.co.kr
#export HOMEPAGE=http://www.youtube.com/xl
#export HOMEPAGE="http://www.certificationsuites.com/script/php/playlists/file.php?fileId=2377&swfWrap=1&p=flash&v=10.1&r=1.0.15&w=240&h=320"
#export HOMEPAGE=http://www.facebook.com

# ES
#export LANGUAGE=ES
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/ES/EU/favourites.html
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/ES/NA/favourites.html

# F
#export LANGUAGE=F
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/F/EU/favourites.html
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/F/NA/favourites.html

# FIN
#export LANGUAGE=FIN
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/FIN/favourites.html

# G
#export LANGUAGE=G
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/G/favourites.html

# GK
#export LANGUAGE=GK
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/GK/favourites.html

# HB
#export LANGUAGE=HB
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/HB/favourites.html

# HU
#export LANGUAGE=HU
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/HU/favourites.html

# I
#export LANGUAGE=I
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/I/favourites.html

# J
#export LANGUAGE=J
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/J/favourites.html

# K
#export LANGUAGE=K
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/K/favourites.html

# N
#export LANGUAGE=N
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/N/favourites.html

# NL
#export LANGUAGE=NL
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/NL/favourites.html

# PL
#export LANGUAGE=PL
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/PL/favourites.html

# RU
#export LANGUAGE=RU
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/RU/favourites.html

# SW
#export LANGUAGE=SW
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/SW/favourites.html

# TK
#export LANGUAGE=TK
#export HOMEPAGE=file:///usr/applications/EspialTVBrowser/bin/HtmlUI/TK/favourites.html

#export DCCHD_LOG_CFG=/tmp/dcchdlog.cfg

#export ESPIAL_DUMP_SWF=true
#export EVO_DEBUG_MASK=0x0FFFFFFFF
# flash circular buffer max size
export FLASH_CIRC_FILE_MAX_SIZE_MB=10
# flash temporary directory
export FLASH_TEMP_DIR=/tmp
# spit out the format
export FLASH_ANNOUNCE_FORMAT=true
# skip On2 frames
export FLASH_SKIP_ON2_DECODE=true
#skip Sorenson
export FLASH_SKIP_SORENSON_DECODE=true
#preallocate teh circular buffer
export FLASH_CIRC_FILE_PREALLOC=true
# EspialTVBrowser temporary directory
export TMPDIR=/tmp
# library path
export LD_LIBRARY_PATH=../lib:/mnt/dcchd/dcchd/dcchd:/mnt/dcchd/dcchd/core:/mnt/dcchd/dcchd/mono:/mnt/dcchd/dcchd/dtv/acap:/mnt/dcchd/dcchd/dtv/tuner:/mnt/dcchd/dcchd/dtv:/mnt/mrua/lib:/mnt/dcchd/directfb/lib:/mnt/dcchd/dcchd/dtv/capture:/mnt/dcchd/dcchd/dtv/network:/lib:../lib/pango/1.6.0/modules
# stack size
ulimit -s 16384

#export LC_ALL=
export LANG=en_US
#export LANGUAGE=en_US

export PANGO_RC_FILE=/usr/applications/EspialTVBrowser/etc/pangorc

./EspialTVBrowser
#./EspialTVBrowser 2> FACEBOOK
#strace -o TRACE ./EspialTVBrowser
