#!/usr/bin/python
import os
os.system("../../../bin/main 115_111_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,61,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main 115_111_F2.in -n 8 -DRotAxes1=z -DRotAxes2=z -DRots1="+str(theta/2.)+" -DRots2="+str(-theta/2.)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat")
