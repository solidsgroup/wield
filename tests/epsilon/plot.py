#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

#files1=["100.dat"]; files2=["Wolf/100.dat"]; print(wield.leastSquares(files1,files2)); files1=["111.dat"]; files2=["Wolf/111.dat"]; print(wield.leastSquares(files1,files2)); exit(); 

#print(wield.leastSquares(["100.dat"],["Wolf/100.dat"])); exit();

pylab.figure(figsize=(10*8/10,8*8/10));

A=.0490/0.0244991;
B=1/0.0244991;

Stdev_0_100  = numpy.loadtxt("100_0.1.dat", delimiter=" ");
Stdev_0_050  = numpy.loadtxt("100_0.05.dat", delimiter=" ");
Stdev_0_010  = numpy.loadtxt("100_0.01.dat", delimiter=" ");
Stdev_0_001  = numpy.loadtxt("100_0.001.dat", delimiter=" ");

pylab.plot(Stdev_0_100[:,0], A + B*Stdev_0_100[:,1],color="black",linewidth=2,linestyle='-',label='$\epsilon=0.1$')
pylab.plot(Stdev_0_050[:,0], A + B*Stdev_0_050[:,1],color="black",linewidth=2,linestyle='--',label='$\epsilon=0.05$')
pylab.plot(Stdev_0_010[:,0], A + B*Stdev_0_010[:,1],color="black",linewidth=2,linestyle='-.',label='$\epsilon=0.01$')
pylab.plot(Stdev_0_001[:,0], A + B*Stdev_0_001[:,1],color="black",linewidth=2,linestyle=':',label='$\epsilon=0.001$')

Stdev_0_100[:,0] = -Stdev_0_100[:,0];
Stdev_0_050[:,0] = -Stdev_0_050[:,0];
Stdev_0_010[:,0] = -Stdev_0_010[:,0];
Stdev_0_001[:,0] = -Stdev_0_001[:,0];

pylab.plot(Stdev_0_100[:,0], A + B*Stdev_0_100[:,1],color="black",linewidth=2,linestyle='-');
pylab.plot(Stdev_0_050[:,0], A + B*Stdev_0_050[:,1],color="black",linewidth=2,linestyle='--');
pylab.plot(Stdev_0_010[:,0], A + B*Stdev_0_010[:,1],color="black",linewidth=2,linestyle='-.');
pylab.plot(Stdev_0_001[:,0], A + B*Stdev_0_001[:,1],color="black",linewidth=2,linestyle=':');


pylab.xlim(-2,10);

pylab.xlabel("Tilt Angle (Degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='lower right',fancybox=True,shadow=True);
pylab.tight_layout();
pylab.show();

