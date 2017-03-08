#! /bin/bash

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$1 mpirun -n 3 plumed driver --igro ala2.gro
