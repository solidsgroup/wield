#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import numpy
import argparse
from scipy.interpolate import interp1d

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

for data, model, multiplier, description in [
    [Tilt_100_100_Wolf_Cu, Tilt_100_100_Model, A_Cu, "100 100 Wolf Cu"],
    [Tilt_111_111_Wolf_Cu, Tilt_111_111_Model, A_Cu, "111 111 Wolf Cu"],
    [Tilt_114_011_Wolf_Cu, Tilt_114_011_Model, A_Cu, "114 011 Wolf Cu"],
    [Tilt_115_111_Wolf_Cu, Tilt_115_111_Model, A_Cu, "115 111 Wolf Cu"],
    [Tilt_221_001_Wolf_Cu, Tilt_221_001_Model, A_Cu, "221 001 Wolf Cu"],
    [Tilt_557_113_Wolf_Cu, Tilt_557_113_Model, A_Cu, "557 113 Wolf Cu"],
    [Tilt_114_011_Wolf_Au, Tilt_114_011_Model, A_Au, "114 011 Wolf Au"],
    [Tilt_115_111_Wolf_Au, Tilt_115_111_Model, A_Au, "115 111 Wolf Au"],
    [Tilt_221_001_Wolf_Au, Tilt_221_001_Model, A_Au, "221 001 Wolf Au"],
    [Tilt_557_113_Wolf_Au, Tilt_557_113_Model, A_Au, "557 113 Wolf Au"]
    ]:

    print(description);
    model_interp = interp1d(model[:,0],multiplier*model[:,1]);
    ErrorNorm=0;
    Norm=0;

    for (x,y) in data:
        ErrorNorm += (y - model_interp(x))**2;
        Norm += y**2;
    ErrorNorm = numpy.sqrt(ErrorNorm);
    Norm = numpy.sqrt(Norm);
    print(ErrorNorm,Norm,ErrorNorm/Norm);



