#!/bin/python
import argparse
from math import atan2
from numpy import loadtxt, linspace, meshgrid, arctan2, pi, radians,degrees,concatenate,cos,sin,sqrt
from scipy.interpolate import griddata, interp2d
from pylab import subplots,contourf,pcolor,figure,draw,ginput,show,colorbar,pcolormesh,savefig,plot,ion,pause,clf
from fractional_polar_axes import *
import sys

parser = argparse.ArgumentParser(description='Create a polar surface plot');
parser.add_argument('file', help='Data file for plotting');
parser.add_argument('-r', '--resolution', nargs=2, default=[100,100], help='Resolution in the r and theta directions, respectively')
parser.add_argument('-l', '--theta-limit', nargs=2, default=[-180,180], help='Maximum polar angle')
parser.add_argument('-x', '--x-symmetry', dest='xsim', action='store_true', help='Reflect along the x axis');
parser.add_argument('-y', '--y-symmetry', dest='ysim', action='store_true', help='Reflect along the y axis');
parser.add_argument('-i', '--interactive', dest='interactive', action='store_true', help='Interactive facet investigator');
parser.add_argument('-m', '--method', default='nearest', help='Interpolation method: options are nearest, linear, cubic');
parser.add_argument('-n1','--n1', nargs=2, default=[0,2], help='First Facet vector');
parser.add_argument('-n2','--n2', nargs=2, default=[0,2], help='Second Facet vector');
parser.add_argument('-n3','--n3', nargs=2, default=[0,2], help='Third Facet vector');
parser.add_argument('-f', '--facet-file', default="", help='Facet data input file');
parser.add_argument('-o', '--output-file', default="", help='Image output file');
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
wgrid   = griddata((x,y),w,(rgrid*cos(radians(thetagrid)),rgrid*sin(radians(thetagrid))),fill_value=0,method=args.method);

if float(args.theta_limit[1])-float(args.theta_limit[0]) > 180:
    fig,ax = subplots(ncols=1,subplot_kw=dict(projection='polar'))
    ax.xaxis.set_ticklabels([])
    ax.yaxis.set_ticklabels([])
    pc = pcolormesh(radians(thetagrid),rgrid,wgrid,shading='gouraud');
    #pc = ax.pcolormesh(radians(thetagrid),rgrid,wgrid);
    colorbar(pc)
else:
    fig = figure()
    ax = fractional_polar_axes(fig,thlim=(float(args.theta_limit[0]),float(args.theta_limit[1])),rlim=(0.0,1))
    pc = pcolormesh(thetagrid,rgrid,wgrid,shading='gouraud');
    colorbar(pc)


rr = []; tt = [];
if float(args.n1[0])**2 + float(args.n1[1])**2 <= 1:
    rr.append(sqrt(float(args.n1[0])**2 + float(args.n1[1])**2))
    tt.append(atan2(float(args.n1[1]),float(args.n1[0])))
    if float(args.n2[0])**2 + float(args.n2[1])**2 <= 1:
        rr.append(sqrt(float(args.n2[0])**2 + float(args.n2[1])**2))
        tt.append(atan2(float(args.n2[1]),float(args.n2[0])))
        if float(args.n3[0])**2 + float(args.n3[1])**2 <= 1:
            rr.append(sqrt(float(args.n3[0])**2 + float(args.n3[1])**2))
            tt.append(atan2(float(args.n3[1]),float(args.n3[0])))
    rr.append(sqrt(float(args.n1[0])**2 + float(args.n1[1])**2))
    tt.append(atan2(float(args.n1[1]),float(args.n1[0])))
    plot(tt,rr,marker='o');

if args.facet_file != "":
    rr = []; tt = []; lamb = []
    n1=[]; n2=[]; n3=[];
    file=open(args.facet_file,'r');
    file.readline(); #skip past energy
    lambStr = file.readline().split(); #skip past lambda
    lamb.append(float(lambStr[0]));
    lamb.append(float(lambStr[1]));
    lamb.append(float(lambStr[2]));

    xStr = file.readline().split();
    yStr = file.readline().split();
    n1.append(float(xStr[0])); n2.append(float(xStr[1])); n3.append(float(xStr[2]))
    n1.append(float(yStr[0])); n2.append(float(yStr[1])); n3.append(float(yStr[2]))

    if (lamb[0] > 1E-6):
        rr.append(sqrt(float(n1[0])**2 + float(n1[1])**2))
        tt.append(atan2(float(n1[1]),float(n1[0])))

    if (lamb[1] > 1E-6):
        rr.append(sqrt(float(n2[0])**2 + float(n2[1])**2))
        tt.append(atan2(float(n2[1]),float(n2[0])))

    if (lamb[2] > 1E-6):
        rr.append(sqrt(float(n3[0])**2 + float(n3[1])**2))
        tt.append(atan2(float(n3[1]),float(n3[0])))

    if (lamb[0] > 1E-6):
        rr.append(sqrt(float(n1[0])**2 + float(n1[1])**2))
        tt.append(atan2(float(n1[1]),float(n1[0])))

    plot(tt,rr,marker='o',color='black');

plot(0,0,color='white',marker='o');

if args.output_file != "":
    savefig(args.output_file);
elif args.interactive:
    ion();
    show(); pause(1);

    while True:
        io = input("Enter a command: ")
        if (io == 'q'):
            exit();
        if (io == '1'):
            print(griddata((x,y),w,(0,0),fill_value=0,method=args.method));
        if (io == '3'):
            pts = ginput(3,timeout=-1);
            n = np.array([[0.,0.,0.],[0.,0.,0.],[0.,0.,0.]])
            e = np.array([0.,0.,1.])
            print(pts);

            n[0][0] = cos(pts[0][0])*pts[0][1]; n[1][0] = sin(pts[0][0])*pts[0][1];  n[2][0] = sqrt(1 - n[0][0]**2 - n[1][0]**2);
            n[0][1] = cos(pts[1][0])*pts[1][1]; n[1][1] = sin(pts[1][0])*pts[1][1];  n[2][1] = sqrt(1 - n[0][1]**2 - n[1][1]**2);
            n[0][2] = cos(pts[2][0])*pts[2][1]; n[1][2] = sin(pts[2][0])*pts[2][1];  n[2][2] = sqrt(1 - n[0][2]**2 - n[1][2]**2);

            lamb = np.linalg.solve(n,e);

            print (n);
            print (lamb);
            print ("Wc = ", 
                   lamb[0]*griddata((x,y),w,(n[0][0], n[1][0]),fill_value=0,method=args.method) +
                   lamb[1]*griddata((x,y),w,(n[0][1], n[1][1]),fill_value=0,method=args.method) +
                   lamb[2]*griddata((x,y),w,(n[0][2], n[1][2]),fill_value=0,method=args.method))

            tt = [pts[0][0],pts[1][0],pts[2][0],pts[0][0]];
            rr = [pts[0][1],pts[1][1],pts[2][1],pts[0][1]];
            plot(tt,rr,marker='o');
            show(); pause(1);
            #print(griddata((x,y),w,(cos(pts[0][0])*pts[0][1], sin(pts[0][0])*pts[0][1]),fill_value=0,method=args.method));
    show()
else:
    show()

