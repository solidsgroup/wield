import numpy
import pylab

dataA = numpy.loadtxt("graphene_0.1_0.05.out")
dataB = numpy.loadtxt("graphene_0.1_0.1.out")
dataC = numpy.loadtxt("graphene_0.1_0.2.out")

pylab.plot(dataA[:,0],dataA[:,1],label=r"$\varepsilon=0.05$")
pylab.plot(dataB[:,0],dataB[:,1],label=r"$\varepsilon=0.1$")
pylab.plot(dataC[:,0],dataC[:,1],label=r"$\varepsilon=0.2$")
pylab.legend()
pylab.xlim(0,60)
pylab.xlabel(r"$\theta$ (degrees)")
pylab.ylabel(r"$\Sigma$ (thermalized)")
pylab.tight_layout()
pylab.show()
