#!/bin/bash
# do dummy work for the time specified, default to 10 seconds
# this script actually consumers CPU time, not just sleeping
# LIMITED for training use ONLY
i=0 # task id
[ ! -z "$1" ] && i=$1
T=10 # time to run, in seconds
[ ! -z "$2" ] && T=$2
m=$HOSTNAME
p=$SLURM_PROCID
n=$SLURM_NODEID
w=`whoami`
echo "[`date`] START: task $i for $T seconds on node $n ($m) processor $p"
t1=`date +%s`
t=0
while [ $t -lt $T ]
do
    #dummyout=`echo "s($RANDOM + 1) - c($RANDOM +3) + e(l($RANDOM+1))" |bc -l`
    dummyout=`expr 1 \+ 2 \* 1000`
    t2=`date +%s`
    t=`expr $t2 \- $t1`
done
echo "[`date`] END: task $i for $T seconds on node $n ($m) processor $p. actual time: $t seconds."

