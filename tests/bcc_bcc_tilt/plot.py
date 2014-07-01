#!/usr/bin/python
import pylab
import numpy


A = 2.97817
B = 78.4756

Tilt_001_Model  = numpy.loadtxt("100.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("110.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("112.dat", delimiter=" ");

Tilt_001_Shibuta  = numpy.loadtxt("Shibuta/100.dat", delimiter=" ");
Tilt_110_Shibuta  = numpy.loadtxt("Shibuta/110.dat", delimiter=" ");
Tilt_111_Shibuta  = numpy.loadtxt("Shibuta/111.dat", delimiter=" ");
Tilt_112_Shibuta  = numpy.loadtxt("Shibuta/112.dat", delimiter=" ");

pylab.figure(figsize=(14,9));

pylab.subplot(221)
pylab.xlim(0,90)
pylab.ylim(0,2.0)
pylab.plot(Tilt_001_Model[:,0],
           A + B*Tilt_001_Model[:,1],color="blue",linewidth="2",linestyle='-',label='100 Model')
pylab.plot(Tilt_001_Shibuta[:,0],Tilt_001_Shibuta[:,1],color="blue",linewidth="2",marker='o',linestyle='--',label='100 MD')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='upper left');

pylab.subplot(222)
pylab.xlim(0,180)
pylab.ylim(-0.5,2.0)
pylab.plot(Tilt_110_Model[:,0],
           A + B*Tilt_110_Model[:,1],color="blue",linewidth="2",linestyle='-',label='110 Model')
pylab.plot(Tilt_110_Shibuta[:,0],Tilt_110_Shibuta[:,1],color="blue",linewidth="2",marker='o',linestyle='--',label='110 Model')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='upper left');

pylab.subplot(223)
pylab.xlim(0,60)
pylab.ylim(0,2.0)
pylab.plot(Tilt_111_Model[:,0],
           A + B*Tilt_111_Model[:,1],color="blue",linewidth="2",linestyle='-',label='111 Model')
pylab.plot(Tilt_111_Shibuta[:,0],Tilt_111_Shibuta[:,1],color="blue",linewidth="2",marker='o',linestyle='--',label='111 Model')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='upper left');

pylab.subplot(224)
pylab.xlim(0,110)
pylab.ylim(0,2.0)
pylab.plot(Tilt_112_Model[:,0],
           A + B*Tilt_112_Model[:,1],color="blue",linewidth="2",linestyle='-',label='112 Model')
pylab.plot(Tilt_112_Shibuta[:,0],Tilt_112_Shibuta[:,1],color="blue",linewidth="2",marker='o',linestyle='--',label='112 Model')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='upper left');

pylab.tight_layout();
pylab.show();

