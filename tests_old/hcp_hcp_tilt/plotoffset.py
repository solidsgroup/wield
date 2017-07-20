#!/usr/bin/python3.2
import numpy
import pylab

data = numpy.loadtxt("offset.dat",delimiter=' ')
x = data[:,0]; y = data[:,1]; 
X,Y = numpy.meshgrid(x,y);

pylab.pcolor(X,Y,data[:,3].reshape(11,11))
pylab.show()

