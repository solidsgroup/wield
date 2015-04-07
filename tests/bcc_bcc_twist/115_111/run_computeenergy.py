#!/usr/bin/python
# 115_111
raise("danger will robinson")
import os
os.system("../../../bin/main 115_111_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,61,1):
    DR = .01
    DTheta = 1
    print ("115_111: theta="+str(theta).zfill(3));
    os.system("../../../bin/main 115_111_F2.in -n 6 -DRotAxes1=z -DRotAxes2=z -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat " + "-DDR=" + str(DR) + " -DDTheta="+str(DTheta) )
