#!/usr/bin/python
import os
os.system("../../../bin/main 110_F1.in -DGammaOR1D=outfiles/F1.dat")
for theta in range(0,181,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main 110_F2.in -n 8 -DGammaSurfaceSphere.PreThetaRotX1="+str(theta/2.)+" -DGammaSurfaceSphere.PreThetaRotX2="+str(-theta/2.)+" -DGammaSurfaceSphere.OutFile=outfiles/F2_"+str(theta)+".dat")