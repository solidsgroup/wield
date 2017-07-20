#!/usr/bin/python
import os
X=[];Y=[];
for theta in range(0,181,5):
    print ("100: theta="+str(theta).zfill(3));
    os.system("../../../bin/main -n 6 -- -DFacet2D.DataFile=outfiles/F2_"+str(theta).zfill(3)+".dat -DFacet2D.OutFile=facetfiles/F2_"+str(theta).zfill(3)+".dat -DFacet2D.MaxFacetOrder=2")
    file = open("facetfiles/F2_"+str(theta).zfill(3)+".dat",'r'); 
    X.append(theta); 
    Y.append(float(file.readline()));  
    file.close();
f = open("outfiles/F2.dat","w");
for x,y in zip(X,Y):
    f.write(str(x)+" "+str(y)+"\n");
f.close();
