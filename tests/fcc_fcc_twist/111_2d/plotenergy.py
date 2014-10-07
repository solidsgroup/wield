#!/bin/python
from pylab import plot,show,xlabel,ylabel,ylim,legend
from numpy import loadtxt, genfromtxt

B = 55000;

Unrelaxed100 = genfromtxt("outfiles/F1.dat", delimiter=" ");
plot(Unrelaxed100[:,0],
     B*Unrelaxed100[:,1],
     color="black",linewidth=2,linestyle=':',marker="",label='100 Model')
# Schmidt = genfromtxt("schmidt/schmidt.dat", delimiter=" ");
# plot(Schmidt[:,0],
#      Schmidt[:,1],
#      color="black",linewidth=2,linestyle='--',marker="o",label='MD')
Relaxed100 = loadtxt("outfiles/F2.dat", delimiter=" ");
plot(Relaxed100[:,0],
     B*Relaxed100[:,1],
     color="black",linewidth=2,linestyle='-',marker="",label='100 Model (2-Faceting)')
# SuperRelaxed100 = loadtxt("outfiles/F3.dat", delimiter=" ");
# plot(SuperRelaxed100[:,0],
#      B*SuperRelaxed100[:,1],
#      color="black",linewidth=3,linestyle='-',marker="",label='100 Model (3-Faceting)')

xlabel(r"Interface tilt angle $\phi$",size=15);
ylabel("Energy",size=15);
ylim(0,2200);
legend(loc='upper center',fancybox=True,shadow=True,ncol=2);
show()
