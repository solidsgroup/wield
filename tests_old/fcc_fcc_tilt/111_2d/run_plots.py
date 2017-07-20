#!/usr/bin/python
import os
for theta in range(0,61,1):
    print ("111: theta="+str(theta).zfill(3));
    os.system("../../../scripts/plotPolarSurface.py outfiles/out_"+str(theta).zfill(3)+".dat -o images/plot_"+str(theta).zfill(3)+".png -m cubic")

