#!/usr/bin/python
import os
raise("don't do it! you already have a good data set")
dirs = ["001_001", "011_011", "031_031", "111_111", "112_112", "114_011", "115_111", "158_031", "221_001", "552_112"]
for d in dirs:
    os.chdir(d);
    print(d);
    os.system("python run_computeenergy.py");
    os.system("python run_faceting.py");
    os.chdir("..");
print("done");
