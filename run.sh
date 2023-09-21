#!/bin/bash

make
likwid-perfctr -C 0-3 -g "FLOPS_DP" -m ./perfEG > LikwidFlops.log
