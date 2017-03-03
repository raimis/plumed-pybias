#! /bin/bash

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$1 plumed driver --igro ../ala2.gro
