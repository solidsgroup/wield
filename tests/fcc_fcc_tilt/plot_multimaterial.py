#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy


#files1=["100.dat", "110.dat", "111.dat", "112.dat"]; files2=["Shibuta/100.dat","Shibuta/110.dat","Shibuta/111.dat","Shibuta/112.dat"]; print(wield.leastSquares(files1,files2)); exit();

# print(wield.leastSquares(["110.dat"], ["Wolf/110_Al.dat"]));
# print(wield.leastSquares(["110.dat"], ["Wolf/110_Au.dat"]));
# print(wield.leastSquares(["110.dat"], ["Wolf/110_Cu.dat"]));
# print(wield.leastSquares(["110.dat"], ["Wolf/110_Ni.dat"]));
# exit();

[A_Al, B_Al] = [0.44142970295202566, 3.8489267554408668]
[A_Au, B_Au] = [0.44133817936454506, 3.9175874033797884]
[A_Cu, B_Cu] = [0.82938792750373236, 7.3992863197993586]
[A_Ni, B_Ni] = [1.1542392537932971, 9.7447800085104319]


C_Al = 22; [A_Al, B_Al] = [C_Al*0.0527911,C_Al];
C_Au = 24; [A_Au, B_Au] = [C_Au*0.0527911,C_Au];
C_Cu = 40; [A_Cu, B_Cu] = [C_Cu*0.0527911,C_Cu];
C_Ni = 60; [A_Ni, B_Ni] = [C_Ni*0.0527911,C_Ni];


Tilt_110_Model  = numpy.loadtxt("110_multimat.dat", delimiter=" ");


Tilt_110_Al  = numpy.loadtxt("Wolf/110_Al.dat", delimiter=" ");
Tilt_110_Au  = numpy.loadtxt("Wolf/110_Au.dat", delimiter=" ");
Tilt_110_Cu  = numpy.loadtxt("Wolf/110_Cu.dat", delimiter=" ");
Tilt_110_Ni  = numpy.loadtxt("Wolf/110_Ni.dat", delimiter=" ");


pylab.plot(Tilt_110_Model[:,0],
           A_Al + B_Al*Tilt_110_Model[:,1],color="green",linewidth="2",linestyle='-',label='Al')
pylab.errorbar(Tilt_110_Al[:,0],Tilt_110_Al[:,1],yerr=0.1*Tilt_110_Al[:,1],color="green",linewidth="2",marker='o',linestyle=' ')

pylab.plot(Tilt_110_Model[:,0],
           A_Au + B_Au*Tilt_110_Model[:,1],color="red",linewidth="2",linestyle='-',label='Au')
pylab.errorbar(Tilt_110_Au[:,0],Tilt_110_Au[:,1],yerr=0.1*Tilt_110_Au[:,1],color="red",linewidth="2",marker='o',linestyle=' ')

pylab.plot(Tilt_110_Model[:,0],
           A_Cu + B_Cu*Tilt_110_Model[:,1],color="turquoise",linewidth="2",linestyle='-',label='Cu')
pylab.errorbar(Tilt_110_Cu[:,0],Tilt_110_Cu[:,1],yerr=0.1*Tilt_110_Cu[:,1],color="turquoise",linewidth="2",marker='o',linestyle=' ')

pylab.plot(Tilt_110_Model[:,0],
           A_Ni + B_Ni*Tilt_110_Model[:,1],color="blue",linewidth="2",linestyle='-',label='Ni')
pylab.errorbar(Tilt_110_Ni[:,0],Tilt_110_Ni[:,1],yerr=Tilt_110_Ni[:,1]*0.1,color="blue",linewidth="2",marker='o',linestyle=' ')

pylab.legend(loc="upper center",ncol=4,fancybox=True,shadow=True);
pylab.xlim(0,180);
pylab.ylim(0,1.5);
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");

pylab.show();

