#!/bin/bash

jdatagen=`sbatch datagen.sh | awk '{print $NF}'`
echo "datagen: $jdatagen"
jdatamaxlist=""
for i in `seq 10`
do
	j=`sbatch --dependency=afterok:$jdatagen datamax$i.sh | awk '{print $NF}'`
	jdatamaxlist="$jdatamaxlist:$j"
done
echo "datamax: $jdatamaxlist"
jglobalmax=`sbatch --dependency=afterany$jdatamaxlist globalmax.sh | awk '{print $NF}'`
echo "globalmax: $jglobalmax"
jcheck=`sbatch --dependency=afternotok$jdatamaxlist checker.sh | awk '{print $NF}'`
echo "checker: $jcheck"

	
