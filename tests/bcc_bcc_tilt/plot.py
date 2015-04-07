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
else: fig_height_in = 4
fig_width_in  = 6.5
xlabelpad=1
ylabelpad=3
if args.right: legend_loc = 'lower right'
else: legend_loc = 'lower center'
#data parameters
A_Mo = 2525 # blue
A_Fe = 1950 # green
#texing
if args.tex_off:
    def tex(a): return "\$"+a+"\$"
else:
    def tex(a): return "$"+a+"$"


Tilt_001_Model          = numpy.loadtxt("100_2d/outfiles/F1.dat", delimiter=" ");
Tilt_110_Model          = numpy.loadtxt("110_2d/outfiles/F1.dat", delimiter=" ");
Tilt_111_Model          = numpy.loadtxt("111_2d/outfiles/F1.dat", delimiter=" ");
Tilt_112_Model          = numpy.loadtxt("112_2d/outfiles/F1.dat", delimiter=" ");

Tilt_001_Model_Relaxed  = numpy.loadtxt("100_2d/outfiles/F2.dat", delimiter=" ");
Tilt_110_Model_Relaxed  = numpy.loadtxt("110_2d/outfiles/F2.dat", delimiter=" ");
Tilt_111_Model_Relaxed  = numpy.loadtxt("111_2d/outfiles/F2.dat", delimiter=" ");
Tilt_112_Model_Relaxed  = numpy.loadtxt("112_2d/outfiles/F2.dat", delimiter=" ");

Tilt_001_Wolf_Mo        = numpy.loadtxt("Wolf/100_Mo.dat", delimiter=" ");
Tilt_110_Wolf_Mo        = numpy.loadtxt("Wolf/110_Mo.dat", delimiter=" ");
Tilt_111_Wolf_Mo        = numpy.loadtxt("Wolf/111_Mo.dat", delimiter=" ");
Tilt_112_Wolf_Mo        = numpy.loadtxt("Wolf/112_Mo.dat", delimiter=" ");

Tilt_001_Wolf_Fe        = numpy.loadtxt("Wolf/100_Fe.dat", delimiter=" ");
Tilt_110_Wolf_Fe        = numpy.loadtxt("Wolf/110_Fe.dat", delimiter=" ");
Tilt_111_Wolf_Fe        = numpy.loadtxt("Wolf/111_Fe.dat", delimiter=" ");
Tilt_112_Wolf_Fe        = numpy.loadtxt("Wolf/112_Fe.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

pylab.subplot(221)
pylab.xlim(0,90)
pylab.ylim(0,2)
if unrelaxed:
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Mo*Tilt_001_Model[:,1],        color="blue", marker='', linestyle='-')
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Fe*Tilt_001_Model[:,1],        color="green",marker='', linestyle='-')
else:
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Mo*Tilt_001_Model[:,1],        color="blue", marker='', linestyle=':')
    pylab.plot(Tilt_001_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_001_Model_Relaxed[:,1],color="blue", marker='', linestyle='-')
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Fe*Tilt_001_Model[:,1],        color="green",marker='', linestyle=':')
    pylab.plot(Tilt_001_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_001_Model_Relaxed[:,1],color="green",marker='', linestyle='-')
pylab.plot(Tilt_001_Wolf_Mo[:,0],      1E-3*     Tilt_001_Wolf_Mo[:,1],      color="blue", marker='o',linestyle='')
pylab.plot(Tilt_001_Wolf_Fe[:,0],      1E-3*     Tilt_001_Wolf_Fe[:,1],      color="green",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel(tex(r'[100]')+' tilt angle '+tex(r'\theta'),labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
offset=0.5
if args.annotate:
    pylab.annotate(tex(r'(001)(001)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}3)(013)'), xycoords=('data','axes fraction'), xy=(37.5+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}2)(012)'), xycoords=('data','axes fraction'), xy=(53+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}1)(011)'), xycoords=('data','axes fraction'), xy=(90+offset,1.05),va="bottom", ha="center",rotation=90)

pylab.subplot(222)
pylab.xlim(0,180)
pylab.ylim(0,2)
if unrelaxed:
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Mo*Tilt_110_Model[:,1],        color="blue", marker='', linestyle='-')
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Fe*Tilt_110_Model[:,1],        color="green",marker='', linestyle='-')
else:
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Mo*Tilt_110_Model[:,1],        color="blue", marker='', linestyle=':')
    pylab.plot(Tilt_110_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_110_Model_Relaxed[:,1],color="blue", marker='', linestyle='-')
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Fe*Tilt_110_Model[:,1],        color="green",marker='', linestyle=':')
    pylab.plot(Tilt_110_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_110_Model_Relaxed[:,1],color="green",marker='', linestyle='-')
