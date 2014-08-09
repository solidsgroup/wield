#!/bin/python
import argparse
from numpy import loadtxt, linspace, meshgrid, arctan2, pi, radians,degrees,concatenate,cos,sin
from scipy.interpolate import griddata
from pylab import subplots,contourf,pcolor,figure,show,colorbar,pcolormesh
from fractional_polar_axes import *

parser = argparse.ArgumentParser(description='Create a polar surface plot');
parser.add_argument('file', help='Data file for plotting');
parser.add_argument('-r', '--resolution', nargs=2, default=[100,100], help='Resolution in the r and theta directions, respectively')
parser.add_argument('-l', '--theta-limit', nargs=2, default=[-180,180], help='Maximum polar angle')
parser.add_argument('-x', '--x-symmetry', dest='xsim', action='store_true', help='Reflect along the x axis');
parser.add_argument('-y', '--y-symmetry', dest='ysim', action='store_true', help='Reflect along the y axis');
parser.add_argument('-m', '--method', default='nearest', help='Interpolation method: options are nearest, linear, cubic');
args=parser.parse_args();

data = loadtxt(args.file);
x = data[:,0];
y = data[:,1];
w = data[:,3];

if args.xsim:
    x = concatenate([x,x])
    y = concatenate([y,-y])
    w = concatenate([w,w])
if args.ysim:
    x = concatenate([x,-x])
    y = concatenate([y,y])
    w = concatenate([w,w])

rgrid = linspace(0.0,1,args.resolution[0])
thetagrid = linspace(float(args.theta_limit[0]),float(args.theta_limit[1]),args.resolution[1])
rgrid, thetagrid = meshgrid(rgrid,thetagrid)
wgrid = griddata((x,y),w,(rgrid*cos(radians(thetagrid)),rgrid*sin(radians(thetagrid))),fill_value=0,method=args.method);

if float(args.theta_limit[1])-float(args.theta_limit[0]) > 180:
    fig,ax = subplots(ncols=1,subplot_kw=dict(projection='polar'))
    ax.xaxis.set_ticklabels([])
    ax.yaxis.set_ticklabels([])
    pc = ax.pcolormesh(radians(thetagrid),rgrid,wgrid,shading='gouraud');
    #pc = ax.pcolormesh(radians(thetagrid),rgrid,wgrid);
    colorbar(pc)
else:
    fig = figure()
    ax = fractional_polar_axes(fig,thlim=(float(args.theta_limit[0]),float(args.theta_limit[1])),rlim=(0.0,1))
    pc = ax.pcolormesh(thetagrid,rgrid,wgrid,shading='gouraud');
    colorbar(pc)
show()

