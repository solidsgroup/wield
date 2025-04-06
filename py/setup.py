from setuptools import setup, Extension
import pybind11
import numpy

ext_modules = [
    Extension(
        name="wield",
        sources=["wield.cpp"],
        include_dirs=[
            pybind11.get_include(),
            numpy.get_include(),
            "/usr/include/eigen3/",
            "../inc/",
            "../src/"
        ],
        language="c++",
        extra_compile_args=["-std=c++17"],
    )
]

setup(
    name="wield",
    url="https://github.com/solidsgroup/wield",
    author="Brandon Runnels",
    author_email="brunnels@solids.group",
    version="0.1",
    ext_modules=ext_modules,
    zip_safe=False,
)
