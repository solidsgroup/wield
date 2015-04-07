#!/usr/bin/python
import os
os.system("../../bin/main KS_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(-12,13,1):
    print ("theta="+str(theta));
    os.system("../../bin/main KS_F2.in -n 8 -DRotAxes1=x -DRots1="+str(theta)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat")
