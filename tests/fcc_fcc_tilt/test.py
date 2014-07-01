#!/usr/bin/python
import sys; sys.path.append("../../scripts");
import wield

files1=["100.dat", "110.dat", "111.dat", "112.dat"]
files2=["Shibuta/100.dat", "Shibuta/110.dat", "Shibuta/111.dat", "Shibuta/112.dat"];
print(wield.leastSquares(files1,files2));
