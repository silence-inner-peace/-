#!/bin/bash

function getpi()
{
	num_steps=$1
	step=`echo "1.0/ $num_steps"|bc -l`
	sum=0
	for i in `seq $num_steps`
	do
		x=`echo "($i-1+0.5)*$step"|bc -l`
		sum=`echo "$sum + 4.0/(1.0+$x*$x)" | bc  -l`
	done
	pi=`echo "$step * $sum"|bc -l`
	echo $pi
}

getpi $1
