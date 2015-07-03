#!/bin/sh

while [ 1 ]; do
	sleep 3;
	cpulimit --exe dmaosd --limit 98;
done

