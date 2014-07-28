#!/usr/bin/python
import pylab
import numpy
from matplotlib.widgets import Slider

num = 1

filenames = ["outfiles/00_00.dat",
             "outfiles/06_21.dat",
             "outfiles/10_02.dat",
             "outfiles/13_26.dat",
             "outfiles/15_79.dat",
             "outfiles/19_47.dat",
             "outfiles/22_00.dat",
             "outfiles/25_24.dat",
             "outfiles/29_50.dat",
             "outfiles/35_26.dat",
             "outfiles/40_32.dat",
             "outfiles/43_31.dat",
             "outfiles/46_69.dat",
             "outfiles/48_50.dat",
             "outfiles/54_74.dat",
             "outfiles/60_50.dat",
             "outfiles/62_06.dat",
             "outfiles/64_76.dat",
             "outfiles/67_01.dat",
             "outfiles/70_53.dat",
             "outfiles/74_21.dat",
             "outfiles/79_98.dat",
             "outfiles/81_95.dat",
             "outfiles/90_00.dat"]

angles = [00.00,
          06.21,
          10.02,
          13.26,
          15.79,
          19.47,
          22.00,
          25.24,
          29.50,
          35.26,
          40.32,
          43.31,
          46.69,
          48.50,
          54.74,
          60.50,
          62.06,
          64.76,
          67.01,
          70.53,
          74.21,
          79.98,
          81.95,
          90.00]



energies = [];
relaxedEnergies = [];
num;
for f in filenames:
    dat = numpy.loadtxt(f,delimiter=' ');
    num = len(dat[:,1])/2;
    energies.append(dat[num,1]);
    relaxedEnergies.append(dat[num,2]);

pylab.subplot(121)
pylab.axis();
pltUnrelaxed, = pylab.plot(dat[:,0],dat[:,1],color='green',linewidth=2,linestyle='--',label='unrelaxed')
pltRelaxed, = pylab.plot(dat[:,0],dat[:,2],color='blue',linewidth=2,linestyle='-',label='relaxed')
pylab.plot([[0,0], [0,2]])
pylab.ylabel('Energy');
pylab.xlabel('Interface angle');
pylab.legend(loc='lower center');

pylab.subplot(122)
pylab.axis();
pylab.xlim(min(angles),max(angles));
pltZeroUnrelaxed, = pylab.plot(angles,energies,color='green',linewidth=2,linestyle='--',label='unrelaxed')
pltZeroRelaxed,   = pylab.plot(angles,relaxedEnergies,color='blue',linewidth=2,linestyle='-',label='relaxed')
pylab.ylim(0,max(energies));
# Data from Tschopp and McDowell
tschoppDat = numpy.loadtxt('Tschopp.dat');
plotTschopp, = pylab.plot(tschoppDat[:,0],tschoppDat[:,1]-tschoppDat[0,1],linewidth=2,linestyle='--',marker='o',color='red',label='MD (Tschopp)')
pylab.xlabel('Misorientation Angle');
pylab.ylabel('Energy');
pylab.legend(loc='lower right')


pnum = Slider(pylab.axes([0.25,0.04,0.65,0.01]),'Theta',1,len(energies)+1,valinit=len(energies)+1);
tschoppSlider = Slider(pylab.axes([0.25,0.02,0.65,0.01]),'Tschopp',0,0.005,0);

def updatePnum(val):
    dat = numpy.loadtxt(filenames[int(val)-1]);
    pltUnrelaxed.set_ydata(dat[:,1]);
    pltRelaxed.set_ydata(dat[:,2]);
    pltZeroUnrelaxed.set_data(angles[:int(val)],energies[:int(val)]);
    pltZeroRelaxed.set_data(angles[:int(val)],relaxedEnergies[:int(val)]);
pnum.on_changed(updatePnum);
def updateTschopp(val):
    plotTschopp.set_data(tschoppDat[:,0],val*(tschoppDat[:,1]-tschoppDat[0,1]));
tschoppSlider.on_changed(updateTschopp)
pylab.tight_layout();
pylab.show();
