#!/usr/bin/python
import os
os.system("../../../bin/main 111_F1.in -DGammaInterface1D.OutFile=outfiles/F1.dat")
for theta in range(0,91,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main 111_F2.in -n 8 -- -DGammaSurfaceSphere.PreThetaRotZ1="+str(theta/2.)+" -DGammaSurfaceSphere.PreThetaRotZ2="+str(-theta/2.)+" -DGammaSurfaceSphere.OutFile=outfiles/F2_"+str(theta)+".dat")
