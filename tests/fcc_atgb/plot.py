#!/usr/bin/python
import pylab
import numpy


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
for f in filenames:
    dat = numpy.loadtxt(f,delimiter=" ");
    pylab.plot(dat[:,0],dat[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(dat[:,0],dat[:,2],color="blue",linewidth="2",linestyle='--')
    pylab.plot(dat[90,0],dat[90,2],color="blue",linestyle="",marker="o");
    pylab.show();
    energies.append(dat[90,1]);
    relaxedEnergies.append(dat[90,2]);

pylab.plot(angles,energies,color="blue",linewidth="2",linestyle='-',marker='o')
pylab.plot(angles,relaxedEnergies,color="blue",linewidth="2",linestyle='-',marker='o')
pylab.show();
