#!/usr/bin/python
import os
os.system("../../../bin/main 100_F1.in -DEnergyInterface1D.OutFile=outfiles/F1.dat")
for theta in range(0,91,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main 100_F2.in -n 8 -- -DEnergySurfaceSphere.PreThetaRotZ1="+str(theta/2.)+" -DEnergySurfaceSphere.PreThetaRotZ2="+str(-theta/2.)+" -DEnergySurfaceSphere.OutFile=outfiles/F2_"+str(theta)+".dat")
