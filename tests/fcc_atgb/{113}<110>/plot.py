#!/usr/bin/python
import numpy
import pylab
import argparse


angles=numpy.array([180,154.5,125.1,111.6,100.2,84.3,65.1,45.6,29.7,4.26,-25.24,-54.9,-68.7,-80.1,-95.7,-114.9,-134.4,-150.6])
#angles=numpy.arange(-180,180,20)

parser = argparse.ArgumentParser(description='Create a polar line plot')
parser.add_argument('file', help='Data file for plotting');
parser.add_argument('-f','--file', default="", help='Input file name');
parser.add_argument('-o','--output-file', default="", help='Output file name');
parser.add_argument('-t', '--tex-off', dest='tex_off', action='store_true', help='Render without using latex');

args = parser.parse_args()
if args.tex_off:
    def tex(a): return '\$'+a+'\$'
else:
    def tex(a): return '$'+a+'$'

data = numpy.loadtxt(args.file)

theta = numpy.radians(data[:,0])
w     = data[:,1]
wc    = data[:,2]
wulff = data[:,3]

fig = pylab.figure(figsize=(3,3)); #inches
ax = pylab.subplot(111,polar=True)
ax.set_theta_zero_location('N')
ax.set_yticklabels([])

ax.grid(color='gray', linestyle=':', linewidth=0.25)

# theta labels ranging from [-180 to 180] 
pylab.thetagrids(angles%360,[tex(r''+str(a)+r'^\circ') for a in angles],frac=1.2)

# plot unrelaxed, relaxed shapes
pylab.polar(         theta,w, color='blue',linewidth=0.5)
pylab.polar(numpy.pi+theta,w, color='blue',linewidth=0.5)
pylab.polar(         theta,wc,color='blue',linewidth=1.5)
pylab.polar(numpy.pi+theta,wc,color='blue',linewidth=1.5)

pylab.fill(         theta,wulff,color='navajowhite')
pylab.fill(numpy.pi+theta,wulff,color='navajowhite')
pylab.polar(         theta,wulff,color='darkorange')
pylab.polar(numpy.pi+theta,wulff,color='darkorange')
#pylab.polar([0,0],[0,w[0]],color='black')

#pylab.Polygon([[0,0],[1.5,.5],[0,1]],closed=True,edgecolor='blue')
#ax.fill([0,numpy.pi/2,numpy.pi],[0,0.1,0.1])


pylab.tight_layout()

if (args.output_file !=""):
    fig.savefig(args.output_file)
else:
    pylab.show()


