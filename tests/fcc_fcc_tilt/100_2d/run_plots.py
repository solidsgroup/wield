#!/usr/bin/python
import os
for theta in range(0,91,1):
    print ("100: theta="+str(theta).zfill(3));
    os.system("python ~/LANL_2013/Wield/scripts/plotPolarSurface.py outfiles/F2_"+str(theta).zfill(3)+".dat -o images/plot_"+str(theta).zfill(3)+".png -m cubic -f facetfiles/F2_"+str(theta).zfill(3)+".dat")

