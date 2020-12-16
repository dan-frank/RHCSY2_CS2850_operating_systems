#!/bin/sh
# select.sh
IN="students.txt"
START=$1
END=$2
END=$((END+1))
FIRST=$(sort $IN | head -1 | cut -d / -f 1)
LAST=$(sort $IN | tail -1 | cut -d / -f 1)
if [ $# -ne 2 ]; then
    echo "Usuage: $0 [startID] [endID]"
    echo "first ID=$FIRST"
    echo "last ID=$LAST"
else
    LOOP=$START
    while [ "$LOOP" -lt "$END" ]
    do
        grep $LOOP $IN
        LOOP=$((LOOP+1))
    done
fi
