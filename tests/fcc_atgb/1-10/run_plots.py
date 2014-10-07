#!/usr/bin/python
import os
for theta in range(0,121,5):
    print ("theta="+str(theta));
    os.system("~/LANL_2013/Wield/scripts/plotPolarSurface.py out_"+str(theta)+".dat -o plot_"+str(theta)+".png -m cubic -f facet2d_"+str(theta)+".dat")
    #os.system("../../../scripts/plotPolarSurface.py out_"+str(theta)+".dat -o plot_"+str(theta)+".png -m cubic")

