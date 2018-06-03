#!/bin/sh

echo -n "{"

for c in $(echo $1 | grep -o .)
do
	printf "%d, " "'$c"
done

echo "0}"
