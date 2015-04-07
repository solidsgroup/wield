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

B = 1450;
labels = [tex(r'(11\bar{1})(\bar{1}\bar{1}1)'), tex(r'(1\bar{1}0)(\bar{1}10)')]
locs = [0, 90]
offset = 0.75

Unrelaxed100 = genfromtxt("outfiles/F1.dat", delimiter=" ");
Relaxed100 = loadtxt("outfiles/F2.dat", delimiter=" ");
SuperRelaxed100 = loadtxt("outfiles/F3.dat",delimiter=" ");
Schmidt = genfromtxt("schmidt/schmidt.dat", delimiter=" ");

pylab.figure(figsize=(5,3))
ax = pylab.subplot(1,1,1);
pylab.plot(Unrelaxed100[:,0],1E-3*B*Unrelaxed100[:,1],color="blue",linestyle=':',marker="",label='Cu (Unrelaxed model)'),
pylab.plot(Relaxed100[:,0],1E-3*B*Relaxed100[:,1],color="blue",linestyle='-',marker='',label='Cu (2-Relaxed model)')
pylab.plot(SuperRelaxed100[:,0],1E-3*B*SuperRelaxed100[:,1],color="blue",linewidth=1.5,linestyle='-',marker='',label='Cu (3-Relaxed model)')
pylab.plot(Schmidt[:,0],1E-3*Schmidt[:,1],color="blue",linestyle='--',marker="o",label='Cu (MD)'.ljust(50))

for label, loc in zip(labels,locs):
    pylab.annotate(label, xycoords=('data','axes fraction'), xy=(loc+offset,1.05),va="bottom", ha="center",rotation=90)

pylab.xlabel(r"Inclination Angle "+tex(r"\phi"));
pylab.ylabel(r"Energy "+tex(r"J/m^2"));
pylab.xlim(0,90);
pylab.ylim(0,1.2);
pylab.tight_layout()

#box = ax.get_position();ax.set_position([0.9*box.x0, 0.85*box.y0, box.width*0.8, box.height*.8]);pylab.legend(ncol=1,loc='center left', bbox_to_anchor=(1, 0.5));
box = ax.get_position();ax.set_position([box.x0, 0.85*box.y0, box.width, box.height*.8]);pylab.legend(ncol=1,loc='center left', bbox_to_anchor=(1, 0.5));pylab.legend(ncol=1,loc='lower right');
pylab.show()
