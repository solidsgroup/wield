#!/usr/bin/python
import os
import numpy
os.system("../../bin/main KS_F1.in -DOutFile=outfiles/F1.dat")
THETA = []
GAMMA = []
GAMMAC = []
for theta in numpy.arange(-10,10,0.25):
    print ("theta="+str(theta));
    os.system("../../bin/main KS_F2.in -DRotAxes1=x -DRots1="+str(theta)+" -DOutFile=outfiles/F1_"+str(theta).zfill(3)+".dat")
    DAT = numpy.loadtxt("outfiles/F1_"+str(theta).zfill(3)+".dat")
    gamma = -1
    gammac = -1
    for dat in DAT:
        if abs(dat[0])<1E-8:
            gamma = dat[1]
            gammac = dat[2]
    THETA.append(theta)
    GAMMA.append(gamma)
    GAMMAC.append(gammac)
f = open("outfiles/F2.dat","w");
for theta,gamma,gammac in zip(THETA,GAMMA,GAMMAC):
    f.write(str(theta)+" "+str(gamma)+" "+str(gammac)+"\n");
f.close();
