#!/bin/python
from pylab import plot,show,xlabel,xlim,ylabel,ylim,legend
from numpy import loadtxt, genfromtxt

B = 20000;

Unrelaxed100 = genfromtxt("outfiles/F1.dat", delimiter=" ");
plot(Unrelaxed100[:,0],
     B*Unrelaxed100[:,1],
     color="black",linewidth=2,linestyle=':',marker="",label='Unrelaxed')
Wolf = genfromtxt("wolf/100.dat", delimiter=" ");
plot(Wolf[:,0],
     Wolf[:,1],
     color="black",linewidth=2,linestyle='--',marker="o",label='MD')
Relaxed100 = loadtxt("outfiles/F2.dat", delimiter=" ");
plot(Relaxed100[:,0],
     B*Relaxed100[:,1],
     color="black",linewidth=2,linestyle='-',marker="",label='2F Relaxation')

xlabel(r"Interface tilt angle $\phi$",size=15);
ylabel("Energy",size=15);
xlim(0,90)
ylim(0,1000);
legend(loc='upper center',fancybox=True,shadow=True,ncol=2);
show()
