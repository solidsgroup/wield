#!/bin/python

from numpy import loadtxt, linspace, meshgrid, arctan2, radians, pi
from scipy.interpolate import griddata
from pylab import subplots,contourf,pcolor,figure,show
from fractional_polar_axes import *

data = loadtxt("out.dat");

rgrid = linspace(0.01,1,100)
thetagrid = linspace(0.1,90,100)
rgrid, thetagrid = meshgrid(rgrid,thetagrid)
r = data[:,0]**2 + data[:,1]**2;
theta = arctan2(data[:,1],data[:,0])*180/pi;
wgrid = griddata((r,theta),data[:,3],(rgrid,thetagrid));
print(r,theta);

fig = figure()
ax = fractional_polar_axes(fig,thlim=(0.01,90),rlim=(0.01,1))
ax.pcolor(thetagrid,rgrid,wgrid);
show()

