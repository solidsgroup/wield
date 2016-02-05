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

for data, model, maxangle, multiplier, description in [
    [Tilt_001_001_Wolf_Fe, Tilt_001_001_Model, 45, A_Fe, "001 001 Wolf Fe"],
    [Tilt_011_011_Wolf_Fe, Tilt_011_011_Model, 90, A_Fe, "011 011 Wolf Fe"],
    [Tilt_031_031_Wolf_Fe, Tilt_031_031_Model, 180, A_Fe, "031 031 Wolf Fe"],
    [Tilt_111_111_Wolf_Fe, Tilt_111_111_Model, 60, A_Fe, "111 111 Wolf Fe"],
    [Tilt_112_112_Wolf_Fe, Tilt_112_112_Model, 180, A_Fe, "112 112 Wolf Fe"]
    ]:

    print(description);
    model_interp = interp1d(model[:,0],multiplier*model[:,1]);
    ErrorNorm=0;
    Norm=0;

    for (x,y) in data:
        if (x>maxangle): break;
        ErrorNorm += (y - model_interp(x))**2;
        Norm += y**2;
    ErrorNorm = numpy.sqrt(ErrorNorm);
    Norm = numpy.sqrt(Norm);
    print(ErrorNorm,Norm,ErrorNorm/Norm);
