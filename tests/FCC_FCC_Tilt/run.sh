#!/bin/bash

./bin/Main tests/FCC_FCC_Tilt/fcc_fcc_tilt_100.in -DDISTRIBUTION $1 
./bin/Main tests/FCC_FCC_Tilt/fcc_fcc_tilt_110.in -DDISTRIBUTION $1
./bin/Main tests/FCC_FCC_Tilt/fcc_fcc_tilt_111.in -DDISTRIBUTION $1
./bin/Main tests/FCC_FCC_Tilt/fcc_fcc_tilt_112.in -DDISTRIBUTION $1
