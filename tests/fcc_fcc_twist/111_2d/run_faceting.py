#!/usr/bin/python
import os
order = 2;
X=[];Y=[];
for theta in range(0,91,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main -n 8 -DFacet2D.DataFile=outfiles/F2_"+str(theta)+".dat -DFacet2D.OutFile=facetfiles/F"+str(order)+"_"+str(theta)+".dat -DFacet2D.MaxFacetOrder="+str(order)+"")
    file = open("facetfiles/F"+str(order)+"_"+str(theta)+".dat",'r'); 
    X.append(theta); 
    Y.append(float(file.readline()));  
    file.close();
f = open("outfiles/F"+str(order)+".dat","w");
for x,y in zip(X,Y):
    f.write(str(x)+" "+str(y)+"\n");
f.close();



