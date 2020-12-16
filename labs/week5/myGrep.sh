#!/bin/sh
#myGrep.sh
IN=$2
OUT="out.txt"
PATTERN=$1
if test -f "$IN" ; then
    grep $PATTERN $IN > $OUT
    head -10 $OUT
fi
