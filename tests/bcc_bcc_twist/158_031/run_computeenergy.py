#!/usr/bin/python
# 158_031
raise("danger will robinson")
import os
os.system("../../../bin/main 158_031_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,181,1):
    DR = .025
    DTheta = 1
    print ("158_031: theta="+str(theta).zfill(3));
    os.system("../../../bin/main 158_031_F2.in -n 6 -DRotAxes1=z -DRotAxes2=z -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat " + "-DDR=" + str(DR) + " -DDTheta="+str(DTheta) )
