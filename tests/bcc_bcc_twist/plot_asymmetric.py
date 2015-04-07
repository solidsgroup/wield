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
ylabelpad = 3
#data parameters
A_Mo = 2525
A_Fe = 1700
if args.tex_off:
    def tex(a): return "\$"+a+"\$"
else:
    def tex(a): return "$"+a+"$"


Tilt_114_011_Model  = numpy.loadtxt("114_011/outfiles/F1.dat", delimiter=" ");
Tilt_115_111_Model  = numpy.loadtxt("115_111/outfiles/F1.dat", delimiter=" ");
Tilt_158_031_Model  = numpy.loadtxt("158_031/outfiles/F1.dat", delimiter=" ");
Tilt_221_001_Model  = numpy.loadtxt("221_001/outfiles/F1.dat", delimiter=" ");
Tilt_552_112_Model  = numpy.loadtxt("552_112/outfiles/F1.dat", delimiter=" ");

Tilt_114_011_RModel  = numpy.loadtxt("114_011/outfiles/F2.dat", delimiter=" ");
Tilt_115_111_RModel  = numpy.loadtxt("115_111/outfiles/F2.dat", delimiter=" ");
Tilt_158_031_RModel  = numpy.loadtxt("158_031/outfiles/F2.dat", delimiter=" ");
Tilt_221_001_RModel  = numpy.loadtxt("221_001/outfiles/F2.dat", delimiter=" ");
Tilt_552_112_RModel  = numpy.loadtxt("552_112/outfiles/F2.dat", delimiter=" ");

Tilt_114_011_Wolf_Fe  = numpy.loadtxt("Wolf/114_011_Fe.dat", delimiter=" ");
Tilt_115_111_Wolf_Fe  = numpy.loadtxt("Wolf/115_111_Fe.dat", delimiter=" ");
Tilt_158_031_Wolf_Fe  = numpy.loadtxt("Wolf/158_031_Fe.dat", delimiter=" ");
Tilt_221_001_Wolf_Fe  = numpy.loadtxt("Wolf/221_001_Fe.dat", delimiter=" ");
Tilt_552_112_Wolf_Fe  = numpy.loadtxt("Wolf/552_112_Fe.dat", delimiter=" ");

