#!/usr/bin/python
import os
raise("don't do it! you already have a good data set")
#dirs = ["100_2d", "110_2d", "111_2d", "112_2d"]
for d in dirs:
    os.chdir(d);
    print(d);
    os.system("python run_computeenergy.py");
    os.system("python run_faceting.py");
    os.chdir("..");
print("done");
