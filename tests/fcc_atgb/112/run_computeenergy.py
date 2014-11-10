#!/usr/bin/python
import os
os.system("../../../bin/main 112_F1.in -DEnergyInterface1D.OutFile=outfiles/F1.dat")
for theta in range(0,91,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main 112_F2.in -n 8 -- -DEnergySurfaceSphere.PrePhiRotX="+str(theta)+" -DEnergySurfaceSphere.OutFile=outfiles/F2_"+str(theta)+".dat")