Tilt_114_011_Wolf_Mo  = numpy.loadtxt("Wolf/114_011_Mo.dat", delimiter=" ");
Tilt_115_111_Wolf_Mo  = numpy.loadtxt("Wolf/115_111_Mo.dat", delimiter=" ");
Tilt_158_031_Wolf_Mo  = numpy.loadtxt("Wolf/158_031_Mo.dat", delimiter=" ");
Tilt_221_001_Wolf_Mo  = numpy.loadtxt("Wolf/221_001_Mo.dat", delimiter=" ");
Tilt_552_112_Wolf_Mo  = numpy.loadtxt("Wolf/552_112_Mo.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

ax = pylab.subplot(2,3,1)
if not args.labels_off:
    pylab.title(tex("(114)(011)"))
pylab.xlim(0,180)
pylab.xticks(numpy.arange(0,180,40)) 
pylab.ylim(0,2.2)
if unrelaxed:
    pylab.plot(Tilt_114_011_Model[:,0],  1E-3*A_Mo*Tilt_114_011_Model[:,1],  color="green",linestyle='-')
    pylab.plot(Tilt_114_011_Model[:,0],  1E-3*A_Fe*Tilt_114_011_Model[:,1],  color="blue",linestyle='-') 
else:
    pylab.plot(Tilt_114_011_Model[:,0],  1E-3*A_Mo*Tilt_114_011_Model[:,1],  color="green",linestyle=':')
    pylab.plot(Tilt_114_011_Model[:,0],  1E-3*A_Fe*Tilt_114_011_Model[:,1],  color="blue",linestyle=':') 
    pylab.plot(Tilt_114_011_RModel[:,0], 1E-3*A_Mo*Tilt_114_011_RModel[:,1], color="green",linestyle='-')
    pylab.plot(Tilt_114_011_RModel[:,0], 1E-3*A_Fe*Tilt_114_011_RModel[:,1], color="blue",linestyle='-')
pylab.plot(Tilt_114_011_Wolf_Mo[:,0],1E-3*     Tilt_114_011_Wolf_Mo[:,1],color="green",marker='o',linestyle='')
pylab.plot(Tilt_114_011_Wolf_Fe[:,0],1E-3*     Tilt_114_011_Wolf_Fe[:,1],color="blue",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);


ax = pylab.subplot(2,3,2)
if not args.labels_off:
    pylab.title(tex("(115)(111)"))
pylab.xlim(0,60)
pylab.ylim(0,2.5)
if unrelaxed:
    pylab.plot(Tilt_115_111_Model[:,0],  1E-3*A_Mo*Tilt_115_111_Model[:,1],        color="green", linestyle='-')
    pylab.plot(Tilt_115_111_Model[:,0],  1E-3*A_Fe*Tilt_115_111_Model[:,1],        color="blue",linestyle='-')
else:
    pylab.plot(Tilt_115_111_Model[:,0],  1E-3*A_Mo*Tilt_115_111_Model[:,1],        color="green", linestyle=':')
    pylab.plot(Tilt_115_111_Model[:,0],  1E-3*A_Fe*Tilt_115_111_Model[:,1],        color="blue",linestyle=':')
    pylab.plot(Tilt_115_111_RModel[:,0], 1E-3*A_Mo*Tilt_115_111_RModel[:,1],color="green",linestyle='-')
    pylab.plot(Tilt_115_111_RModel[:,0], 1E-3*A_Fe*Tilt_115_111_RModel[:,1],color="blue",linestyle='-')
pylab.plot(Tilt_115_111_Wolf_Mo[:,0],1E-3*Tilt_115_111_Wolf_Mo[:,1],           color="green", marker='o',linestyle='')
pylab.plot(Tilt_115_111_Wolf_Fe[:,0],1E-3*Tilt_115_111_Wolf_Fe[:,1],           color="blue",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);


ax = pylab.subplot(2,3,3)
if not args.labels_off:
    pylab.title(tex("(158)(031)"))
pylab.xlim(0,180)
pylab.xticks(numpy.arange(0,180,40)) 
pylab.ylim(0,2.4)
if unrelaxed:
    pylab.plot(Tilt_158_031_Model[:,0],  1E-3*A_Mo*Tilt_158_031_Model[:,1],        color="green",linestyle='-')
    pylab.plot(Tilt_158_031_Model[:,0],  1E-3*A_Fe*Tilt_158_031_Model[:,1],        color="blue",linestyle='-')
else:
    pylab.plot(Tilt_158_031_Model[:,0],  1E-3*A_Mo*Tilt_158_031_Model[:,1],        color="green",linestyle=':')
    pylab.plot(Tilt_158_031_Model[:,0],  1E-3*A_Fe*Tilt_158_031_Model[:,1],        color="blue",linestyle=':')
    pylab.plot(Tilt_158_031_RModel[:,0], 1E-3*A_Mo*Tilt_158_031_RModel[:,1],color="green",linestyle='-')
    pylab.plot(Tilt_158_031_RModel[:,0], 1E-3*A_Fe*Tilt_158_031_RModel[:,1],color="blue",linestyle='-')
pylab.plot(Tilt_158_031_Wolf_Mo[:,0],1E-3*Tilt_158_031_Wolf_Mo[:,1],           color="green",marker='o',linestyle='')
pylab.plot(Tilt_158_031_Wolf_Fe[:,0],1E-3*Tilt_158_031_Wolf_Fe[:,1],           color="blue",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);

ax = pylab.subplot(2,3,4)
if not args.labels_off:
    pylab.title(tex("(221)(001)"))
pylab.xlim(0,90)
pylab.ylim(0,2.2)
if unrelaxed:
    pylab.plot(Tilt_221_001_Model[:,0],  1E-3*A_Mo*Tilt_221_001_Model[:,1],        color="green", linestyle='-')
    pylab.plot(Tilt_221_001_Model[:,0],  1E-3*A_Fe*Tilt_221_001_Model[:,1],        color="blue",linestyle='-')
else:
    pylab.plot(Tilt_221_001_Model[:,0],  1E-3*A_Mo*Tilt_221_001_Model[:,1],        color="green", linestyle=':')
    pylab.plot(Tilt_221_001_Model[:,0],  1E-3*A_Fe*Tilt_221_001_Model[:,1],        color="blue",linestyle=':')
    pylab.plot(Tilt_221_001_RModel[:,0], 1E-3*A_Mo*Tilt_221_001_RModel[:,1],color="green",linestyle='-')
    pylab.plot(Tilt_221_001_RModel[:,0], 1E-3*A_Fe*Tilt_221_001_RModel[:,1],color="blue",linestyle='-')
pylab.plot(Tilt_221_001_Wolf_Mo[:,0],1E-3*Tilt_221_001_Wolf_Mo[:,1],           color="green", marker='o',linestyle='')
pylab.plot(Tilt_221_001_Wolf_Fe[:,0],1E-3*Tilt_221_001_Wolf_Fe[:,1],           color="blue",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);

ax = pylab.subplot(2,3,5)
if not args.labels_off:
    pylab.title(tex("(552)(112)"))
pylab.xlim(0,180)
pylab.xticks(numpy.arange(0,180,40)) 
pylab.ylim(0,2.3)
if unrelaxed:
    pylab.plot(Tilt_552_112_Model[:,0],  1E-3*A_Mo*Tilt_552_112_Model[:,1],        color="green", linestyle='-',label='Mo (Model)'.ljust(50))
    pylab.plot(Tilt_552_112_Model[:,0],  1E-3*A_Fe*Tilt_552_112_Model[:,1],        color="blue",linestyle='-',label='Fe (Model)'.ljust(50))
else:
    pylab.plot(Tilt_552_112_Model[:,0],  1E-3*A_Mo*Tilt_552_112_Model[:,1],        color="green", linestyle=':',label='Mo (Unrelaxed model)'.ljust(60))
    pylab.plot(Tilt_552_112_Model[:,0],  1E-3*A_Fe*Tilt_552_112_Model[:,1],        color="blue",linestyle=':',label='Fe (Unrelaxed model)'.ljust(60))
    pylab.plot(Tilt_552_112_RModel[:,0], 1E-3*A_Mo*Tilt_552_112_RModel[:,1],color="green", linestyle='-',label='Mo (Relaxed model)'.ljust(60))
    pylab.plot(Tilt_552_112_RModel[:,0], 1E-3*A_Fe*Tilt_552_112_RModel[:,1],color="blue",linestyle='-',label='Fe (Relaxed model)'.ljust(60))
pylab.plot(Tilt_552_112_Wolf_Mo[:,0],1E-3*Tilt_552_112_Wolf_Mo[:,1],           color="green", marker='o',linestyle='',label='Mo (MD-FS)'.ljust(50))
pylab.plot(Tilt_552_112_Wolf_Fe[:,0],1E-3*Tilt_552_112_Wolf_Fe[:,1],           color="blue",marker='o',linestyle='',label='Fe (MD-Johnson)'.ljust(50))
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);

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

