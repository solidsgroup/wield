#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

#files1=["011.dat"]; files2=["Wolf/011.dat"]; print(wield.leastSquares(files1,files2)); files1=["114_011.dat"]; files2=["Wolf/114_011.dat"]; print(wield.leastSquares(files1,files2)); exit();




Tilt_001_Model  = numpy.loadtxt("001.dat", delimiter=" ");
Tilt_011_Model  = numpy.loadtxt("011.dat", delimiter=" ");
Tilt_031_Model  = numpy.loadtxt("031.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("112.dat", delimiter=" ");

Tilt_001_Wolf  = numpy.loadtxt("Wolf/001.dat", delimiter=" ");
Tilt_011_Wolf  = numpy.loadtxt("Wolf/011.dat", delimiter=" ");
Tilt_031_Wolf  = numpy.loadtxt("Wolf/031.dat", delimiter=" ");
Tilt_111_Wolf  = numpy.loadtxt("Wolf/111.dat", delimiter=" ");
Tilt_112_Wolf  = numpy.loadtxt("Wolf/112.dat", delimiter=" ");

#[A, B] = wield.leastSquares(["001.dat","011.dat","031.dat","112.dat"], ["Wolf/001.dat","Wolf/011.dat","Wolf/031.dat","Wolf/112.dat"]);
#print(wield.leastSquares(["001.dat"], ["Wolf/001.dat"])); exit();

A = 2145.89
B = 38073.25

pylab.figure(figsize=(14,7));

pylab.subplot(221)
pylab.xlim(0,90)
pylab.ylim(0,1800)
pylab.plot(Tilt_001_Model[:,0],
           A + B*Tilt_001_Model[:,1],color="blue",linewidth=2,linestyle='-',label="001 Model")
pylab.plot(Tilt_001_Wolf[:,0],Tilt_001_Wolf[:,1],color="blue",marker='o',linestyle='--',label="001 MD")
pylab.legend(loc='lower center',ncol=2);
pylab.xlabel("Twist Angle (Degrees)");
pylab.ylabel("Energy");

pylab.subplot(222)
pylab.xlim(0,180)
pylab.ylim(0,1800)
pylab.plot(Tilt_011_Model[:,0],
           A + B*Tilt_011_Model[:,1],color="blue",linewidth=2,linestyle='-',label="011 Model")
pylab.plot(Tilt_011_Wolf[:,0],Tilt_011_Wolf[:,1],color="blue",linewidth=2,marker='o',linestyle='--',label='011 MD')
pylab.legend(loc='lower center',ncol=2);
pylab.xlabel("Twist Angle (Degrees)");
pylab.ylabel("Energy");

pylab.subplot(223)
pylab.xlim(0,180)
pylab.ylim(0,1800)
pylab.plot(Tilt_031_Model[:,0],
           A + B*Tilt_031_Model[:,1],color="blue",linewidth=2,linestyle='-',label="031 Model")
pylab.plot(Tilt_031_Wolf[:,0],Tilt_031_Wolf[:,1],color="blue",linewidth=2,marker='o',linestyle='--',label='031 MD')
pylab.legend(loc='lower center',ncol=2);
pylab.xlabel("Twist Angle (Degrees)");
pylab.ylabel("Energy");

pylab.subplot(224)
pylab.xlim(0,180)
pylab.ylim(0,1800)
pylab.plot(Tilt_112_Model[:,0],
           A + B*Tilt_112_Model[:,1],color="blue",linewidth=2,linestyle='-',label="112 Model")
pylab.plot(Tilt_112_Wolf[:,0],Tilt_112_Wolf[:,1],color="blue",linewidth=2,marker='o',linestyle='--',label='112 MD')
pylab.legend(loc='lower center',ncol=2);
pylab.xlabel("Twist Angle (Degrees)");
pylab.ylabel("Energy");


pylab.tight_layout();
pylab.show();

