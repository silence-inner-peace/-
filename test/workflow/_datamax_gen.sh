#!/bin/bash
for i in `seq 10`
do 
	sed -e "s/__num__/$i/g" _datamax.sh >datamax$i.sh
done
