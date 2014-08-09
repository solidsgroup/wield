#!/usr/bin/python
import pylab
import numpy
from matplotlib.widgets import Slider

num = 1

dat = numpy.loadtxt("outfiles/00_00.dat")
#dat = numpy.loadtxt("112.dat")
pylab.polar(3.14159*dat[:,0]/180,dat[:,1],color='green',linewidth=1,linestyle='-',label='unrelaxed')
pylab.polar(3.14159*dat[:,0]/180,dat[:,2],color='blue',linewidth=2,linestyle='-',label='relaxed')
pylab.polar(-3.14159*dat[:,0]/180,dat[:,1],color='green',linewidth=1,linestyle='-',label='unrelaxed')
pylab.polar(-3.14159*dat[:,0]/180,dat[:,2],color='blue',linewidth=2,linestyle='-',label='relaxed')
pylab.polar(3.14159 + 3.14159*dat[:,0]/180,dat[:,1],color='green',linewidth=1,linestyle='-',label='unrelaxed')
pylab.polar(3.14159 + 3.14159*dat[:,0]/180,dat[:,2],color='blue',linewidth=2,linestyle='-',label='relaxed')
pylab.polar(3.14159 - 3.14159*dat[:,0]/180,dat[:,1],color='green',linewidth=1,linestyle='-',label='unrelaxed')
pylab.polar(3.14159 - 3.14159*dat[:,0]/180,dat[:,2],color='blue',linewidth=2,linestyle='-',label='relaxed')


pylab.tight_layout();
pylab.show();
