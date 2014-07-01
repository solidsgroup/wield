#!/usr/bin/python
import scipy.interpolate
import scipy.integrate
import numpy
#from numpy import loadtxt

def integrateNoFunctions(f,g):
    MIN = max(f[:,0].min(),g[:,0].min());
    MAX = min(f[:,0].max(),g[:,0].max());
    return 1;

def integrateOneFunction(f):
    MIN = f[:,0].min();
    MAX = f[:,0].max();
    F = scipy.interpolate.interp1d(f[:,0],f[:,1]);
    return scipy.integrate.quad(F,MIN,MAX)[0] / (MAX-MIN);

def integrateTwoFunctions(f,g):
    MIN = max(f[:,0].min(),g[:,0].min());
    MAX = min(f[:,0].max(),g[:,0].max());
    F = scipy.interpolate.interp1d(f[:,0],f[:,1]);
    G = scipy.interpolate.interp1d(g[:,0],g[:,1]);
    FG = lambda x: F(x) * G(x);
    return scipy.integrate.quad(FG,MIN,MAX)[0] / (MAX-MIN);


Tilt_001_Model  = numpy.loadtxt("100.dat", delimiter=" ");
Tilt_001_Shibuta = numpy.loadtxt("Shibuta/100.dat", delimiter=" ");

Tilt_110_Model  = numpy.loadtxt("110.dat", delimiter=" ");
Tilt_110_Shibuta = numpy.loadtxt("Shibuta/110.dat", delimiter=" ");

Tilt_111_Model  = numpy.loadtxt("111.dat", delimiter=" ");
Tilt_111_Shibuta = numpy.loadtxt("Shibuta/111.dat", delimiter=" ");

Tilt_112_Model  = numpy.loadtxt("112.dat", delimiter=" ");
Tilt_112_Shibuta = numpy.loadtxt("Shibuta/112.dat", delimiter=" ");


a = integrateNoFunctions(Tilt_001_Model,Tilt_001_Shibuta) + \
    integrateNoFunctions(Tilt_110_Model,Tilt_110_Shibuta) + \
    integrateNoFunctions(Tilt_111_Model,Tilt_111_Shibuta) + \
    integrateNoFunctions(Tilt_112_Model,Tilt_112_Shibuta);
b = integrateOneFunction(Tilt_001_Model) + \
    integrateOneFunction(Tilt_110_Model) + \
    integrateOneFunction(Tilt_111_Model) + \
    integrateOneFunction(Tilt_112_Model);
c = b;
d = integrateTwoFunctions(Tilt_001_Model,Tilt_001_Model) + \
    integrateTwoFunctions(Tilt_110_Model,Tilt_110_Model) + \
    integrateTwoFunctions(Tilt_111_Model,Tilt_111_Model) + \
    integrateTwoFunctions(Tilt_112_Model,Tilt_112_Model);
e = integrateOneFunction(Tilt_001_Shibuta) + \
    integrateOneFunction(Tilt_110_Shibuta) + \
    integrateOneFunction(Tilt_111_Shibuta) + \
    integrateOneFunction(Tilt_112_Shibuta);
f = integrateTwoFunctions(Tilt_001_Model,Tilt_001_Shibuta) + \
    integrateTwoFunctions(Tilt_110_Model,Tilt_110_Shibuta) + \
    integrateTwoFunctions(Tilt_111_Model,Tilt_111_Shibuta) + \
    integrateTwoFunctions(Tilt_112_Model,Tilt_112_Shibuta);

A = (+ d*e - b*f)/(a*d - b*c);
B = (- c*e + a*f)/(a*d - b*c);

print(A," ",B)

# print(Theta);

