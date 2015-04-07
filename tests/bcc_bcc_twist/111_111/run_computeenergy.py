#!/usr/bin/python
# 111_111
import os
os.system("../../../bin/main 111_111_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(1,15,1):
    if theta <= 20:
        DR = .01
        DTheta = .25
    else:
        DR=1
        DTheta = 360
    print ("111_111: theta="+str(theta).zfill(3));
    os.system("../../../bin/main 111_111_F2.in -n 6 -DRotAxes1=z -DRotAxes2=z -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat " + "-DDR=" + str(DR) + " -DDTheta="+str(DTheta) )
