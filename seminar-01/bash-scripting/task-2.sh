#!/bin/bash
result=$(( $(ls -la $1 | wc -l) - 3 ))
echo "Directory $1 contains $result entries"
