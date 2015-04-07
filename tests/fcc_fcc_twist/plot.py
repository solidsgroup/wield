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
parser.add_argument('-r', '--right', dest='right', action='store_true', help='Put legend on right');
parser.add_argument('-l', '--labels-off', dest='labels_off', action='store_true', help='Suppress labels')
args=parser.parse_args()
filename=args.file
unrelaxed=args.unrelaxed          
#plot parameters
fig_height_in = 4.5
fig_width_in  = 6.5
xlabelpad = 4
ylabelpad = 3
if args.right: legend_loc = 'lower right'
else: legend_loc = 'lower center'
#data parameters
A_Cu = 1450
A_Au = 950
#texing
if args.tex_off:
    def tex(a): return "\$"+a+"\$"
else:
    def tex(a): return "$"+a+"$"


Tilt_100_100_Model  = numpy.loadtxt("100_100/outfiles/F1.dat", delimiter=" ");
Tilt_111_111_Model  = numpy.loadtxt("111_111/outfiles/F1.dat", delimiter=" ");
Tilt_114_011_Model  = numpy.loadtxt("114_011/outfiles/F1.dat", delimiter=" ");
Tilt_115_111_Model  = numpy.loadtxt("115_111/outfiles/F1.dat", delimiter=" ");
Tilt_221_001_Model  = numpy.loadtxt("221_001/outfiles/F1.dat", delimiter=" ");
Tilt_557_113_Model  = numpy.loadtxt("557_113/outfiles/F1.dat", delimiter=" ");

Tilt_100_100_Model_Relaxed  = numpy.loadtxt("100_100/outfiles/F2.dat", delimiter=" ");
Tilt_111_111_Model_Relaxed  = numpy.loadtxt("111_111/outfiles/F2.dat", delimiter=" ");
Tilt_114_011_Model_Relaxed  = numpy.loadtxt("114_011/outfiles/F2.dat", delimiter=" ");
Tilt_115_111_Model_Relaxed  = numpy.loadtxt("115_111/outfiles/F2.dat", delimiter=" ");
Tilt_221_001_Model_Relaxed  = numpy.loadtxt("221_001/outfiles/F2.dat", delimiter=" ");
Tilt_557_113_Model_Relaxed  = numpy.loadtxt("557_113/outfiles/F2.dat", delimiter=" ");

Tilt_100_100_Wolf_Cu  = numpy.loadtxt("Wolf/100_100_Cu.dat", delimiter=" ");
Tilt_111_111_Wolf_Cu  = numpy.loadtxt("Wolf/111_111_Cu.dat", delimiter=" ");
Tilt_114_011_Wolf_Cu  = numpy.loadtxt("Wolf/114_011_Cu.dat", delimiter=" ");
Tilt_115_111_Wolf_Cu  = numpy.loadtxt("Wolf/115_111_Cu.dat", delimiter=" ");
Tilt_221_001_Wolf_Cu  = numpy.loadtxt("Wolf/221_001_Cu.dat", delimiter=" ");
Tilt_557_113_Wolf_Cu  = numpy.loadtxt("Wolf/557_113_Cu.dat", delimiter=" ");

