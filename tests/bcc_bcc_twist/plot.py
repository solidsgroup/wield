#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

#files1=["011.dat", "114_011.dat"]; files2=["Wolf/011.dat","Wolf/114_011.dat"]; print(wield.leastSquares(files1,files2)); exit();


A = 4*(19927.9 - 691.6)
B = 4*(699.38)

Tilt_100_Model  = numpy.loadtxt("011.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("114_011.dat", delimiter=" ");

Tilt_100_Wolf  = numpy.loadtxt("Wolf/011.dat", delimiter=" ");
Tilt_111_Wolf  = numpy.loadtxt("Wolf/114_011.dat", delimiter=" ");

pylab.xlim(0,180);
pylab.ylim(0,1500);
pylab.plot(Tilt_100_Model[:,0],
           A + B*Tilt_100_Model[:,1],color="blue",linewidth=2,linestyle='-',label='011-011 Model')
pylab.plot(180-Tilt_100_Model[:,0],
           A + B*Tilt_100_Model[:,1],color="blue",linewidth=2,linestyle='-')
pylab.plot(Tilt_100_Wolf[:,0],Tilt_100_Wolf[:,1],color="blue",marker='o',linestyle='--',label='011-011 MD')
pylab.plot(Tilt_111_Model[:,0],
           A + B*Tilt_111_Model[:,1],color="green",linewidth=2,linestyle='-',label='114-011 Model')
pylab.plot(180-Tilt_111_Model[:,0],
           A + B*Tilt_111_Model[:,1],color="green",linewidth=2,linestyle='-')
pylab.plot(Tilt_111_Wolf[:,0],Tilt_111_Wolf[:,1],color="green",linewidth=2,marker='o',linestyle='--',label='114-011 MD')

pylab.xlabel("Twist Angle (Degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='lower center',ncol=2);
pylab.show();
