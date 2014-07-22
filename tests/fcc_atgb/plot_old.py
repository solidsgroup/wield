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
Dat = [];
for f in filenames:
    dat = numpy.loadtxt(f,delimiter=" ");
    # pylab.plot(dat[:,0],dat[:,1],color="blue",linewidth="2",linestyle='-')
    # pylab.plot(dat[:,0],dat[:,2],color="blue",linewidth="2",linestyle='--')
    # pylab.show();
    Dat.insert([dat[90,0],dat[90,1]]);
    Dat.print(dat[90,0], " ", dat[90,1]);



Dat_1a  = numpy.loadtxt("1.a.dat", delimiter=" ");
Dat_1b  = numpy.loadtxt("1.b.dat", delimiter=" ");
Dat_1c  = numpy.loadtxt("1.c.dat", delimiter=" ");
Dat_1d  = numpy.loadtxt("1.d.dat", delimiter=" ");
Dat_1e  = numpy.loadtxt("1.e.dat", delimiter=" ");
Dat_1f  = numpy.loadtxt("1.f.dat", delimiter=" ");

Dat_2a  = numpy.loadtxt("2.a.dat", delimiter=" ");
Dat_2b  = numpy.loadtxt("2.b.dat", delimiter=" ");
Dat_2c  = numpy.loadtxt("2.c.dat", delimiter=" ");
Dat_2d  = numpy.loadtxt("2.d.dat", delimiter=" ");
Dat_2e  = numpy.loadtxt("2.e.dat", delimiter=" ");
Dat_2f  = numpy.loadtxt("2.f.dat", delimiter=" ");

def annotate(x,y,s):
    pylab.annotate(s=s+"("+str(x)+"$^\circ$)",
                   xy=(x,y),
                   rotation='vertical',
                   xytext=(x-2,y+3),
                   arrowprops=dict(arrowstyle="->"),
                   bbox=dict(boxstyle="round",fc="0.8"));
if (num==1):
    pylab.subplot(321)
    pylab.title("$[111],[11\overline{1}]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_1a[:,0],Dat_1a[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_1a[:,0],Dat_1a[:,2],color="blue",linewidth="2",linestyle='--')

    pylab.subplot(322)
    pylab.title("$[558],[\overline{7}\overline{7}4]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_1b[:,0],Dat_1b[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_1b[:,0],Dat_1b[:,2],color="blue",linewidth="2",linestyle='--')
    pylab.xticks(list(pylab.xticks()[0]) + [13.25])
    annotate(-42.32,2.12,"IB")
    annotate(13.26,0.1,"CTB")

    pylab.subplot(323)
    pylab.title("$[112],[\overline{5}\overline{5}2]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_1c[:,0],Dat_1c[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_1c[:,0],Dat_1c[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-35.792,1.97,"IB")
    annotate(19.47,0.1,"CTB")

    pylab.subplot(324)
    pylab.title("$[114],[110]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_1d[:,0],Dat_1d[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_1d[:,0],Dat_1d[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-54.78,2.09,"SITB")
    annotate(35.26,0.1,"CTB")

    pylab.subplot(325)
    pylab.title("$[001],[221]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_1e[:,0],Dat_1e[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_1e[:,0],Dat_1e[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-35.47,1.43,"SITB")
    annotate(54.74,0.1,"CTB")

    pylab.subplot(326)
    pylab.title("$[11\overline{8}],[554]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_1f[:,0],Dat_1f[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_1f[:,0],Dat_1f[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-24.89,1.34,"SITB")
    annotate(64.76,0.1,"CTB")

elif (num == 2):
    pylab.subplot(321)
    pylab.title("$[11\overline{5}],[111]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_2a[:,0],Dat_2a[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_2a[:,0],Dat_2a[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-19.32,1.24,"SITB")
    annotate(70.53,0,"CTB")

    pylab.subplot(322)
    pylab.title("$[11\overline{4}],[778]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_2b[:,0],Dat_2b[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_2b[:,0],Dat_2b[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-15.6,1.24,"SITB")
    annotate(74.21,0.13,"CTB")

    pylab.subplot(323)
    pylab.title("$[22\overline{7}],[445]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_2c[:,0],Dat_2c[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_2c[:,0],Dat_2c[:,2],color="blue",linewidth="2",linestyle='--')
    pylab.xticks(list(pylab.xticks()[0]) + [19.47])
    annotate(-13.1,1.23,"SITB")
    annotate(76.74,0.33,"CTB")

    pylab.subplot(324)
    pylab.title("$[11\overline{3}],[557]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_2d[:,0],Dat_2d[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_2d[:,0],Dat_2d[:,2],color="blue",linewidth="2",linestyle='--')
    annotate(-10.3,1.2,"SITB")
    annotate(79.98,.115,"CTB")

    pylab.subplot(325)
    pylab.title("$[44\overline{11}],[223]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_2e[:,0],Dat_2e[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_2e[:,0],Dat_2e[:,2],color="blue",linewidth="2",linestyle='--')
    pylab.xticks(rotation=70)
    annotate(-8.08,1.24,"SITB")
    annotate(81.95,.25,"CTB")

    pylab.subplot(326)
    pylab.title("$[11\overline{2}],[112]$")
    pylab.xlim(-90,90)
    pylab.ylim(0,6.)
    pylab.plot(Dat_2f[:,0],Dat_2f[:,1],color="blue",linewidth="2",linestyle='-')
    pylab.plot(Dat_2f[:,0],Dat_2f[:,2],color="blue",linewidth="2",linestyle='--')
    

pylab.tight_layout();
pylab.show();

