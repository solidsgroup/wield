#!/usr/bin/python
import scipy.interpolate
import scipy.integrate
import numpy

def leastSquares(files1, files2):
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

    if (len(files1) != len(files2)):
        raise RuntimeError("Lists of files not the same size!");

    F1 = []
    F2 = []
    for f1,f2 in zip(files1,files2):
        F1.append(numpy.loadtxt(f1,delimiter=" "));
        F2.append(numpy.loadtxt(f2,delimiter=" "));

    a=0; b=0; c=0; d=0; e=0; f=0;
    for f1,f2 in zip(F1,F2):
        a += integrateNoFunctions(f1,f2);
        b += integrateOneFunction(f1);
        c  = b;
        d += integrateTwoFunctions(f1,f1);
        e += integrateOneFunction(f2);
        f += integrateTwoFunctions(f1,f2);

    A = (+ d*e - b*f)/(a*d - b*c);
    B = (- c*e + a*f)/(a*d - b*c);
    
    return [A,B];

