#!/bin/python
from pylab import plot,show,xlabel,xlim,ylabel,ylim,legend
from numpy import loadtxt, genfromtxt

B = 55000;

Unrelaxed100 = genfromtxt("outfiles/F1.dat", delimiter=" ");
plot(Unrelaxed100[:,0],
     B*Unrelaxed100[:,1],
     color="black",linewidth=2,linestyle=':',marker="",label='Unrelaxed')
# plot(Unrelaxed100[:,0],
#      B*Unrelaxed100[:,2],
#      color="black",linewidth=2,linestyle='--',marker='',label='Constrained 2F')
Relaxed100 = loadtxt("outfiles/F2.dat", delimiter=" ");
# plot(Relaxed100[:,0],
#      B*Relaxed100[:,1],
#      color="black",linewidth=2,linestyle='-',marker='o',label='2F Relaxed')
SuperRelaxed100 = loadtxt("outfiles/F3.dat",delimiter=" ");
plot(SuperRelaxed100[:,0],
     B*SuperRelaxed100[:,1],
     color="black",linewidth=3,linestyle='-',marker='o',label='3F Relaxed')
Schmidt = genfromtxt("schmidt/schmidt.dat", delimiter=" ");
plot(Schmidt[:,0],
     Schmidt[:,1],
     color="black",linewidth=2,linestyle='--',marker="o",label='MD Data')

xlabel(r"Inclination Angle $\phi$",size=15);
ylabel("Energy",size=15);
xlim(0,90);
ylim(0,2200);
legend(loc='upper center',fancybox=True,shadow=True,ncol=2);
show()
