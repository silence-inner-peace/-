#!/bin/sh
dir=`dirname $0`
cd $dir
export CLASSPATH="./bin"
java sequential.SequentialRasterization "$@"

