#!/bin/bash
FILES=$(ls $1)
ITERATOR=0
for FILE in $FILES
do
	echo "$ITERATOR) $FILE"
	ITERATOR=$((1 + $ITERATOR))
done
