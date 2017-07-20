#!/usr/bin/python
# 114_011
import os
os.system("../../../bin/main 114_011_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,181,5):
    DR = .1
    DTheta = 2
    print ("114_011: theta="+str(theta).zfill(3));
    os.system("../../../bin/main 114_011_F2.in -n 6 -DRotAxes1=z -DRotAxes2=z -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat " + "-DDR=" + str(DR) + " -DDTheta="+str(DTheta) )
