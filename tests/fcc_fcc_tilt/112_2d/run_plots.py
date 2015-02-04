#!/usr/bin/python
import os
for theta in range(0,111,1):
    print ("112: theta="+str(theta).zfill(3));
    os.system("../../../scripts/plotPolarSurface.py outfiles/out_"+str(theta).zfill(3)+".dat -o images/plot_"+str(theta).zfill(3)+".png -m cubic")

