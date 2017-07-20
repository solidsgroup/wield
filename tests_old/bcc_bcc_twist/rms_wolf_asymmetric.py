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
A_Mo = 2525
A_Fe = 1700
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


for data, model, multiplier, description in [
    [Tilt_114_011_Wolf_Mo, Tilt_114_011_Model, A_Mo, "114 011 Wolf Mo"],
    [Tilt_115_111_Wolf_Mo, Tilt_115_111_Model, A_Mo, "115 111 Wolf Mo"],
    [Tilt_158_031_Wolf_Mo, Tilt_158_031_Model, A_Mo, "158 031 Wolf Mo"],
    [Tilt_221_001_Wolf_Mo, Tilt_221_001_Model, A_Mo, "221 001 Wolf Mo"],
    [Tilt_552_112_Wolf_Mo, Tilt_552_112_Model, A_Mo, "552 112 Wolf Mo"],
    [Tilt_114_011_Wolf_Fe, Tilt_114_011_Model, A_Fe, "114 011 Wolf Fe"],
    [Tilt_115_111_Wolf_Fe, Tilt_115_111_Model, A_Fe, "115 111 Wolf Fe"],
    [Tilt_158_031_Wolf_Fe, Tilt_158_031_Model, A_Fe, "158 031 Wolf Fe"],
    [Tilt_221_001_Wolf_Fe, Tilt_221_001_Model, A_Fe, "221 001 Wolf Fe"],
    [Tilt_552_112_Wolf_Fe, Tilt_552_112_Model, A_Fe, "552 112 Wolf Fe"]
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
