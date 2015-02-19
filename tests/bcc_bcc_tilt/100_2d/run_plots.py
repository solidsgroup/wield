import os
for theta in range(0,91,5):
    print ("100: theta="+str(theta).zfill(3));
    os.system("python ~/Wield/scripts/plotPolarSurface.py outfiles/F2_"+str(theta).zfill(3)+".dat -o images/plot_"+str(theta).zfill(3)+".png -m cubic -f facetfiles/F2_"+str(theta).zfill(3)+".dat")

