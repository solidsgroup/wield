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
parser.add_argument('-l', '--labels-off', dest='labels_off', action='store_true', help='Suppress labels')
args=parser.parse_args()
filename=args.file
unrelaxed=args.unrelaxed
#plot parameters
fig_height_in = 3.8
fig_width_in  = 6.5
xlabelpad = 4
ylabelpad = 0
#data parameters
A_Mo = 2525 # the blue things
A_Fe = 1700 # the green things
if args.tex_off:
    def tex(a): return "\$"+a+"\$"
    def xlabel(a) : return "\\xlabel{"+a+"}"
    def ylabel(a) : return "\\ylabel{"+a+"}"
    def legend(a) : return "\\legend{"+a+"}"
    def annotate(a) : return "\\annotate{"+a+"}"
else:
    def tex(a): return "$"+a+"$"
    def xlabel(a) : return a
    def ylabel(a) : return a
    def legend(a) : return a
    def annotate(a) : return a


#symmetric twist
Tilt_001_001_Model  = numpy.loadtxt("001_001/outfiles/F1.dat", delimiter=" ");
Tilt_011_011_Model  = numpy.loadtxt("011_011/outfiles/F1.dat", delimiter=" ");
Tilt_031_031_Model  = numpy.loadtxt("031_031/outfiles/F1.dat", delimiter=" ");
Tilt_111_111_Model  = numpy.loadtxt("111_111/outfiles/F1.dat", delimiter=" ");
Tilt_112_112_Model  = numpy.loadtxt("112_112/outfiles/F1.dat", delimiter=" ");

Tilt_001_001_RModel  = numpy.loadtxt("001_001/outfiles/F2.dat", delimiter=" ");
Tilt_011_011_RModel  = numpy.loadtxt("011_011/outfiles/F2.dat", delimiter=" ");
Tilt_031_031_RModel  = numpy.loadtxt("031_031/outfiles/F3.dat", delimiter=" ");
Tilt_111_111_RModel  = numpy.loadtxt("111_111/outfiles/F3.dat", delimiter=" ");
Tilt_112_112_RModel  = numpy.loadtxt("112_112/outfiles/F2.dat", delimiter=" ");

