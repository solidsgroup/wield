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
A_Cu = 1450
A_Au = 950


Tilt_100_100_Model  = numpy.loadtxt("100_100/outfiles/F1.dat", delimiter=" ");
Tilt_111_111_Model  = numpy.loadtxt("111_111/outfiles/F1.dat", delimiter=" ");
Tilt_114_011_Model  = numpy.loadtxt("114_011/outfiles/F1.dat", delimiter=" ");
Tilt_115_111_Model  = numpy.loadtxt("115_111/outfiles/F1.dat", delimiter=" ");
Tilt_221_001_Model  = numpy.loadtxt("221_001/outfiles/F1.dat", delimiter=" ");
Tilt_557_113_Model  = numpy.loadtxt("557_113/outfiles/F1.dat", delimiter=" ");

Tilt_100_100_Model_Relaxed  = numpy.loadtxt("100_100/outfiles/F2.dat", delimiter=" ");
Tilt_111_111_Model_Relaxed  = numpy.loadtxt("111_111/outfiles/F2.dat", delimiter=" ");
Tilt_114_011_Model_Relaxed  = numpy.loadtxt("114_011/outfiles/F2.dat", delimiter=" ");
Tilt_115_111_Model_Relaxed  = numpy.loadtxt("115_111/outfiles/F2.dat", delimiter=" ");
Tilt_221_001_Model_Relaxed  = numpy.loadtxt("221_001/outfiles/F2.dat", delimiter=" ");
Tilt_557_113_Model_Relaxed  = numpy.loadtxt("557_113/outfiles/F2.dat", delimiter=" ");

Tilt_100_100_Wolf_Cu  = numpy.loadtxt("Wolf/100_100_Cu.dat", delimiter=" ");
Tilt_111_111_Wolf_Cu  = numpy.loadtxt("Wolf/111_111_Cu.dat", delimiter=" ");
Tilt_114_011_Wolf_Cu  = numpy.loadtxt("Wolf/114_011_Cu.dat", delimiter=" ");
Tilt_115_111_Wolf_Cu  = numpy.loadtxt("Wolf/115_111_Cu.dat", delimiter=" ");
Tilt_221_001_Wolf_Cu  = numpy.loadtxt("Wolf/221_001_Cu.dat", delimiter=" ");
Tilt_557_113_Wolf_Cu  = numpy.loadtxt("Wolf/557_113_Cu.dat", delimiter=" ");

Tilt_114_011_Wolf_Au  = numpy.loadtxt("Wolf/114_011_Au.dat", delimiter=" ");
Tilt_115_111_Wolf_Au  = numpy.loadtxt("Wolf/115_111_Au.dat", delimiter=" ");
Tilt_221_001_Wolf_Au  = numpy.loadtxt("Wolf/221_001_Au.dat", delimiter=" ");
Tilt_557_113_Wolf_Au  = numpy.loadtxt("Wolf/557_113_Au.dat", delimiter=" ");

fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches


pylab.subplot(231)
pylab.xlim(0,90)
pylab.title("(100)(100)",fontsize=fontsize_title)
pylab.ylim(0,1.300)
pylab.plot(Tilt_100_100_Model[:,0],
           1E-3*A_Cu*Tilt_100_100_Model[:,1],color="blue",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_100_100_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_100_100_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_100_100_Wolf_Cu[:,0],1E-3*Tilt_100_100_Wolf_Cu[:,1],color="blue",linewidth=linewidth,marker='o',markersize=markersize,linestyle='',label='MD')
