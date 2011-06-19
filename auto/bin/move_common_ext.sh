#!/bin/bash
# compare the files in $2 to $1. 
#If file is present in both folder then move the files from $2 to $3


mkdir $3
for i in `ls ./$1`;do 
	ls ./$2/$i 2>/dev/null
	if [ $? -eq 0 ]; then
		mv -f ./$2/$i $3/$i
	fi
done




