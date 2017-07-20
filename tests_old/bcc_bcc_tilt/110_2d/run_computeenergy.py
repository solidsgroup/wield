#!/usr/bin/python
import os
os.system("../../../bin/main 110_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,181,1):
    if theta >= 175 :
        DR = 0.025
        DTheta = .5
    else:
        DR = 1
        DTheta = 360
    print ("110: theta="+str(theta).zfill(3));
    os.system("../../../bin/main 110_F2.in -n 8 -DRotAxes1=x -DRotAxes2=x -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat " + "-DDR=" + str(DR) + " -DDTheta="+str(DTheta) )
