#!/usr/bin/python
import os
for theta in range(95,181,5):
    print ("theta="+str(theta));
    os.system("../../../scripts/plotPolarSurface.py out_"+str(theta)+".dat -o plot_"+str(theta)+".png -m cubic -f facet_"+str(theta)+".dat")

