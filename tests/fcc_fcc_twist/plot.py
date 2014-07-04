#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

#files1=["100.dat"]; files2=["Wolf/100.dat"]; print(wield.leastSquares(files1,files2)); files1=["111.dat"]; files2=["Wolf/111.dat"]; print(wield.leastSquares(files1,files2)); exit(); 

#print(wield.leastSquares(["100.dat"],["Wolf/100.dat"])); exit();

A1 = 18000 * 0.0527911
B1 = 18000
A2 = A1 #717.3
B2 = B1 #10759.8

Tilt_100_Model  = numpy.loadtxt("100.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111.dat", delimiter=" ");

Tilt_100_Wolf  = numpy.loadtxt("Wolf/100.dat", delimiter=" ");
Tilt_111_Wolf  = numpy.loadtxt("Wolf/111.dat", delimiter=" ");

pylab.xlim(0,90);
pylab.ylim(0,800);
pylab.plot(Tilt_100_Model[:,0],
           A1 + B1*Tilt_100_Model[:,1],color="blue",linewidth=2,linestyle='-',label='100 Model')
pylab.plot(Tilt_100_Wolf[:,0],Tilt_100_Wolf[:,1],color="blue",marker='o',linestyle='--',label='100 MD')
pylab.plot(Tilt_111_Model[:,0],
           A2 + B2*Tilt_111_Model[:,1],color="green",linewidth=2,linestyle='-',label='111 Model')
pylab.plot(Tilt_111_Wolf[:,0],Tilt_111_Wolf[:,1],color="green",linewidth=2,marker='o',linestyle='--',label='111 MD')

pylab.xlabel("Twist Angle (Degrees)");
pylab.ylabel("Energy");
pylab.legend(loc='upper left');
pylab.show();

