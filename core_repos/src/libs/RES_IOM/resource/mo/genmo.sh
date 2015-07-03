#!/bin/sh

#define MO convert tool in linux 
MO_CONVERT_TOOL=msgfmt

#
# Auto Script to generate all .po over here to .mo
# Requirement 'msgfmt'

rm -rf *.mo

function convert_all_po_to_mo(){
	echo "Convert All .po to .mo"
	POFILES=`ls *.po`
	for SRC in ${POFILES}
	do
	echo "${MO_CONVERT_TOOL} ${SRC} -o ${SRC/po/mo}"
	${MO_CONVERT_TOOL} ${SRC} -o ${SRC/po/mo}
	done
}


which $MO_CONVERT_TOOL && convert_all_po_to_mo;

