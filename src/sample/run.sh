#!/bin/bash
SIMGRID_BIN=~/simgrid/SimGrid-3.13/bin
$SIMGRID_BIN/smpicc -O4 roundtrip.c -o roundtrip
$SIMGRID_BIN/smpirun -np 2 -hostfile ../../hostfile/cluster_hostfile.txt -platform ../../platform/crossbar.xml ./roundtrip
