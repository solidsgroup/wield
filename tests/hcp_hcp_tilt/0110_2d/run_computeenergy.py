#!/usr/bin/python
import os
#os.system("../../../bin/main -n 4 0110_F1_mg.in -DOutFile=outfiles/F1_mg.dat")
os.system("../../../bin/main -n 4 0110_F1_ti.in -DOutFile=outfiles/F1_ti.dat")
#for theta in range(0,91,1):
#    print ("0110: theta="+str(theta).zfill(3));
#    os.system("../../../bin/main 0110_F2.in -n 8 -DRotAxes1=x -DRotAxes2=x -DRots1="+str(theta)+" -DRots2="+str(-theta)+" -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat")
    #os.system("../../../bin/main 0110_F2.in -n 8 -DOutFile=outfiles/F2_"+str(theta).zfill(3)+".dat")
