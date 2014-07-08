#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

Sigma_0_5  = numpy.loadtxt("100_0.5.dat", delimiter=" ");
Sigma_0_4  = numpy.loadtxt("100_0.4.dat", delimiter=" ");
Sigma_0_35  = numpy.loadtxt("100_0.35.dat", delimiter=" ");
Sigma_0_3  = numpy.loadtxt("100_0.3.dat", delimiter=" ");
Sigma_0_25  = numpy.loadtxt("100_0.25.dat", delimiter=" ");
Sigma_0_2  = numpy.loadtxt("100_0.2.dat", delimiter=" ");
Sigma_0_15  = numpy.loadtxt("100_0.15.dat", delimiter=" ");
Sigma_0_1  = numpy.loadtxt("100_0.1.dat", delimiter=" ");

pylab.plot(Sigma_0_5[:,0], (Sigma_0_5[:,1] - min(Sigma_0_5[:,1]))/(max(Sigma_0_5[:,1])-min(Sigma_0_5[:,1])),color="red",linewidth=2,linestyle='-',label='$\sigma=0.5\alpha$')
pylab.plot(Sigma_0_4[:,0], (Sigma_0_4[:,1] - min(Sigma_0_4[:,1]))/(max(Sigma_0_4[:,1])-min(Sigma_0_4[:,1])),color="yellow",linewidth=2,linestyle='-',label='$\sigma=0.40\alpha$')
pylab.plot(Sigma_0_35[:,0], (Sigma_0_35[:,1] - min(Sigma_0_35[:,1]))/(max(Sigma_0_35[:,1])-min(Sigma_0_35[:,1])),color="blue",linewidth=2,linestyle='-',label='$\sigma=0.35\alpha$')
pylab.plot(Sigma_0_3[:,0], (Sigma_0_3[:,1] - min(Sigma_0_3[:,1]))/(max(Sigma_0_3[:,1])-min(Sigma_0_3[:,1])),color="turquoise",linewidth=2,linestyle='-',label='$\sigma=0.30\alpha$')
pylab.plot(Sigma_0_25[:,0], (Sigma_0_25[:,1] - min(Sigma_0_25[:,1]))/(max(Sigma_0_25[:,1])-min(Sigma_0_25[:,1])),color="green",linewidth=2,linestyle='-',label='$\sigma=0.25\alpha$')
pylab.plot(Sigma_0_2[:,0], (Sigma_0_2[:,1] - min(Sigma_0_2[:,1]))/(max(Sigma_0_2[:,1])-min(Sigma_0_2[:,1])),color="gray",linewidth=2,linestyle='-',label='$\sigma=0.20\alpha$')
pylab.plot(Sigma_0_15[:,0], (Sigma_0_15[:,1] - min(Sigma_0_15[:,1]))/(max(Sigma_0_15[:,1])-min(Sigma_0_15[:,1])),color="purple",linewidth=2,linestyle='-',label='$\sigma=0.15\alpha$')
pylab.plot(Sigma_0_1[:,0], (Sigma_0_1[:,1] - min(Sigma_0_1[:,1]))/(max(Sigma_0_1[:,1])-min(Sigma_0_1[:,1])),color="black",linewidth=2,linestyle='-',label='$\sigma=0.10\alpha$')


#pylab.xlim(-2,10);

pylab.xlabel("Tilt Angle (Degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='lower right',fancybox=True,shadow=True);
pylab.show();

