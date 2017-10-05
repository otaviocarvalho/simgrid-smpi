#!/bin/bash
SIMGRID_BIN=~/simgrid/SimGrid-3.13/bin

#$SIMGRID_BIN/smpirun -np $1 -hostfile ../../../hostfile/cluster_hostfile.txt \
#-platform ../../../platform/crossbar.xml ./julia_set $2 \
#--cfg=smpi/running-power:1 \
#--cfg=smpi/privatize-global-variables:yes

smpirun -np $1 -hostfile ../../../hostfile/cluster_hostfile.txt \
-platform ../../../platform/crossbar.xml ./julia_set $2 \
--cfg=smpi/running-power:1 \
--cfg=smpi/privatize-global-variables:yes

#mpirun -np $1 valgrind --show-leak-kinds=all --leak-check=full ./julia_set $2

#mpirun -np $1 ./julia_set $2

