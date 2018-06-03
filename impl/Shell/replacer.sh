#!/bin/sh

FILE="$1"

cp "$FILE" "$FILE.substituted"

COUNT=1
while [[ $# -gt 0 ]]
do
	ARG="$2"
	#echo $COUNT
	sed -i "s/ARGV$COUNT#/$ARG/g" "$FILE.substituted"
	
	shift
	COUNT=$(($COUNT + 1))
done
		
