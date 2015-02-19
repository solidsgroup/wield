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


Tilt_001_Model  = numpy.loadtxt("100_2d/outfiles/F1.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("110_2d/outfiles/F1.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("111_2d/outfiles/F1.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("112_2d/outfiles/F1.dat", delimiter=" ");

Tilt_001_Model_Relaxed  = numpy.loadtxt("100_2d/outfiles/F2.dat", delimiter=" ");
Tilt_110_Model_Relaxed  = numpy.loadtxt("110_2d/outfiles/F2.dat", delimiter=" ");
Tilt_111_Model_Relaxed  = numpy.loadtxt("111_2d/outfiles/F2.dat", delimiter=" ");
Tilt_112_Model_Relaxed  = numpy.loadtxt("112_2d/outfiles/F2.dat", delimiter=" ");

Tilt_001_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/100_Cu_LJ.dat", delimiter=" ");
Tilt_110_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/110_Cu_LJ.dat", delimiter=" ");
Tilt_111_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/111_Cu_LJ.dat", delimiter=" ");
Tilt_112_Wolf_Cu_LJ  = numpy.loadtxt("Wolf/112_Cu_LJ.dat", delimiter=" ");

Tilt_001_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/100_Cu_EAM.dat", delimiter=" ");
Tilt_110_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/110_Cu_EAM.dat", delimiter=" ");
Tilt_111_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/111_Cu_EAM.dat", delimiter=" ");
Tilt_112_Wolf_Cu_EAM  = numpy.loadtxt("Wolf/112_Cu_EAM.dat", delimiter=" ");

Tilt_001_Wolf_Au_EAM  = numpy.loadtxt("Wolf/100_Au_EAM.dat", delimiter=" ");
Tilt_110_Wolf_Au_EAM  = numpy.loadtxt("Wolf/110_Au_EAM.dat", delimiter=" ");
Tilt_111_Wolf_Au_EAM  = numpy.loadtxt("Wolf/111_Au_EAM.dat", delimiter=" ");
Tilt_112_Wolf_Au_EAM  = numpy.loadtxt("Wolf/112_Au_EAM.dat", delimiter=" ");


fig = pylab.figure(figsize=(fig_width_in,fig_height_in)); #inches

pylab.subplot(221)
pylab.title('[100] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,90)
pylab.ylim(0,1.4)
pylab.plot(90-Tilt_001_Model[:,0],
           1E-3*A_Cu*Tilt_001_Model[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle=':',label='Cu(Cov)')
pylab.plot(90-Tilt_001_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_001_Model_Relaxed[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle='-',label='Cu(RCov)')
pylab.plot(90-Tilt_001_Model[:,0],
           1E-3*A_Au*Tilt_001_Model[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle=':',label='Au(Cov)')
pylab.plot(90-Tilt_001_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_001_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_001_Wolf_Cu_LJ[:,0],1E-3*Tilt_001_Wolf_Cu_LJ[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='^',linestyle='',label='Cu(LJ)')
pylab.plot(Tilt_001_Wolf_Cu_EAM[:,0],1E-3*Tilt_001_Wolf_Cu_EAM[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Cu(EAM)')
pylab.plot(Tilt_001_Wolf_Au_EAM[:,0],1E-3*Tilt_001_Wolf_Au_EAM[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=4,prop={'size':fontsize_legend});

pylab.subplot(222)
pylab.title('[110] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,180)
pylab.ylim(0,1.200)
pylab.plot(Tilt_110_Model[:,0],
           1E-3*A_Cu*Tilt_110_Model[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_110_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_110_Model_Relaxed[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_110_Model[:,0],
           1E-3*A_Au*Tilt_110_Model[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_110_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_110_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_110_Wolf_Cu_LJ[:,0],1E-3*Tilt_110_Wolf_Cu_LJ[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='^',linestyle='',label='Cu(EAM)')
pylab.plot(Tilt_110_Wolf_Cu_EAM[:,0],1E-3*Tilt_110_Wolf_Cu_EAM[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Cu(EAM)')
pylab.plot(Tilt_110_Wolf_Au_EAM[:,0],1E-3*Tilt_110_Wolf_Au_EAM[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=4,prop={'size':fontsize_legend});

pylab.subplot(223)
pylab.title('[111] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,60)
pylab.ylim(0,1.200)
pylab.plot(Tilt_111_Model[:,0],
           1E-3*A_Cu*Tilt_111_Model[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_111_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_111_Model_Relaxed[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_111_Model[:,0],
           1E-3*A_Au*Tilt_111_Model[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle=':',label='Au(Cov)')
pylab.plot(Tilt_111_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_111_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_111_Wolf_Cu_LJ[:,0],1E-3*Tilt_111_Wolf_Cu_LJ[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='^',linestyle='',label='Cu(LJ)')
pylab.plot(Tilt_111_Wolf_Cu_EAM[:,0],1E-3*Tilt_111_Wolf_Cu_EAM[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Cu(EAM)')
pylab.plot(Tilt_111_Wolf_Au_EAM[:,0],1E-3*Tilt_111_Wolf_Au_EAM[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=4,prop={'size':fontsize_legend});

ax = pylab.subplot(224)
pylab.title('[112] Symmetric Tilt',fontsize=fontsize_title)
pylab.xlim(0,110)
pylab.ylim(0,1.400)
pylab.plot(Tilt_112_Model[:,0],
           1E-3*A_Cu*Tilt_112_Model[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle=':',label='Cu(Cov)')
pylab.plot(Tilt_112_Model_Relaxed[:,0],
           1E-3*A_Cu*Tilt_112_Model_Relaxed[:,1],color="blue",linewidth=linewidth,markersize=markersize,linestyle='-',label='Cu(RCov)')
pylab.plot(Tilt_112_Model[:,0],
           1E-3*A_Au*Tilt_112_Model[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle=':',label='Au(Cov)')
pylab.plot(Tilt_112_Model_Relaxed[:,0],
           1E-3*A_Au*Tilt_112_Model_Relaxed[:,1],color="green",linewidth=linewidth,markersize=markersize,linestyle='-',label='Au(RCov)')
pylab.plot(Tilt_112_Wolf_Cu_LJ[:,0],1E-3*Tilt_112_Wolf_Cu_LJ[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Cu(LJ)')
pylab.plot(Tilt_112_Wolf_Cu_EAM[:,0],1E-3*Tilt_112_Wolf_Cu_EAM[:,1],color="blue",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Cu(EAM)')
pylab.plot(Tilt_112_Wolf_Au_EAM[:,0],1E-3*Tilt_112_Wolf_Au_EAM[:,1],color="green",linewidth=linewidth,markersize=markersize,marker='o',linestyle='',label='Au(EAM)')
pylab.xlabel("Tilt angle (degrees)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.ylabel("Energy ($kJ/m^2$)",fontsize=fontsize_axis,labelpad=-0.5);
pylab.tick_params(axis='both', which='major', labelsize=fontsize_numbers)
#pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=4,prop={'size':fontsize_legend});

handles, labels = ax.get_legend_handles_labels()
lgd = pylab.figlegend(handles, labels, loc = 'lower center', ncol=4,prop={'size':fontsize_legend})
#                , labelspacing=0) bbox_to_anchor=(0.5, -0.5), 

pylab.tight_layout();
pylab.subplots_adjust(bottom=0.175,left=0.05,right=0.98,top=0.95,wspace=0.15,hspace=0.4);
#fig.savefig('plot_relaxed_wolf.pdf', bbox_extra_artists=(lgd,), bbox_inches='tight')
pylab.show();

