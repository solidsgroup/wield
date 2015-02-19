#!/usr/bin/python
#raise("danger--plots have already been generated!")
import os
for theta in range(0,91,5):
    print ("theta="+str(theta));
    #os.system("~/LANL_2013/Wield/scripts/plotPolarSurface.py out_"+str(theta)+".dat -o plot_"+str(theta)+".png -m cubic -f facet_"+str(theta)+".dat")
    os.system("/usr/local/bin/python3.4 ../../../scripts/plotPolarSurface.py outfiles/F2_"+str(theta).zfill(3)+".dat -o images/plot_"+str(theta).zfill(3)+".png -f facetfiles/F2_"+str(theta).zfill(3)+".dat -c")

