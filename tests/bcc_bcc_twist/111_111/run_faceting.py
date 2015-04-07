#!/usr/bin/python
import os
X=[];Y=[];
order = 3
for theta in range(0,61,1):
    print ("100: theta="+str(theta).zfill(3));
    os.system("../../../bin/main -n 6 -- -DFacet2D.DataFile=outfiles/F2_"+str(theta).zfill(3)+".dat -DFacet2D.OutFile=facetfiles/F"+str(order)+"_"+str(theta).zfill(3)+".dat -DFacet2D.MaxFacetOrder="+str(order)+" -DFacet2D.SymmetricY")
    file = open("facetfiles/F"+str(order)+"_"+str(theta).zfill(3)+".dat",'r'); 
    X.append(theta); 
    Y.append(float(file.readline()));  
    file.close();
f = open("outfiles/F"+str(order)+".dat","w");
for x,y in zip(X,Y):
    f.write(str(x)+" "+str(y)+"\n");
f.close();