Tilt_114_011_Wolf_Au  = numpy.loadtxt("Wolf/114_011_Au.dat", delimiter=" ");
Tilt_115_111_Wolf_Au  = numpy.loadtxt("Wolf/115_111_Au.dat", delimiter=" ");
Tilt_221_001_Wolf_Au  = numpy.loadtxt("Wolf/221_001_Au.dat", delimiter=" ");
Tilt_557_113_Wolf_Au  = numpy.loadtxt("Wolf/557_113_Au.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches


pylab.subplot(231)
pylab.xlim(0,90)
if not args.labels_off:
    pylab.title(tex("(100)(100)"))
pylab.ylim(0,1.)
if unrelaxed:
    pylab.plot(Tilt_100_100_Model[:,0],        1E-3*A_Cu*Tilt_100_100_Model[:,1],color="blue",linestyle='-')
else:
    pylab.plot(Tilt_100_100_Model[:,0],        1E-3*A_Cu*Tilt_100_100_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_100_100_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_100_100_Model_Relaxed[:,1],color="blue",linestyle='-')
pylab.plot(Tilt_100_100_Wolf_Cu[:,0],      1E-3*Tilt_100_100_Wolf_Cu[:,1],color="blue",marker='o',linestyle='',label='MD')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
pylab.tick_params(axis='both', which='major')

pylab.subplot(232)
pylab.xlim(0,90)
pylab.ylim(0,1.)
if not args.labels_off:
    pylab.title(tex("(111)(111)"))
if unrelaxed:
    pylab.plot(Tilt_111_111_Model[:,0],        1E-3*A_Cu*Tilt_111_111_Model[:,1],color="blue",linestyle='-')
else:
    pylab.plot(Tilt_111_111_Model[:,0],        1E-3*A_Cu*Tilt_111_111_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_111_111_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_111_111_Model_Relaxed[:,1],color="blue",linestyle='-')
pylab.plot(Tilt_111_111_Wolf_Cu[:,0],1E-3*Tilt_111_111_Wolf_Cu[:,1],color="blue",marker='o',linestyle='',label='MD')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
pylab.tick_params(axis='both', which='major')

pylab.subplot(233)
pylab.xlim(0,180)
pylab.xticks(numpy.arange(0,180,40)) 
pylab.ylim(0,1.300)
if not args.labels_off:
    pylab.title(tex("(114)(011)"))
if unrelaxed:
    pylab.plot(Tilt_114_011_Model[:,0],            1E-3*A_Cu*Tilt_114_011_Model[:,1],color="blue",linestyle='-')
    pylab.plot(Tilt_114_011_Model[:,0],            1E-3*A_Au*Tilt_114_011_Model[:,1],color="green",linestyle='-')
else:
    pylab.plot(Tilt_114_011_Model[:,0],            1E-3*A_Cu*Tilt_114_011_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_114_011_Model_Relaxed[:,0],    1E-3*A_Cu*Tilt_114_011_Model_Relaxed[:,1],color="blue",linestyle='-')
    pylab.plot(180-Tilt_114_011_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_114_011_Model_Relaxed[:,1],color="blue",linestyle='-')
    pylab.plot(Tilt_114_011_Model[:,0],            1E-3*A_Au*Tilt_114_011_Model[:,1],color="green",linestyle=':')
    pylab.plot(Tilt_114_011_Model_Relaxed[:,0],    1E-3*A_Au*Tilt_114_011_Model_Relaxed[:,1],color="green",linestyle='-')
    pylab.plot(180-Tilt_114_011_Model_Relaxed[:,0],1E-3*A_Au*Tilt_114_011_Model_Relaxed[:,1],color="green",linestyle='-')
pylab.plot(Tilt_114_011_Wolf_Cu[:,0],1E-3*Tilt_114_011_Wolf_Cu[:,1],color="blue",marker='o',linestyle='')
pylab.plot(Tilt_114_011_Wolf_Au[:,0],1E-3*Tilt_114_011_Wolf_Au[:,1],color="green",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
pylab.tick_params(axis='both', which='major')

pylab.subplot(234)
pylab.xlim(0,60)
pylab.ylim(0,1.00)
if not args.labels_off:
    pylab.title(tex("(115)(111)"))
if unrelaxed:
    pylab.plot(Tilt_115_111_Model[:,0],        1E-3*A_Cu*Tilt_115_111_Model[:,1],color="blue",linestyle='-')
    pylab.plot(Tilt_115_111_Model[:,0],        1E-3*A_Au*Tilt_115_111_Model[:,1],color="green",linestyle='-')
else:
    pylab.plot(Tilt_115_111_Model[:,0],        1E-3*A_Cu*Tilt_115_111_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_115_111_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_115_111_Model_Relaxed[:,1],color="blue",linestyle='-')
    pylab.plot(Tilt_115_111_Model[:,0],        1E-3*A_Au*Tilt_115_111_Model[:,1],color="green",linestyle=':')
    pylab.plot(Tilt_115_111_Model_Relaxed[:,0],1E-3*A_Au*Tilt_115_111_Model_Relaxed[:,1],color="green",linestyle='-')
pylab.plot(Tilt_115_111_Wolf_Cu[:,0],1E-3*Tilt_115_111_Wolf_Cu[:,1],color="blue",marker='o',linestyle='')
pylab.plot(Tilt_115_111_Wolf_Au[:,0],1E-3*Tilt_115_111_Wolf_Au[:,1],color="green",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
pylab.tick_params(axis='both', which='major')

pylab.subplot(235)
pylab.xlim(0,90)
pylab.ylim(0,1.00)
if not args.labels_off:
    pylab.title(tex("(221)(001)"))
if unrelaxed:
    pylab.plot(Tilt_221_001_Model[:,0],           1E-3*A_Cu*Tilt_221_001_Model[:,1],color="blue",linestyle='-')
    pylab.plot(Tilt_221_001_Model[:,0],           1E-3*A_Au*Tilt_221_001_Model[:,1],color="green",linestyle='-')
else:
    pylab.plot(Tilt_221_001_Model[:,0],           1E-3*A_Cu*Tilt_221_001_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_221_001_Model_Relaxed[:,0],   1E-3*A_Cu*Tilt_221_001_Model_Relaxed[:,1],color="blue",linestyle='-')
    pylab.plot(90-Tilt_221_001_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_221_001_Model_Relaxed[:,1],color="blue",linestyle='-')
    pylab.plot(Tilt_221_001_Model[:,0],           1E-3*A_Au*Tilt_221_001_Model[:,1],color="green",linestyle=':')
    pylab.plot(Tilt_221_001_Model_Relaxed[:,0],   1E-3*A_Au*Tilt_221_001_Model_Relaxed[:,1],color="green",linestyle='-')
    pylab.plot(90-Tilt_221_001_Model_Relaxed[:,0],1E-3*A_Au*Tilt_221_001_Model_Relaxed[:,1],color="green",linestyle='-')
pylab.plot(Tilt_221_001_Wolf_Cu[:,0],1E-3*Tilt_221_001_Wolf_Cu[:,1],color="blue",marker='o',linestyle='')
pylab.plot(Tilt_221_001_Wolf_Au[:,0],1E-3*Tilt_221_001_Wolf_Au[:,1],color="green",marker='o',linestyle='')
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
pylab.tick_params(axis='both', which='major')

ax = pylab.subplot(236)
pylab.xlim(0,180)
pylab.xticks(numpy.arange(0,180,40)) 
pylab.ylim(0,1.300)
if not args.labels_off:
    pylab.title(tex("(557)(113)"))
if unrelaxed:
    pylab.plot(Tilt_557_113_Model[:,0],        1E-3*A_Cu*Tilt_557_113_Model[:,1],color="blue",linestyle='-',label='Cu (Model)'.ljust(50))
    pylab.plot(Tilt_557_113_Model[:,0],        1E-3*A_Au*Tilt_557_113_Model[:,1],color="green",linestyle='-',label='Au (Model)'.ljust(50))
else:
    pylab.plot(Tilt_557_113_Model[:,0],        1E-3*A_Cu*Tilt_557_113_Model[:,1],color="blue",linestyle=':',label='Cu (Unrelaxed model)'.ljust(60))
    pylab.plot(Tilt_557_113_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_557_113_Model_Relaxed[:,1],color="blue",linestyle='-',label='Cu(Relaxed model)'.ljust(60))
    pylab.plot(Tilt_557_113_Model[:,0],        1E-3*A_Au*Tilt_557_113_Model[:,1],color="green",linestyle=':',label='Au(Unrelaxed model)'.ljust(60))
    pylab.plot(Tilt_557_113_Model_Relaxed[:,0],1E-3*A_Au*Tilt_557_113_Model_Relaxed[:,1],color="green",linestyle='-',label='Au(Relaxed model)'.ljust(60))
pylab.plot(Tilt_557_113_Wolf_Cu[:,0],1E-3*Tilt_557_113_Wolf_Cu[:,1],color="blue",marker='o',linestyle='',label='Cu (MD-LJ)'.ljust(50))
pylab.plot(Tilt_557_113_Wolf_Au[:,0],1E-3*Tilt_557_113_Wolf_Au[:,1],color="green",marker='o',linestyle='',label='Au (MD-EAM)'.ljust(50))
if not args.labels_off:
    pylab.xlabel("Twist angle (degrees)",labelpad=xlabelpad);
    pylab.ylabel("Energy "+tex("(J/m^2)"),labelpad=ylabelpad);
pylab.tick_params(axis='both', which='major')

handles, labels = ax.get_legend_handles_labels()
if not args.labels_off:
    if unrelaxed:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=2)
    else:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=3)

pylab.tight_layout();
if args.tex_off:
    pylab.subplots_adjust(bottom=0.175,left=0.05,right=0.97,top=0.95,wspace=0.2,hspace=0.4);
else :
    pylab.subplots_adjust(bottom=0.175,left=0.05,right=0.98,top=0.95,wspace=0.2,hspace=0.4);


if (filename!=""):
    fig.savefig(filename, bbox_extra_artists=(lgd,), bbox_inches='tight')
else:
    pylab.show()
