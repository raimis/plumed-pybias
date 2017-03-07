#! /bin/bash

rm -r BIAS FORCE

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$1 plumed driver --igro ../ala2.gro

diff BIAS.ref BIAS || diff FORCE.ref FORCE
