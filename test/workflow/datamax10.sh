#!/bin/bash
#SBATCH -p hpxg
#SBATCH -t 00:05:00 
#SBATCH -n 1
#SBATCH -J datamax10
#SBATCH -o /data/%u/test/workflow/log/%x.%j.stdout
#SBATCH -e /data/%u/test/workflow/log/%x.%j.stderr

echo "START[`date`]: $USER@`hostname -f`: PID=$$ "

ddir=/data/$USER/test/workflow/data
dfile=$ddir/input10
[ ! -f "$dfile" ] && echo "Err: $dfile not exist" && exit 1

ofile=$ddir/max10
max=`sort -n -r $dfile | head -n 1`

echo "END[`date`]"

sleep 5

e=`expr $RANDOM \% 3`
if [ $e -gt 0 ]; then
	echo "$max">$ofile
	exit 0
fi
echo "probalistically set to fail" >&2
exit 1
