#!/bin/python
from pylab import plot, show
from numpy import loadtxt

# x=[];y=[];
# for theta in range(0,121,5):
#     file = open("facet2d_"+str(theta)+".dat",'r'); 
#     x.append(theta); 
#     y.append(float(file.readline()));  
#     file.close();
# plot(x,y,marker='o');

x=[];y=[];
for theta in range(0,181,5):
    file = open("facetfiles/F2_"+str(theta)+".dat",'r'); 
    x.append(theta); 
    y.append(float(file.readline()));  
    file.close();
plot(x,y,marker='o');

Unrelaxed110 = loadtxt("outfiles/F1.dat", delimiter=" ");
plot(Unrelaxed110[:,0],
     Unrelaxed110[:,1],
     color="black",linewidth=2,linestyle='-',marker="",label='110 Model')


show()
