#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy


#plot parameters
fig_height_in = 4.5
fig_width_in  = 6.5
linewidth = 1
markersize = 3
fontsize_title = 10
fontsize_legend = 8
fontsize_axis = 6
fontsize_numbers = 6
#data parameters
A_Mo = 2525 # blue
A_Fe = 1950 # green


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

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

pylab.subplot(221)
pylab.title('[100] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,90)
pylab.ylim(0,2)
pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Mo*Tilt_001_Model[:,1],        color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_001_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_001_Model_Relaxed[:,1],color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_001_Model[:,0],        1E-3*A_Fe*Tilt_001_Model[:,1],        color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Au(Cov)')
pylab.plot(Tilt_001_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_001_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_001_Wolf_Mo[:,0],      1E-3*     Tilt_001_Wolf_Mo[:,1],      color="blue", linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Cu(EAM)')
pylab.plot(Tilt_001_Wolf_Fe[:,0],      1E-3*     Tilt_001_Wolf_Fe[:,1],      color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($J/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)

pylab.subplot(222)
pylab.title('[110] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,180)
pylab.ylim(0,2)
pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Mo*Tilt_110_Model[:,1],        color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_110_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_110_Model_Relaxed[:,1],color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_110_Model[:,0],        1E-3*A_Fe*Tilt_110_Model[:,1],        color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Au(Cov)')
pylab.plot(Tilt_110_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_110_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_110_Wolf_Mo[:,0],      1E-3*     Tilt_110_Wolf_Mo[:,1],      color="blue", linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Cu(EAM)')
pylab.plot(Tilt_110_Wolf_Fe[:,0],      1E-3*     Tilt_110_Wolf_Fe[:,1],      color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($J/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)

pylab.subplot(223)
pylab.title('[111] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,60)
pylab.ylim(0,2)
pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Mo*Tilt_111_Model[:,1],        color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_111_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_111_Model_Relaxed[:,1],color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_111_Model[:,0],        1E-3*A_Fe*Tilt_111_Model[:,1],        color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Au(Cov)')
pylab.plot(Tilt_111_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_111_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_111_Wolf_Mo[:,0],      1E-3*     Tilt_111_Wolf_Mo[:,1],      color="blue", linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Cu(EAM)')
pylab.plot(Tilt_111_Wolf_Fe[:,0],      1E-3*     Tilt_111_Wolf_Fe[:,1],      color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($J/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)

ax = pylab.subplot(224)
pylab.title('[112] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,110)
pylab.ylim(0,2)
pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Mo*Tilt_112_Model[:,1],        color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Mo(Cov)')
pylab.plot(Tilt_112_Model_Relaxed[:,0],1E-3*A_Mo*Tilt_112_Model_Relaxed[:,1],color="blue", linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Mo(RCov)')
pylab.plot(Tilt_112_Model[:,0],        1E-3*A_Fe*Tilt_112_Model[:,1],        color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle=':',label='Fe(Cov)')
pylab.plot(Tilt_112_Model_Relaxed[:,0],1E-3*A_Fe*Tilt_112_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='', linestyle='-',label='Fe(RCov)')
pylab.plot(Tilt_112_Wolf_Mo[:,0],      1E-3*     Tilt_112_Wolf_Mo[:,1],      color="blue", linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Mo(EAM)')
pylab.plot(Tilt_112_Wolf_Fe[:,0],      1E-3*     Tilt_112_Wolf_Fe[:,1],      color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='', label='Fe(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($J/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)

handles, labels = ax.get_legend_handles_labels()
lgd = pylab.figlegend(handles, labels, loc = 'lower center', ncol=3,prop={'size':fontsize_legend})

pylab.tight_layout();
pylab.subplots_adjust(bottom=0.175,left=0.05,right=0.98,top=0.95,wspace=0.15,hspace=0.4);
#fig.savefig('/home/brandon/Desktop/figure_1.pdf', bbox_extra_artists=(lgd,), bbox_inches='tight')
pylab.show();

