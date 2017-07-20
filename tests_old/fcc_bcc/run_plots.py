#!/usr/bin/python
import os
for theta in range(-12,13,1):
    print ("theta="+str(theta).zfill(3));
    os.system("python3.2 ~/Research/Wield/scripts/plotPolarSurface.py outfiles/F2_"+str(theta).zfill(3)+".dat -o images/plot_"+str(theta).zfill(3)+".png -m cubic -f facetfiles/F2_"+str(theta).zfill(3)+".dat")

