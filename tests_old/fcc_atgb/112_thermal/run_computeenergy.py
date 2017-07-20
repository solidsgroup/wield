#!/usr/bin/python
#raise("Dataset already computed--do not run again")
import os
os.system("../../../bin/main 112_F1.in -DOutFile=outfiles/F1.dat")
for theta in range(0,91,1):
    print ("theta="+str(theta));
    os.system("../../../bin/main 112_F2.in -n 8 -DRotAxes1=x -DRotAxes2=x -DRots1="+str(theta)+" -DRots2="+str(theta)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat")