Tilt_001_001_Wolf_Fe  = numpy.loadtxt("Wolf/001_001_Fe.dat", delimiter=" ");
Tilt_011_011_Wolf_Fe  = numpy.loadtxt("Wolf/011_011_Fe.dat", delimiter=" ");
Tilt_031_031_Wolf_Fe  = numpy.loadtxt("Wolf/031_031_Fe.dat", delimiter=" ");
Tilt_111_111_Wolf_Fe  = numpy.loadtxt("Wolf/111_111_Fe.dat", delimiter=" ");
Tilt_112_112_Wolf_Fe  = numpy.loadtxt("Wolf/112_112_Fe.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

#pylab.subplot(4,3,1)
pylab.subplot(2,3,1)
pylab.xlim(-1,91)
if not args.labels_off:
    pylab.title(annotate(tex("(001)(001)")))
pylab.ylim(0,1.8)
pylab.yticks(numpy.arange(0,1.8,0.4)) 
if unrelaxed:
    pylab.plot(   Tilt_001_001_Model[:,0],         1E-3*A_Fe*Tilt_001_001_Model[:,1],color="blue",linestyle='-')
    pylab.plot(90-Tilt_001_001_Model[:,0],         1E-3*A_Fe*Tilt_001_001_Model[:,1],color="blue",linestyle='-')
else:
    pylab.plot(   Tilt_001_001_Model[:,0],         1E-3*A_Fe*Tilt_001_001_Model[:,1],color="blue",linestyle=':')
    pylab.plot(90-Tilt_001_001_Model[:,0],         1E-3*A_Fe*Tilt_001_001_Model[:,1],color="blue",linestyle=':')
    pylab.plot(   Tilt_001_001_RModel[:,0], 1E-3*A_Fe*Tilt_001_001_RModel[:,1],color="blue",linestyle='-')
    pylab.plot(90-Tilt_001_001_RModel[:,0], 1E-3*A_Fe*Tilt_001_001_RModel[:,1],color="blue",linestyle='-')
pylab.plot(   Tilt_001_001_Wolf_Fe[:,0],       1E-3*Tilt_001_001_Wolf_Fe[:,1],color="blue",marker='o',linestyle=' ',label='MD')
if not args.labels_off:
    pylab.xlabel(xlabel("Twist angle (degrees)"),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);

#pylab.subplot(4,3,2)
pylab.subplot(2,3,2)
if not args.labels_off:
    pylab.title(annotate(tex("(011)(011)")))
pylab.xlim(-1,181)
pylab.ylim(0,1.800)
pylab.yticks(numpy.arange(0,1.8,0.4)) 
if unrelaxed:
    pylab.plot(Tilt_011_011_Model[:,0],  1E-3*A_Fe*Tilt_011_011_Model[:,1],  color="blue",linestyle='-')
else:
    pylab.plot(Tilt_011_011_Model[:,0],  1E-3*A_Fe*Tilt_011_011_Model[:,1],  color="blue",linestyle=':')
    pylab.plot(Tilt_011_011_RModel[:,0], 1E-3*A_Fe*Tilt_011_011_RModel[:,1], color="blue",linestyle='-')
pylab.plot(Tilt_011_011_Wolf_Fe[:,0],1E-3*     Tilt_011_011_Wolf_Fe[:,1],color="blue",marker='o',linestyle='',label='MD')
if not args.labels_off:
    pylab.xlabel(xlabel("Twist angle (degrees)"),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);

#ax = pylab.subplot(4,3,3)
pylab.subplot(2,3,3)
if not args.labels_off:
    pylab.title(annotate(tex("(031)(031)")))
pylab.xlim(-2,180)
pylab.ylim(0,1.800)
pylab.yticks(numpy.arange(0,1.8,0.4)) 
if unrelaxed:
    pylab.plot(Tilt_031_031_Model[:,0],  1E-3*A_Fe*Tilt_031_031_Model[:,1],  color="blue",linestyle='-')
else:
    pylab.plot(Tilt_031_031_Model[:,0],  1E-3*A_Fe*Tilt_031_031_Model[:,1],  color="blue",linestyle=':')
    pylab.plot(Tilt_031_031_RModel[:,0], 1E-3*A_Fe*Tilt_031_031_RModel[:,1], color="blue",linestyle='-')
pylab.plot(Tilt_031_031_Wolf_Fe[:,0],1E-3*     Tilt_031_031_Wolf_Fe[:,1],color="blue",marker='o',linestyle='',label='MD')
if not args.labels_off:
    pylab.xlabel(xlabel("Twist angle (degrees)"),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);

#ax = pylab.subplot(4,3,4)
pylab.subplot(2,3,4)
if not args.labels_off:
    pylab.title(annotate(tex("(111)(111)")))
pylab.xlim(-1,60)
pylab.ylim(0,1.800)
pylab.yticks(numpy.arange(0,1.8,0.4)) 
if unrelaxed:
    pylab.plot(Tilt_111_111_Model[:,0],  1E-3*A_Fe*Tilt_111_111_Model[:,1],  color="blue",linestyle='-')
else:
    pylab.plot(Tilt_111_111_Model[:,0],  1E-3*A_Fe*Tilt_111_111_Model[:,1],  color="blue",linestyle=':')
    pylab.plot(Tilt_111_111_RModel[:,0], 1E-3*A_Fe*Tilt_111_111_RModel[:,1], color="blue",linestyle='-')
pylab.plot(Tilt_111_111_Wolf_Fe[:,0],1E-3*     Tilt_111_111_Wolf_Fe[:,1],color="blue",marker='o',linestyle='',label='MD')
if not args.labels_off:
    pylab.xlabel(xlabel("Twist angle (degrees)"),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);

#ax = pylab.subplot(4,3,5)
ax = pylab.subplot(2,3,5)
if not args.labels_off:
    pylab.title(annotate(tex("(112)(112)")))
pylab.xlim(-2,180)
pylab.ylim(0,1.800)
pylab.yticks(numpy.arange(0,1.8,0.4)) 
if unrelaxed:
    pylab.plot(Tilt_112_112_Model[:,0],  1E-3*A_Fe*Tilt_112_112_Model[:,1],  color="blue",linestyle='-',label=legend('Fe (Model)').ljust(50))
else:
    pylab.plot(Tilt_112_112_Model[:,0],  1E-3*A_Fe*Tilt_112_112_Model[:,1],  color="blue",linestyle=':',label=legend('Fe (Unrelaxed model)').ljust(60))
    pylab.plot(Tilt_112_112_RModel[:,0], 1E-3*A_Fe*Tilt_112_112_RModel[:,1], color="blue",linestyle='-',label=legend('Fe (Relaxed model)').ljust(60))
pylab.plot(Tilt_112_112_Wolf_Fe[:,0],1E-3*     Tilt_112_112_Wolf_Fe[:,1],color="blue",marker='o',linestyle='',label=legend('Fe (MD-Johnson)').ljust(50))
if not args.labels_off:
    pylab.xlabel(xlabel("Twist angle (degrees)"),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);

if not args.labels_off:
    lgd = pylab.legend(ncol=1,bbox_to_anchor=(1.95,1))
pylab.tight_layout()
if args.tex_off:
    pylab.subplots_adjust(bottom=0.075,left=0.05,right=0.97,top=0.95,wspace=0.2,hspace=0.4);
else :
    pylab.subplots_adjust(bottom=0.075,left=0.05,right=0.98,top=0.95,wspace=0.2,hspace=0.4);

if (filename!=""):
    fig.savefig(filename, bbox_extra_artists=(lgd,), bbox_inches='tight')
else:
    pylab.show()
