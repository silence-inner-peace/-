#!/bin/bash
#SBATCH -p hpxg
#SBATCH -t 00:05:00 
#SBATCH -n 1
#SBATCH -J jobok
#SBATCH -o /home/liuyan/test/jobok.stdout
#SBATCH -e /home/liuyan/test/jobok.stderr


sleep 20
echo "tok [`date`]: $USER@`hostname -f`:$0 $1 $2 PID=$$ "

exit 0