pylab.xlabel("Twist angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,columnspacing=1.5,ncol=3,prop={'size':12});

pylab.subplot(232)
pylab.xlim(0,90)
pylab.ylim(0,1.300)
pylab.title("(111)(111)",fontsize=fontsize_title)
pylab.plot(Tilt_111_111_Model[:,0],
           1E-3*A_Cu*Tilt_111_111_Model[:,1],color="blue",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_111_111_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_111_111_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_111_111_Wolf_Cu[:,0],1E-3*Tilt_111_111_Wolf_Cu[:,1],color="blue",linewidth=linewidth,marker='o',markersize=markersize,linestyle='',label='MD')
pylab.xlabel("Twist angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,columnspacing=1.5,ncol=3,prop={'size':12});

pylab.subplot(233)
pylab.xlim(0,180)
pylab.ylim(0,1.500)
pylab.title("(114)(011)",fontsize=fontsize_title)
pylab.plot(Tilt_114_011_Model[:,0],
           1E-3*A_Cu*Tilt_114_011_Model[:,1],color="blue",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_114_011_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_114_011_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(180-Tilt_114_011_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_114_011_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_114_011_Model[:,0],
           1E-3*A_Au*Tilt_114_011_Model[:,1],color="green",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_114_011_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_114_011_Model_Relaxed[:,1],color="green",linewidth=linewidth,linestyle='-')
pylab.plot(180-Tilt_114_011_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_114_011_Model_Relaxed[:,1],color="green",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_114_011_Wolf_Cu[:,0],1E-3*Tilt_114_011_Wolf_Cu[:,1],color="blue",linewidth=linewidth,marker='o',markersize=markersize,linestyle='')
pylab.plot(Tilt_114_011_Wolf_Au[:,0],1E-3*Tilt_114_011_Wolf_Au[:,1],color="green",linewidth=linewidth,marker='o',markersize=markersize,linestyle='')
pylab.xlabel("Twist angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,columnspacing=1.5,ncol=3,prop={'size':12});

pylab.subplot(234)
pylab.xlim(0,60)
pylab.ylim(0,1.300)
pylab.title("(115)(111)",fontsize=fontsize_title)
pylab.plot(Tilt_115_111_Model[:,0],
           1E-3*A_Cu*Tilt_115_111_Model[:,1],color="blue",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_115_111_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_115_111_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_115_111_Model[:,0],
           1E-3*A_Au*Tilt_115_111_Model[:,1],color="green",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_115_111_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_115_111_Model_Relaxed[:,1],color="green",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_115_111_Wolf_Cu[:,0],1E-3*Tilt_115_111_Wolf_Cu[:,1],color="blue",linewidth=linewidth,marker='o',markersize=markersize,linestyle='')
pylab.plot(Tilt_115_111_Wolf_Au[:,0],1E-3*Tilt_115_111_Wolf_Au[:,1],color="green",linewidth=linewidth,marker='o',markersize=markersize,linestyle='')
pylab.xlabel("Twist angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,columnspacing=1.5,ncol=3,prop={'size':12});

pylab.subplot(235)
pylab.xlim(0,90)
pylab.ylim(0,1.300)
pylab.title("(221)(001)",fontsize=fontsize_title)
pylab.plot(Tilt_221_001_Model[:,0],
           1E-3*A_Cu*Tilt_221_001_Model[:,1],color="blue",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_221_001_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_221_001_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(90-Tilt_221_001_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_221_001_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_221_001_Model[:,0],
           1E-3*A_Au*Tilt_221_001_Model[:,1],color="green",linewidth=linewidth,linestyle=':')
pylab.plot(Tilt_221_001_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_221_001_Model_Relaxed[:,1],color="green",linewidth=linewidth,linestyle='-')
pylab.plot(90-Tilt_221_001_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_221_001_Model_Relaxed[:,1],color="green",linewidth=linewidth,linestyle='-')
pylab.plot(Tilt_221_001_Wolf_Cu[:,0],1E-3*Tilt_221_001_Wolf_Cu[:,1],color="blue",linewidth=linewidth,marker='o',markersize=markersize,linestyle='')
pylab.plot(Tilt_221_001_Wolf_Au[:,0],1E-3*Tilt_221_001_Wolf_Au[:,1],color="green",linewidth=linewidth,marker='o',markersize=markersize,linestyle='')
pylab.xlabel("Twist angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,columnspacing=1.5,ncol=3,prop={'size':12});

ax = pylab.subplot(236)
pylab.xlim(0,180)
pylab.ylim(0,1.500)
pylab.title("(557)(113)",fontsize=fontsize_title)
pylab.plot(Tilt_557_113_Model[:,0],
           1E-3*A_Cu*Tilt_557_113_Model[:,1],color="blue",linewidth=linewidth,linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_557_113_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_557_113_Model_Relaxed[:,1],color="blue",linewidth=linewidth,linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_557_113_Model[:,0],
           1E-3*A_Au*Tilt_557_113_Model[:,1],color="green",linewidth=linewidth,linestyle=':',label='Au(Cov)')
pylab.plot(Tilt_557_113_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_557_113_Model_Relaxed[:,1],color="green",linewidth=linewidth,linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_557_113_Wolf_Cu[:,0],1E-3*Tilt_557_113_Wolf_Cu[:,1],color="blue",linewidth=linewidth,marker='o',markersize=markersize,linestyle='',label='Cu(LJ)')
pylab.plot(Tilt_557_113_Wolf_Au[:,0],1E-3*Tilt_557_113_Wolf_Au[:,1],color="green",linewidth=linewidth,marker='o',markersize=markersize,linestyle='',label='Au(EAM)')
pylab.xlabel("Twist angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,columnspacing=1.5,ncol=3,prop={'size':12});

handles, labels = ax.get_legend_handles_labels()
lgd = pylab.figlegend(handles, labels, loc = 'lower center', ncol=3,prop={'size':fontsize_legend})

pylab.tight_layout();
pylab.subplots_adjust(bottom=0.175,left=0.05,right=0.98,top=0.95,wspace=0.2,hspace=0.4);
pylab.show();

