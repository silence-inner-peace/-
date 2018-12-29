#!/bin/bash
#SBATCH -p hpxg
#SBATCH -t 00:05:00 
#SBATCH -n 1
#SBATCH -J jobnotok
#SBATCH -o /home/liuyan/test/jobok.stdout
#SBATCH -e /home/liuyan/test/jobok.stderr


sleep 20
echo "tok [`date`]: $USER@`hostname -f`:$0 $1 $2 PID=$$ "
echo "NOT OK" >&2
exit 1
