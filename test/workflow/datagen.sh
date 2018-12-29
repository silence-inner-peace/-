#!/bin/bash
#SBATCH -p hpxg
#SBATCH -t 00:05:00 
#SBATCH -n 1
#SBATCH -J datagen
#SBATCH -o /data/%u/test/workflow/log/%x.%j.stdout
#SBATCH -e /data/%u/test/workflow/log/%x.%j.stderr

echo "START[`date`]: $USER@`hostname -f`: PID=$$ "

ddir=/data/$USER/test/workflow/data
mkdir -p $ddir

for i in `seq 10`
do
	dfile=$ddir/input$i
	echo $RANDOM>$dfile
	for j in `seq 999`
	do
		echo $RANDOM>>$dfile
	done
done

echo "END[`date`]"

sleep 5
exit 0

