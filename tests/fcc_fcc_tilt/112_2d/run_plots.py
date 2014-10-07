#!/usr/bin/python
import os
for theta in range(0,181,5):
    print ("theta="+str(theta));
    #os.system("~/LANL_2013/Wield/scripts/plotPolarSurface.py outfiles/out_"+str(theta)+".dat -o images/plot_"+str(theta)+".png -m cubic -f facet_"+str(theta)+".dat")
    os.system("../../../scripts/plotPolarSurface.py outfiles/out_"+str(theta)+".dat -o images/plot_"+str(theta)+".png -m cubic")

