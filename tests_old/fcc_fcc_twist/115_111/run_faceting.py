#!/usr/local/bin/python3.4
#raise("Faceting already computed--do not run again")
import os
from numpy import sin, cos, radians, sqrt, maximum
order = 2;
X=[];Y=[];
for theta in range(0,61,5):
    print ("theta="+str(theta).zfill(3));
    # Facet2D.N1Guess="x y z"
    
    x1 =  0.0; y1 =             sin(radians(theta)); z1 = sqrt(maximum(0.,1-x1*x1-y1*y1));
    x2 =  0.5; y2 = -sqrt(0.75)*cos(radians(theta)); z2 = sqrt(maximum(0.,1-x1*x1-y1*y1));
    x3 = -0.5; y3 = -sqrt(0.75)*cos(radians(theta)); z3 = sqrt(maximum(0.,1-x1*x1-y1*y1));
    searchRadius=0.1;

    command = ("../../../bin/main -n 8 " +
               " -DFacet2D.DataFile=outfiles/F2_"+str(theta).zfill(3)+".dat "+
               " -DFacet2D.OutFile=facetfiles/F"+str(order)+"_"+str(theta).zfill(3)+".dat "+
               " -DFacet2D.MaxFacetOrder="+str(order)+" ")
               #"-DFacet2D.N1Guess=\""+str(x1)+" "+str(y1)+" "+str(z1)+"\" " +
               #"-DFacet2D.N2Guess=\""+str(x2)+" "+str(y2)+" "+str(z2)+"\" " +
               #"-DFacet2D.N3Guess=\""+str(x3)+" "+str(y3)+" "+str(z3)+"\" " +
               #"-DFacet2D.SearchRadius="+str(searchRadius) +
               #);
    if (order == 3):
        command = command + " -DFacet2D.SymmetricY "


    print(command);
    os.system(command)

    file = open("facetfiles/F"+str(order)+"_"+str(theta).zfill(3)+".dat",'r'); 
    X.append(theta); 
    Y.append(float(file.readline()));  
    file.close();
f = open("outfiles/F"+str(order)+".dat","w");
for x,y in zip(X,Y):
    f.write(str(x)+" "+str(y)+"\n");
f.close();



