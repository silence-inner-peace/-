#!/bin/bash
#SBATCH -p hpxg
#SBATCH -t 00:05:00 
#SBATCH -n 1
#SBATCH -J checker
#SBATCH -o /data/%u/test/workflow/log/%x.%j.stdout
#SBATCH -e /data/%u/test/workflow/log/%x.%j.stderr

echo "START[`date`]: $USER@`hostname -f`: PID=$$ "

ddir=/data/$USER/test/workflow/data
s=""
e=""
for i in `seq 10`
do
	if [ -f "$ddir/max$i" ]; then 
		s="$s $i"
	else
		e="$e $i"
	fi
done
echo "datamax $s succeeded; $e failed."

echo "END[`date`]"

exit 0

