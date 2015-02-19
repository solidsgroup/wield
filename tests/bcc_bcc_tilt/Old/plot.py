#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield
import pylab
import numpy

#files1=["100.dat", "110.dat", "111.dat", "112.dat"]; files2=["Shibuta/100.dat","Shibuta/110.dat","Shibuta/111.dat","Shibuta/112.dat"]; print(wield.leastSquares(files1,files2)); exit();

A = 3.922#0.0586099*70
B = 64.048#70

Tilt_001_Model  = numpy.loadtxt("outfiles/100.dat", delimiter=" ");
Tilt_110_Model  = numpy.loadtxt("outfiles/110.dat", delimiter=" ");
Tilt_111_Model  = numpy.loadtxt("outfiles/111.dat", delimiter=" ");
Tilt_112_Model  = numpy.loadtxt("outfiles/112.dat", delimiter=" ");

Tilt_001_Shibuta  = numpy.loadtxt("Shibuta/100.dat", delimiter=" ");
Tilt_110_Shibuta  = numpy.loadtxt("Shibuta/110.dat", delimiter=" ");
Tilt_111_Shibuta  = numpy.loadtxt("Shibuta/111.dat", delimiter=" ");
Tilt_112_Shibuta  = numpy.loadtxt("Shibuta/112.dat", delimiter=" ");

#pylab.figure(figsize=(14,7));
pylab.figure(figsize=(14*16/14,7*16/14));

pylab.subplot(221)
pylab.xlim(0,90)
pylab.ylim(0,2.0)
pylab.plot(Tilt_001_Model[:,0],
           A + B*Tilt_001_Model[:,1],color="black",linewidth=2,linestyle="-",label="100 Model")
pylab.plot(Tilt_001_Shibuta[:,0],Tilt_001_Shibuta[:,1],color="black",linewidth=2,marker="o",linestyle="--",label="100 MD")
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc="lower center",fancybox=True,shadow=True,ncol=2);

pylab.subplot(222)
pylab.xlim(0,180)
pylab.ylim(-0.5,2.0)
pylab.plot(Tilt_110_Model[:,0],
           A + B*Tilt_110_Model[:,1],color="black",linewidth=2,linestyle="-",label="110 Model")
pylab.plot(Tilt_110_Shibuta[:,0],Tilt_110_Shibuta[:,1],color="black",linewidth=2,marker="o",linestyle="--",label="110 MD")
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc="lower center",fancybox=True,shadow=True,ncol=2);

pylab.subplot(223)
pylab.xlim(0,60)
pylab.ylim(0,2.0)
pylab.plot(Tilt_111_Model[:,0],
           A + B*Tilt_111_Model[:,1],color="black",linewidth=2,linestyle="-",label="111 Model")
pylab.plot(Tilt_111_Shibuta[:,0],Tilt_111_Shibuta[:,1],color="black",linewidth=2,marker="o",linestyle="--",label="111 MD")
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc="lower center",fancybox=True,shadow=True,ncol=2);

pylab.subplot(224)
pylab.xlim(0,100)
pylab.ylim(0,2.0)
pylab.plot(Tilt_112_Model[:,0],
           A + B*Tilt_112_Model[:,1],color="black",linewidth=2,linestyle="-",label="112 Model")
pylab.plot(Tilt_112_Shibuta[:,0],Tilt_112_Shibuta[:,1],color="black",linewidth=2,marker="o",linestyle="--",label="112 MD")
pylab.xlabel("Tilt angle (degrees)");
pylab.ylabel("Energy ($J/m^2$)");
pylab.legend(loc="lower center",fancybox=True,shadow=True,ncol=2);

pylab.tight_layout();
#pylab.savefig("out.pdf", format="pdf")
pylab.show();

