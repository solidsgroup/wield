#!/usr/bin/python
# 031_031
#raise("Stop! Danger Will Robinson!")
import os
os.system("../../../bin/main 031_031_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,1,1):
    if theta == 0:
        DR = .01
        DTheta = .25
    elif theta < 20 or theta > 175:
        DR = .025
        DTheta = 1
    else:
        DR = 0.05
        DTheta = 1
    print ("031_031: theta="+str(theta).zfill(3));
    os.system("../../../bin/main 031_031_F2.in -n 6 -DRotAxes1=z -DRotAxes2=z -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat " + "-DDR=" + str(DR) + " -DDTheta="+str(DTheta) )