pylab.plot(Tilt_110_Wolf_Mo[:,0],      1E-3*     Tilt_110_Wolf_Mo[:,1],      color="blue", marker='o',linestyle='')
pylab.plot(Tilt_110_Wolf_Fe[:,0],      1E-3*     Tilt_110_Wolf_Fe[:,1],      color="green",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel(tex(r'[110]')+' tilt angle '+tex(r'\theta'),labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
offset=1
if args.annotate:
    pylab.annotate(tex(r'(1\bar{1}0)(1\bar{1}0)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(3\bar{3}2)(3\bar{3}\bar{2})'), xycoords=('data','axes fraction'), xy=(51+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(1\bar{1}1)(1\bar{1}\bar{1})'), xycoords=('data','axes fraction'), xy=(70.6+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(1\bar{1}2)(1\bar{1}\bar{2})'), xycoords=('data','axes fraction'), xy=(109+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(1\bar{1}4)(1\bar{1}\bar{4})'), xycoords=('data','axes fraction'), xy=(140.8+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(001)(00\bar{1})'), xycoords=('data','axes fraction'), xy=(180+offset,1.05),va="bottom", ha="center",rotation=90)

pylab.subplot(223)
pylab.xlim(0,60)
pylab.ylim(0,2)
if unrelaxed:
    pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Mo*Tilt_111_Model[:,1],        color="blue", marker='', linestyle='-')
    pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Fe*Tilt_111_Model[:,1],        color="green",marker='', linestyle='-')
else:
    pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Mo*Tilt_111_Model[:,1],        color="blue", marker='', linestyle=':')
    pylab.plot(Tilt_111_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_111_Model_Relaxed[:,1],color="blue", marker='', linestyle='-')
    pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Fe*Tilt_111_Model[:,1],        color="green",marker='', linestyle=':')
    pylab.plot(Tilt_111_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_111_Model_Relaxed[:,1],color="green",marker='', linestyle='-')
pylab.plot(Tilt_111_Wolf_Mo[:,0],      1E-3*     Tilt_111_Wolf_Mo[:,1],      color="blue", marker='o',linestyle='')
pylab.plot(Tilt_111_Wolf_Fe[:,0],      1E-3*     Tilt_111_Wolf_Fe[:,1],      color="green",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel(tex(r'[111]')+' tilt angle '+tex(r'\theta'),labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
offset = 0.5
if args.annotate:
    pylab.annotate(tex(r'(10\bar{1})(10\bar{1})'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(21\bar{3})(3\bar{1}\bar{2})'), xycoords=('data','axes fraction'), xy=(38+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(11\bar{2})(2\bar{1}\bar{1})'), xycoords=('data','axes fraction'), xy=(60+offset,1.05),va="bottom", ha="center",rotation=90)

ax = pylab.subplot(224)
pylab.xlim(0,110)
pylab.ylim(0,2)
if unrelaxed:
    pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Mo*Tilt_112_Model[:,1],        color="blue", marker='', linestyle='-',label='Mo (Model)'.ljust(50))
    pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Fe*Tilt_112_Model[:,1],        color="green",marker='', linestyle='-',label='Fe (Model)'.ljust(50))
else:
    pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Mo*Tilt_112_Model[:,1],        color="blue", marker='', linestyle=':',label='Mo (Unrelaxed model)'.ljust(60))
    pylab.plot(Tilt_112_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_112_Model_Relaxed[:,1],color="blue", marker='', linestyle='-',label='Mo (Relaxed model)'.ljust(50))
    pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Fe*Tilt_112_Model[:,1],        color="green",marker='', linestyle=':',label='Fe (Unrelaxed model)'.ljust(60))
    pylab.plot(Tilt_112_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_112_Model_Relaxed[:,1],color="green",marker='', linestyle='-',label='Fe (Relaxed model)'.ljust(60))
pylab.plot(Tilt_112_Wolf_Mo[:,0],      1E-3*     Tilt_112_Wolf_Mo[:,1],      color="blue", marker='o',linestyle='', label='Mo (MD-FS)'.ljust(50))
pylab.plot(Tilt_112_Wolf_Fe[:,0],      1E-3*     Tilt_112_Wolf_Fe[:,1],      color="green",marker='o',linestyle='', label='Fe (MD-Johnson)'.ljust(50))
if not args.labels_off:
    pylab.xlabel(tex(r'[112]')+' tilt angle '+tex(r'\theta'),labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
offset=0.9
if args.annotate:
    pylab.annotate(tex(r'(1\bar{1}0)(1\bar{1}0)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)

handles, labels = ax.get_legend_handles_labels()
if not args.labels_off:
    if unrelaxed:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=2)
    else:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=3)

pylab.tight_layout();

if args.annotate: pylab.subplots_adjust(bottom=0.175,left=0.075,right=0.98,top=0.875,wspace=0.2,hspace=0.75)
else:             pylab.subplots_adjust(bottom=0.2,left=0.075,right=0.98,top=0.975,wspace=0.2,hspace=0.25)

if (filename!=""):
    fig.savefig(filename, bbox_extra_artists=(lgd,), bbox_inches='tight')
else:
    pylab.show()

