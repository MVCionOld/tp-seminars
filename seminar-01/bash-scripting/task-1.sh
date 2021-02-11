#!/bin/bash
START=$(date +%s)
sleep 5
END=$(date +%s)
DIFF=$(( $END - $START ))
echo "It took $DIFF seconds"
