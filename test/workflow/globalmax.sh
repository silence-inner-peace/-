#!/bin/bash
#SBATCH -p hpxg
#SBATCH -t 00:05:00 
#SBATCH -n 1
#SBATCH -J globalmax
#SBATCH -o /data/%u/test/workflow/log/%x.%j.stdout
#SBATCH -e /data/%u/test/workflow/log/%x.%j.stderr

echo "START[`date`]: $USER@`hostname -f`: PID=$$ "

ddir=/data/$USER/test/workflow/data
max=`cat $ddir/max* |sort -n -r|head -n 1` 
echo "GLOBAL MAX IS $max"

echo "END[`date`]"

exit 0

