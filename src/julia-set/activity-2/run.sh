#!/bin/bash
SIMGRID_BIN=~/simgrid/SimGrid-3.13/bin

#valgrind --leak-check=yes $SIMGRID_BIN/smpirun -np $1 -hostfile ../../../hostfile/cluster_hostfile.txt \
$SIMGRID_BIN/smpirun -np $1 -hostfile ../../../hostfile/cluster_hostfile.txt \
-platform ../../../platform/crossbar.xml ./julia_set $2 \
--cfg=smpi/running-power:1
