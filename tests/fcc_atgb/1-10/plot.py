#!/bin/python
from pylab import plot,show,xlabel,ylabel,ylim,legend
from numpy import loadtxt, genfromtxt, linspace, sin, radians

B = 1450;


Relaxed100 = loadtxt("outfiles/F2.dat", delimiter=" ");
plot(Relaxed100[:,0],
     B*Relaxed100[:,1],
     color="black",linewidth=2,linestyle='-',marker="",label='100 Model')
Unrelaxed100 = genfromtxt("outfiles/F1.dat", delimiter=" ");
plot(Unrelaxed100[:,0],
     B*Unrelaxed100[:,1],
     color="black",linewidth=2,linestyle=':',marker="",label='100 Model (Relaxed)')
Wolf = genfromtxt("wolf/wolf.dat", delimiter=" ");
plot(Wolf[:,0],
     Wolf[:,1],
     color="black",linewidth=2,linestyle='--',marker="o",label='MD')

xlabel(r"Inclination angle $\phi$",size=15);
ylabel("Energy",size=15);
#ylim(0,1.2);
legend(loc='upper center',fancybox=True,shadow=True,ncol=2);
show()
