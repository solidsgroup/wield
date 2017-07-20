#!/bin/python
import pylab
from numpy import loadtxt, genfromtxt
import argparse

parser = argparse.ArgumentParser(description='Create a plot');
parser.add_argument('-t', '--tex-off', dest='tex_off', action='store_true', help='Render without using latex');
args=parser.parse_args()
if args.tex_off:
    def tex(a): return "\$"+a+"\$"
else:
    def tex(a): return "$"+a+"$"

A_Cu = 1450;
A_Al = 750;
A_Au = 950
labels = [tex(r'(11\bar{1})(111)'), tex(r'(112)(11\bar{2})')]
locs = [0, 90]
offset = 0.75

Unrelaxed100 = genfromtxt("outfiles/F1.dat", delimiter=" ");
Relaxed100 = loadtxt("outfiles/F2.dat", delimiter=" ");
#SuperRelaxed100 = loadtxt("outfiles/F3.dat",delimiter=" ");
Wolf = genfromtxt("wolf/wolf.dat", delimiter=" ");
Tschopp_Cu = genfromtxt("tschopp/Cu.dat", delimiter=" ");
Tschopp_Al = genfromtxt("tschopp/Al.dat", delimiter=" ");

pylab.figure(figsize=(5.5,3))
ax = pylab.subplot(1,1,1);
pylab.plot(Unrelaxed100[:,0],1E-3*A_Cu*Unrelaxed100[:,1],color="blue",linestyle=':',marker="",label='Cu (Unrelaxed model)'.ljust(60)),
pylab.plot(Relaxed100[:,0],1E-3*A_Cu*Relaxed100[:,1],color="blue",linestyle='-',marker='',label='Cu (Relaxed model)'.ljust(60))
pylab.plot(Relaxed100[:,0],1E-3*A_Al*Relaxed100[:,1],color="green",linestyle='-',marker='',label='Al (Relaxed model)'.ljust(60))
pylab.plot(Relaxed100[:,0],1E-3*A_Au*Relaxed100[:,1],color="red",linestyle='-',marker='',label='Au (Relaxed model)'.ljust(60))
pylab.plot(Wolf[:,0],Wolf[:,1],color="blue",linestyle='',marker="o",label='Cu (MD-Wolf)'.ljust(60))
pylab.plot(Tschopp_Cu[:,0],1E-3*Tschopp_Cu[:,1],color="blue",linestyle='',marker="^",label='Cu (MD-Tschopp)'.ljust(60))
pylab.plot(Tschopp_Al[:,0],1E-3*Tschopp_Al[:,1],color="green",linestyle='',marker="o",label='Al (MD-Tschopp)'.ljust(60))

for label, loc in zip(labels,locs):
    pylab.annotate(label, xycoords=('data','axes fraction'), xy=(loc+offset,1.05),va="bottom", ha="center",rotation=90)

pylab.xlabel(r"Inclination Angle "+tex(r"\phi"));
pylab.ylabel(r"Energy "+tex(r"J/m^2"));
pylab.xlim(0,90);
pylab.ylim(0,0.9);
pylab.tight_layout()

box = ax.get_position();ax.set_position([0.9*box.x0, 0.85*box.y0, box.width*0.675, box.height*.8]);pylab.legend(ncol=1,loc='center left', bbox_to_anchor=(1, 0.5));
#box = ax.get_position();ax.set_position([box.x0, 0.85*box.y0, box.width, box.height*.8]);pylab.legend(ncol=1,loc='center left', bbox_to_anchor=(1, 0.5));pylab.legend(ncol=2,loc='lower right');
pylab.show()
