#!/bin/env zsh

cdir=$(pwd)/..
export LD_LIBRARY_PATH=${cdir}:${cdir}/obj:$LD_LIBRARY_PATH

./NtupleProducer \
--file input.txt \
--outfile output \
--tree FlatTree/tree \
--nmax -1 \
--isdata 0 \
--year 2016 \
--sync 1
