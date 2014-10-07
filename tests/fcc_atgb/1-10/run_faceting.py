#!/usr/bin/python
import os
order = 2;
X=[];Y=[];
for theta in range(0,91,5):
    print ("theta="+str(theta));
    os.system("../../../bin/main facet.in -n 8 -- -DFacet"+str(order)+"D.DataFile=outfiles/F"+str(order)+"_"+str(theta)+".dat -DFacet"+str(order)+"D.OutFile=facetfiles/F"+str(order)+"_"+str(theta)+".dat -DFacet"+str(order)+"D.MaxFacetOrder="+str(order)+"")
    file = open("facetfiles/F"+str(order)+"_"+str(theta)+".dat",'r'); 
    X.append(theta); 
    Y.append(float(file.readline()));  
    file.close();
f = open("outfiles/F"+str(order)+".dat","w");
for x,y in zip(X,Y):
    f.write(str(x)+" "+str(y)+"\n");
f.close();



