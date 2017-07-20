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

for data, model, multiplier, description in [
    [Tilt_001_Wolf_Mo, Tilt_001_Model, A_Mo, "001 Wolf Mo"],
    [Tilt_110_Wolf_Mo, Tilt_110_Model, A_Mo, "110 Wolf Mo"],
    [Tilt_111_Wolf_Mo, Tilt_111_Model, A_Mo, "111 Wolf Mo"],
    [Tilt_112_Wolf_Mo, Tilt_112_Model, A_Mo, "112 Wolf Mo"],
    [Tilt_001_Wolf_Fe, Tilt_001_Model, A_Fe, "001 Wolf Fe"],
    [Tilt_110_Wolf_Fe, Tilt_110_Model, A_Fe, "110 Wolf Fe"],
    [Tilt_111_Wolf_Fe, Tilt_111_Model, A_Fe, "111 Wolf Fe"],
    [Tilt_112_Wolf_Fe, Tilt_112_Model, A_Fe, "112 Wolf Fe"]]:

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
