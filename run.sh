#!/bin/bash

METRICA="FLOPS_DP"
CPU=3

make
likwid-perfctr -C ${CPU} -g "FLOPS_DP" -m ./perfEG > LikwidFlops.log
