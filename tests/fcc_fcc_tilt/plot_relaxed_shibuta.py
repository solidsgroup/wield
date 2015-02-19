#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy


#files1=["100.dat", "110.dat", "111.dat", "112.dat"]; files2=["Shibuta/100.dat","Shibuta/110.dat","Shibuta/111.dat","Shibuta/112.dat"]; print(wield.leastSquares(files1,files2)); exit();

#A = 3.4234 # 2.9799  #140*0.0384929
#B = 64.2913 # 61.7148 #140
A = 0
B = 2.5


Tilt_001_Model  = numpy.loadtxt("100_2d/outfiles/F1.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("110_2d/outfiles/F1.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111_2d/outfiles/F1.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("112_2d/outfiles/F1.dat", delimiter=" ");

Tilt_001_Model_Relaxed  = numpy.loadtxt("100_2d/outfiles/F2.dat", delimiter=" ");
Tilt_110_Model_Relaxed  = numpy.loadtxt("110_2d/outfiles/F2.dat", delimiter=" ");
Tilt_111_Model_Relaxed  = numpy.loadtxt("111_2d/outfiles/F2.dat", delimiter=" ");
Tilt_112_Model_Relaxed  = numpy.loadtxt("112_2d/outfiles/F2.dat", delimiter=" ");

Tilt_001_Shibuta  = numpy.loadtxt("Shibuta/100.dat", delimiter=" ");
Tilt_110_Shibuta  = numpy.loadtxt("Shibuta/110.dat", delimiter=" ");
Tilt_111_Shibuta  = numpy.loadtxt("Shibuta/111.dat", delimiter=" ");
Tilt_112_Shibuta  = numpy.loadtxt("Shibuta/112.dat", delimiter=" ");

#pylab.figure(figsize=(14,7));
pylab.figure(figsize=(14*16/14,7*16/14));

pylab.subplot(221)
pylab.xlim(0,90)
pylab.ylim(0,2.0)
pylab.plot(Tilt_001_Model[:,0],
           A + B*Tilt_001_Model[:,1],color="black",linewidth=2,linestyle=':',label='100 Model')
pylab.plot(Tilt_001_Model_Relaxed[:,0],
           A + B*Tilt_001_Model_Relaxed[:,1],color="black",linewidth=2,linestyle='-',label='100 Model (Relaxed)')
pylab.plot(Tilt_001_Shibuta[:,0],Tilt_001_Shibuta[:,1],color="black",linewidth=2,marker='o',linestyle='--',label='100 MD')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=3);

pylab.subplot(222)
pylab.xlim(0,180)
pylab.ylim(0,2.0)
pylab.plot(Tilt_110_Model[:,0],
           A + B*Tilt_110_Model[:,1],color="black",linewidth=2,linestyle=':',label='110 Model')
pylab.plot(Tilt_110_Model_Relaxed[:,0],
           A + B*Tilt_110_Model_Relaxed[:,1],color="black",linewidth=2,linestyle='-',label='110 Model (Relaxed)')
pylab.plot(Tilt_110_Shibuta[:,0],Tilt_110_Shibuta[:,1],color="black",linewidth=2,marker='o',linestyle='--',label='110 MD')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=3);

pylab.subplot(223)
pylab.xlim(0,60)
pylab.ylim(0,2.0)
pylab.plot(Tilt_111_Model[:,0],
           A + B*Tilt_111_Model[:,1],color="black",linewidth=2,linestyle=':',label='111 Model')
pylab.plot(Tilt_111_Model_Relaxed[:,0],
           A + B*Tilt_111_Model_Relaxed[:,1],color="black",linewidth=2,linestyle='-',label='111 Model (Relaxed)')
pylab.plot(Tilt_111_Shibuta[:,0],Tilt_111_Shibuta[:,1],color="black",linewidth=2,marker='o',linestyle='--',label='111 MD')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=3);

pylab.subplot(224)
pylab.xlim(0,110)
pylab.ylim(0,2.0)
pylab.plot(Tilt_112_Model[:,0],
           A + B*Tilt_112_Model[:,1],color="black",linewidth=2,linestyle=':',label='112 Model')
pylab.plot(Tilt_112_Model_Relaxed[:,0],
           A + B*Tilt_112_Model_Relaxed[:,1],color="black",linewidth=2,linestyle='-',label='112 Model (Relaxed)')
pylab.plot(Tilt_112_Shibuta[:,0],Tilt_112_Shibuta[:,1],color="black",linewidth=2,marker='o',linestyle='--',label='112 MD')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=3);

pylab.tight_layout();
pylab.show();

