#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy
import argparse

#read commandline argument
parser = argparse.ArgumentParser(description='Create a plot');
parser.add_argument('-f','--file', default="", help='Output file name');
parser.add_argument('-u', '--unrelaxed', dest='unrelaxed', action='store_true', help='Plot unrelaxed only');
parser.add_argument('-t', '--tex-off', dest='tex_off', action='store_true', help='Render without using latex');
parser.add_argument('-a', '--annotate', dest='annotate', action='store_true', help='Render annotations');
parser.add_argument('-r', '--right', dest='right', action='store_true', help='Put legend on right');
parser.add_argument('-l', '--labels-off', dest='labels_off', action='store_true', help='Suppress labels')
args=parser.parse_args()
filename=args.file
unrelaxed=args.unrelaxed
#plot parameters
if args.annotate: fig_height_in = 4.75
else: fig_height_in = 2
fig_width_in  = 6.5
xlabelpad=1
ylabelpad=3
if args.right: legend_loc = 'lower right'
else: legend_loc = 'lower center'
#data parameters
A_Cu = 1750
#texing
if args.tex_off:
    def tex(a): return "\$"+a+"\$"
    def xlabel(a): return "\\xlabel{"+a+"}"
    def ylabel(a): return "\\ylabel{"+a+"}"
    def legend(a): return "\\legend{"+a+"}"
else:
    def tex(a): return "$"+a+"$"
    def xlabel(a): return a
    def ylabel(a): return a
    def legend(a): return a


Tilt_001_Model  = numpy.loadtxt("100_2d/outfiles/F1.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("110_2d/outfiles/F1.dat", delimiter=" ");

Tilt_001_Model_Relaxed  = numpy.loadtxt("100_2d/outfiles/F2.dat", delimiter=" ");
Tilt_110_Model_Relaxed  = numpy.loadtxt("110_2d/outfiles/F2.dat", delimiter=" ");

Tilt_001_Exp  = numpy.loadtxt("Experiment/cu100.dat", delimiter=" ");
Tilt_110_Exp_1123  = numpy.loadtxt("Experiment/cu110_1123.dat", delimiter=" ");
Tilt_110_Exp_1223  = numpy.loadtxt("Experiment/cu110_1223.dat", delimiter=" ");
Tilt_110_Exp_1273  = numpy.loadtxt("Experiment/cu110_1273.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

pylab.subplot(121)
pylab.xlim(0,90)
pylab.ylim(0,1.)
if unrelaxed:
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Cu*Tilt_001_Model[:,1],color="black",linestyle='-')
else:
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Cu*Tilt_001_Model[:,1],color="black",linestyle=':')
    pylab.plot(Tilt_001_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_001_Model_Relaxed[:,1],color="black",linestyle='-')
pylab.plot(Tilt_001_Exp[:,0],   Tilt_001_Exp[:,1],color="blue",marker='o',linestyle='--')
if not args.labels_off:
    pylab.xlabel(xlabel(tex(r'[100]')+' tilt angle '+tex(r'\theta')),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);
offset=0.5
if args.annotate:
    pylab.annotate(tex(r'(001)(001)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}3)(013)'), xycoords=('data','axes fraction'), xy=(36.41+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}1)(011)'), xycoords=('data','axes fraction'), xy=(90+offset,1.05),va="bottom", ha="center",rotation=90)

ax = pylab.subplot(122)
pylab.xlim(0,180)
pylab.ylim(0,1.)
if unrelaxed:
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Cu*Tilt_110_Model[:,1],color="black",linestyle='-',label=legend('Cu(Cov)').ljust(50))
else:
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Cu*Tilt_110_Model[:,1],color="black",linestyle=':',label=legend('Cu (Unrelaxed model)').ljust(50))
    pylab.plot(Tilt_110_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_110_Model_Relaxed[:,1],color="black",linestyle='-',label=legend('Cu (Relaxed model)').ljust(50))
pylab.plot(-1,-1,color="blue",marker='o',linestyle='--',label=legend('Experiment'))
pylab.plot(Tilt_110_Exp_1123[:,0],Tilt_110_Exp_1123[:,1],color="green",marker='s',linestyle='--',label=legend('Experiment \$T=1273K\$').ljust(50))
pylab.plot(Tilt_110_Exp_1223[:,0],Tilt_110_Exp_1223[:,1],color="red",marker='v',linestyle='--',label=legend('Experiment \$T=1223K\$').ljust(50))
pylab.plot(Tilt_110_Exp_1273[:,0],Tilt_110_Exp_1273[:,1],color="orange",marker='^',linestyle='--',label=legend('Experiment \$T=1273K\$').ljust(50))
if not args.labels_off:
    pylab.xlabel(xlabel(tex(r'[110]')+' tilt angle '+tex(r'\theta')),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);
offset=1
if args.annotate:
    pylab.annotate(tex(r'(\bar{1}10)(\bar{1}10)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(\bar{3}31)(\bar{3}3\bar{1})'), xycoords=('data','axes fraction'), xy=(25.77+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(\bar{1}11)(\bar{1}1\bar{1})'), xycoords=('data','axes fraction'), xy=(70.6+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(\bar{1}13)(\bar{1}1\bar{3})'), xycoords=('data','axes fraction'), xy=(129.4+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(001)(00\bar{1})'), xycoords=('data','axes fraction'), xy=(180+offset,1.05),va="bottom", ha="center",rotation=90)

handles, labels = ax.get_legend_handles_labels()
if not args.labels_off:
    if unrelaxed:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=3)
    else:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=3)

pylab.tight_layout();
if args.annotate: pylab.subplots_adjust(bottom=0.175,left=0.075,right=0.98,top=0.875,wspace=0.2,hspace=0.75)
else:             pylab.subplots_adjust(bottom=0.35,left=0.075,right=0.98,top=0.975,wspace=0.2,hspace=0.25)
if (filename!=""):
    fig.savefig(filename, bbox_extra_artists=(lgd,), bbox_inches='tight')
else:
    pylab.show()

