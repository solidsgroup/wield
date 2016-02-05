#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import numpy
import argparse
import pylab
from scipy.interpolate import interp1d

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
A_Cu = 1450
A_Au = 950
#texing
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


Tilt_001_Model  = numpy.loadtxt("100_2d/outfiles/F1.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("110_2d/outfiles/F1.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111_2d/outfiles/F1.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("112_2d/outfiles/F1.dat", delimiter=" ");

Tilt_001_Model_Relaxed  = numpy.loadtxt("100_2d/outfiles/F2.dat", delimiter=" ");
Tilt_110_Model_Relaxed  = numpy.loadtxt("110_2d/outfiles/F2.dat", delimiter=" ");
Tilt_111_Model_Relaxed  = numpy.loadtxt("111_2d/outfiles/F2.dat", delimiter=" ");
Tilt_112_Model_Relaxed  = numpy.loadtxt("112_2d/outfiles/F2.dat", delimiter=" ");

Tilt_001_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/100_Cu_LJ.dat", delimiter=" ");
Tilt_110_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/110_Cu_LJ.dat", delimiter=" ");
Tilt_111_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/111_Cu_LJ.dat", delimiter=" ");
Tilt_112_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/112_Cu_LJ.dat", delimiter=" ");

Tilt_001_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/100_Cu_EAM.dat", delimiter=" ");
Tilt_110_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/110_Cu_EAM.dat", delimiter=" ");
Tilt_111_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/111_Cu_EAM.dat", delimiter=" ");
Tilt_112_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/112_Cu_EAM.dat", delimiter=" ");

Tilt_001_Wolf_Au_EAM  = numpy.loadtxt("Wolf/100_Au_EAM.dat", delimiter=" ");
Tilt_110_Wolf_Au_EAM  = numpy.loadtxt("Wolf/110_Au_EAM.dat", delimiter=" ");
Tilt_111_Wolf_Au_EAM  = numpy.loadtxt("Wolf/111_Au_EAM.dat", delimiter=" ");
Tilt_112_Wolf_Au_EAM  = numpy.loadtxt("Wolf/112_Au_EAM.dat", delimiter=" ");


for data, model, multiplier, description in [
    [Tilt_001_Wolf_Cu_LJ, Tilt_001_Model, A_Cu, "001 Wolf Cu LJ"],
    [Tilt_110_Wolf_Cu_LJ, Tilt_110_Model, A_Cu, "011 Wolf Cu LJ"],
    [Tilt_111_Wolf_Cu_LJ, Tilt_111_Model, A_Cu, "111 Wolf Cu LJ"],
    [Tilt_112_Wolf_Cu_LJ, Tilt_112_Model, A_Cu, "112 Wolf Cu LJ"],
    [Tilt_001_Wolf_Cu_EAM, Tilt_001_Model, A_Cu, "001 Wolf Cu EAM"],
    [Tilt_110_Wolf_Cu_EAM, Tilt_110_Model, A_Cu, "011 Wolf Cu EAM"],
    [Tilt_111_Wolf_Cu_EAM, Tilt_111_Model, A_Cu, "111 Wolf Cu EAM"],
    [Tilt_112_Wolf_Cu_EAM, Tilt_112_Model, A_Cu, "112 Wolf Cu EAM"],
    [Tilt_001_Wolf_Au_EAM, Tilt_001_Model, A_Au, "001 Wolf Au EAM"],
    [Tilt_110_Wolf_Au_EAM, Tilt_110_Model, A_Au, "011 Wolf Au EAM"],
    [Tilt_111_Wolf_Au_EAM, Tilt_111_Model, A_Au, "111 Wolf Au EAM"],
    [Tilt_112_Wolf_Au_EAM, Tilt_112_Model, A_Au, "112 Wolf Au EAM"]]:

    print(description);
    model_interp = interp1d(model[:,0],multiplier*model[:,1]);
    ErrorNorm=0;
    Norm=0;

    #pylab.plot(data[:,0],data[:,1]);
    #pylab.plot(data[:,0],model_interp(data[:,0]));
    #pylab.show();

    for (x,y) in data:
        ErrorNorm += (y - model_interp(x))**2;
        Norm += y**2;
    ErrorNorm = numpy.sqrt(ErrorNorm);
    Norm = numpy.sqrt(Norm);
    print(ErrorNorm,Norm,ErrorNorm/Norm);



