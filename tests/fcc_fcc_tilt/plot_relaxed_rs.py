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
A_Cu = 1450
A_Au = 950
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

# Read Shockley parameters

C11 = 168.40E9
C12 = 121.40E9
C44 = 75.40E9
a = 3.597E-10
r0 = 0.5*a
sigma100 = C12/(C11+C12)
alpha = 2*C44/(C11-C12)
ElasticMultiplier = (C44/(1-sigma100)) * numpy.sqrt(2*(1-sigma100)/(alpha*(1+alpha*(1-2*sigma100)))) 
E0 = a * ElasticMultiplier * (numpy.cos(0) + numpy.sin(0)) / (4 * numpy.pi)
A = 1 + numpy.log(a/(2*numpy.pi*r0))

RS_X = numpy.linspace(0,15,100)
RS_Y = E0*numpy.radians(RS_X)*(A-numpy.log(numpy.radians(RS_X+1E-8)))

Tilt_001_Model  = numpy.loadtxt("100_2d/outfiles/F1.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111_2d/outfiles/F1.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("110_2d/outfiles/F1.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("112_2d/outfiles/F1.dat", delimiter=" ");

Tilt_001_Model_Relaxed  = numpy.loadtxt("100_2d/outfiles/F2.dat", delimiter=" ");
Tilt_111_Model_Relaxed  = numpy.loadtxt("111_2d/outfiles/F2.dat", delimiter=" ");
Tilt_110_Model_Relaxed  = numpy.loadtxt("110_2d/outfiles/F2.dat", delimiter=" ");
Tilt_112_Model_Relaxed  = numpy.loadtxt("112_2d/outfiles/F2.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

pylab.subplot(221)
pylab.xlim(0,90)
pylab.ylim(0,1.)
if unrelaxed:
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Cu*Tilt_001_Model[:,1],color="blue",linestyle='-')
else:
    pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Cu*Tilt_001_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_001_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_001_Model_Relaxed[:,1],color="blue",linestyle='-')
pylab.plot(RS_X,RS_Y,color="black")
pylab.plot(90-RS_X,RS_Y,color="black")
if not args.labels_off:
    pylab.xlabel(xlabel(tex(r'[100]')+' tilt angle '+tex(r'\theta')),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);
offset=0.5
if args.annotate:
    pylab.annotate(tex(r'(001)(001)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}3)(013)'), xycoords=('data','axes fraction'), xy=(36.41+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(0\bar{1}1)(011)'), xycoords=('data','axes fraction'), xy=(90+offset,1.05),va="bottom", ha="center",rotation=90)

pylab.subplot(222)
pylab.xlim(0,180)
pylab.ylim(0,1.)
if unrelaxed:
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Cu*Tilt_110_Model[:,1],color="blue",linestyle='-')
else:
    pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Cu*Tilt_110_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_110_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_110_Model_Relaxed[:,1],color="blue",linestyle='-')
pylab.plot(RS_X,RS_Y,color="black")
pylab.plot(70.6+RS_X,RS_Y,color="black")
pylab.plot(70.6-RS_X,RS_Y,color="black")
pylab.plot(180-RS_X,RS_Y,color="black")
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

pylab.subplot(223)
pylab.xlim(0,60)
pylab.ylim(0,1)
if unrelaxed:
    pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Cu*Tilt_111_Model[:,1],color="blue",linestyle='-')
else:
    pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Cu*Tilt_111_Model[:,1],color="blue",linestyle=':')
    pylab.plot(Tilt_111_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_111_Model_Relaxed[:,1],color="blue",linestyle='-')
pylab.plot(RS_X,RS_Y,color="black")
if not args.labels_off:
    pylab.xlabel(xlabel(tex(r'[111]')+' tilt angle '+tex(r'\theta')),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);
offset = 0.5
if args.annotate:
    pylab.annotate(tex(r'(10\bar{1})(10\bar{1})'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(11\bar{2})(2\bar{1}\bar{1})'), xycoords=('data','axes fraction'), xy=(60+offset,1.05),va="bottom", ha="center",rotation=90)

ax = pylab.subplot(224)
pylab.xlim(0,110)
pylab.ylim(0,1.)
if unrelaxed:
    pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Cu*Tilt_112_Model[:,1],color="blue",linestyle='-',label=legend('Cu (Model)').ljust(50))
else:
    pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Cu*Tilt_112_Model[:,1],color="blue",linestyle=':',label=legend('Cu (Unrelaxed model)').ljust(60))
    pylab.plot(Tilt_112_Model_Relaxed[:,0],1E-3*A_Cu*Tilt_112_Model_Relaxed[:,1],color="blue",linestyle='-',label=legend('Cu (Relaxed model)').ljust(60))
pylab.plot(RS_X,RS_Y,color="black",label=legend('Read-Shockley').ljust(60))
if not args.labels_off:
    pylab.xlabel(xlabel(tex(r'[112]')+' tilt angle '+tex(r'\theta')),labelpad=xlabelpad);
    pylab.ylabel(ylabel("Energy "+tex("(J/m^2)")),labelpad=ylabelpad);
offset=0.9
if args.annotate:
    pylab.annotate(tex(r'(1\bar{1}0)(1\bar{1}0)'), xycoords=('data','axes fraction'), xy=(0+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(3\bar{1}\bar{1})(3\bar{1}1)'), xycoords=('data','axes fraction'), xy=(62.8+offset,1.05),va="bottom", ha="center",rotation=90)
    pylab.annotate(tex(r'(20\bar{1})(201)'), xycoords=('data','axes fraction'), xy=(101.7+offset,1.05),va="bottom", ha="center",rotation=90)

handles, labels = ax.get_legend_handles_labels()
if not args.labels_off:
    if unrelaxed:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=3)
    else:
        lgd = pylab.figlegend(handles, labels, loc = legend_loc, ncol=2)

pylab.tight_layout();
if args.annotate: pylab.subplots_adjust(bottom=0.175,left=0.075,right=0.98,top=0.875,wspace=0.2,hspace=0.75)
else:             pylab.subplots_adjust(bottom=0.2,left=0.075,right=0.98,top=0.975,wspace=0.2,hspace=0.25)
if (filename!=""):
    fig.savefig(filename, bbox_extra_artists=(lgd,), bbox_inches='tight')
else:
    pylab.show()

