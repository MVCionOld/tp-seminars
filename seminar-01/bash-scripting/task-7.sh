#!/bin/bash
function traverse(){
	for ENTRY in $(ls $1)
	do
		ENTRY_PATH=$(realpath $1/$ENTRY)
		if [ -d $ENTRY_PATH ]
		then
			echo "$ENTRY_PATH is a dir"
			traverse $ENTRY_PATH
		elif [ -f $ENTRY_PATH ]
		then
			echo "$ENTRY_PATH is a file"
		fi
	done
}

traverse $1

# Как сделать тоже самое, но через find?
