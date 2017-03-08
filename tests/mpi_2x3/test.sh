#! /bin/bash

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$1 mpirun -n 6 plumed driver --igro ala2.gro --multi 2
