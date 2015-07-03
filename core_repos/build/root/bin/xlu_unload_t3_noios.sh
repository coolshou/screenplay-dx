#!/bin/sh
#set -e
#

video_tag=0xbbbbbbbb
audio_tag=0xaaaaaaaa
demux_tag=0xdddddddd

echo Stopping audio0
xkc ukill a -1 || echo "   ukill audio0 failed"
echo Stopping audio1
xkc ukill A -1 || echo "   ukill audio1 failed. 8654 has no audio1."
echo Stopping audio2
xkc ukill @ -1 || echo "   ukill audio2 failed. 8654 has no audio2."
echo Stopping video0
xkc ukill v -1 || echo "   ukill video0 failed"
echo Stopping video1
xkc ukill V -1 || echo "   ukill video1 failed. 8654 has no video1."
echo Stopping demux0
xkc ukill d -1 || echo "   ukill demux0 failed"
echo Stopping demux1
xkc ukill D -1 || echo "ukill demux1 failed. 8644 has no demux1."
echo Unloading demuxpsf ucode
xkc xunload ${demux_tag}
echo Unloading audio ucode
xkc xunload ${audio_tag}
echo Unloading video ucode
xkc xunload ${video_tag}
