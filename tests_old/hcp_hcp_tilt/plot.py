#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

D_MG = 400
D_TI = 1000

Tilt_1210_MG_Model = numpy.loadtxt("1210_2d/outfiles/F1_mg.dat", delimiter=" ");
Tilt_1210_TI_Model = numpy.loadtxt("1210_2d/outfiles/F1_ti.dat", delimiter=" ");
Tilt_0110_MG_Model = numpy.loadtxt("0110_2d/outfiles/F1_mg.dat", delimiter=" ");
Tilt_0110_TI_Model = numpy.loadtxt("0110_2d/outfiles/F1_ti.dat", delimiter=" ");

Tilt_1210_MG_Model_Relaxed  = numpy.loadtxt("1210_2d/outfiles/F2.dat", delimiter=" ");
Tilt_0110_MG_Model_Relaxed  = numpy.loadtxt("0110_2d/outfiles/F2.dat", delimiter=" ");

Tilt_1210_MG_Wang  = numpy.loadtxt("Wang/1210_mg.csv", delimiter=" ");
Tilt_1210_TI_Wang  = numpy.loadtxt("Wang/1210_ti.csv", delimiter=" ");
Tilt_0110_MG_Wang  = numpy.loadtxt("Wang/0110_mg.csv", delimiter=" ");
Tilt_0110_TI_Wang  = numpy.loadtxt("Wang/0110_ti.csv", delimiter=" ");

#pylab.figure(figsize=(14,7));
pylab.figure(figsize=(14*16/14,0.75*7*16/14));

pylab.subplot(121)
pylab.xlim(0,90)
pylab.ylim(0,1000)
pylab.plot(Tilt_1210_MG_Model[:,0],D_MG*Tilt_1210_MG_Model[:,1], color="blue",linewidth=2, marker='', linestyle='-',label='$[1210]$ Model (Mg)')
pylab.plot(Tilt_1210_MG_Wang[:,0],       Tilt_1210_MG_Wang[:,1], color="blue",linewidth=2,marker='o',linestyle='--',label='$[1210]$ MD (Mg)')
pylab.plot(Tilt_1210_TI_Model[:,0],D_TI*Tilt_1210_TI_Model[:,1],color="green",linewidth=2, marker='', linestyle='-',label='$[1210]$ Model (Ti)')
pylab.plot( Tilt_1210_TI_Wang[:,0],      Tilt_1210_TI_Wang[:,1],color="green",linewidth=2,marker='o',linestyle='--',label='$[1210]$ MD (Ti)')
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J\\,/\\,m^2$)");
pylab.legend(loc='upper center',ncol=2);

#pylab.subplot(223)
#pylab.xlim(0,90)
#pylab.ylim(0,1000)
#pylab.plot(Tilt_1210_TI_Model[:,0], D_TI*Tilt_1210_TI_Model[:,1], color="black",linewidth=2, marker='', linestyle='-',label='$[1210]$ Model')
#pylab.plot( Tilt_1210_TI_Wang[:,0],       Tilt_1210_TI_Wang[:,1], color="black",linewidth=2,marker='o',linestyle='--',   label='$[1210]$ MD')
#pylab.xlabel("Tilt angle (degrees)");
#pylab.ylabel("Energy ($J/m^2$)");
#pylab.legend(loc='upper center',fancybox=True,shadow=True,ncol=3);


pylab.subplot(122)
pylab.xlim(0,90)
pylab.ylim(0,1200.0)
pylab.plot(Tilt_0110_MG_Model[:,0],D_MG*Tilt_0110_MG_Model[:,1], color="blue",linewidth=2, marker='',linestyle='-', label='$[0\\bar{1}10]$ Model (Mg)')
pylab.plot(Tilt_0110_MG_Wang[:,0],       Tilt_0110_MG_Wang[:,1], color="blue",linewidth=2,marker='o',linestyle='--',label="$[0\\bar{1}10]$ MD (Mg)")
pylab.plot(Tilt_0110_TI_Model[:,0],D_TI*Tilt_0110_TI_Model[:,1],color="green",linewidth=2, marker='',linestyle='-', label='$[0\\bar{1}10]$ Model (Ti)')
pylab.plot(Tilt_0110_TI_Wang[:,0],       Tilt_0110_TI_Wang[:,1],color="green",linewidth=2,marker='o',linestyle='--',label="$[0\\bar{1}10]$ MD (Ti)")
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc='upper center',ncol=2);


pylab.tight_layout();
pylab.show();

