#!/bin/bash
smpicc -O4 sample/roundtrip.c -o roundtrip
smpirun -np 16 -hostfile ./hostfile/cluster_hostfile.txt -platform ./platform/crossbar.xml ./roundtrip
