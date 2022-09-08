import os
from pathlib import Path
from glob import glob
from distutils.core import setup

os.system("make -C .. python")

libname = glob("*.so")

if not len(libname):
    raise(Exception("No .so file. Probably an error occurred building wield."))


setup(name="wield",
      url="https://github.com/solidsgroup/wield",
      author="Brandon Runnels",
      author_email="brunnels@solids.group",
      packages=[''],
      package_dir={'':'.'},
      package_data={'':libname})
