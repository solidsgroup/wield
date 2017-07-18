#!/bin/bash
./bin/main -n 4 $1
python3 ./scripts/plotPolarSurface.py results/drexel_s3.dat -o results/myoutput.png
