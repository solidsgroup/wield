# WIELD - (W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries 

This is a small research program to compute the energy of a bicrystal interface (grain boundary). 
This implements the lattice-matching method for GB energy and CSL used in (among others):

- https://doi.org/10.1016/j.jmps.2016.01.008
- https://doi.org/10.1016/j.jmps.2015.11.007
- https://doi.org/10.1107/S205327331700122X
- https://doi.org/10.1016/j.mtla.2019.100221
- https://doi.org/10.1016/j.scriptamat.2020.04.042
- https://doi.org/10.1016/j.actamat.2021.117149
- https://doi.org/10.1016/j.commatsci.2023.112057

There are two main interfaces for wield, the python interface and the input file interface.
The python interface is recommended as it will be more continuously supported.

Python Interface
================

The python interface supports interaction with wield structures and methods by `import wield`.

Dependencies
------------

Installation of dependencies using aptitude or yum can be done by running the following scripts.

[Debian-based distributions (Ubuntu) using apt](.github/workflows/dependencies-apt.sh)

[RPM-based distributions (RHEL,Fedora) using yum](.github/workflows/dependencies-yum.sh)


Installation
------------

If you have not already, clone the repository with:

    git clone https://github.com/solidsgroup/wield.git

Now install using pip:

    pip3 install --user -e wield/py

(The `--user` and `-e` options are not required but are recommended)

Now you can import wield and use wield functions in python, e.g.

    import wield
    wield.createMatrixFromXAngle(0.0)

Run tests
---------

Current tests are stored in the `tests` directory.
To run, execute with python; for instance,

    cd tests/csl_fcc_110
    python3 input.py


Input File Interface
====================

The input file interface is a legacy method for interacting with wield. 
It is not currently maintained, so use at your own risk.

Dependencies 
------------

The following external packages are required for Wield.

1. MuParser: available in the Ubuntu repository as `libmuparser-dev`

2. TCLAP: available in the Ubuntu repository as `libtclap-dev`

3. Python developer tools: available in the Ubuntu repository as `python3-dev`

Compilation
-----------

Wield compiles using the Makefile. In the root directory type

    make


Usage
=====

Running the program:

./main [input file] [-D<StructName>.<VarName>=<VarValue> ... ] [-p --dynamic-plot] [-n --num-threads <num>] [-h --help]

Runtime variables
-----------------

All runtime variables can be specified in one of two ways:
- In the input file

$VarName varvalue
$StructName {
$VarName varvalue
}

- In the command line

./main -DVarName=varvalue -DStructName.VarName=varvalue

Command line options
--------------------

Some routines support additional command line options:
- -p --dynamic-plot: for some supported functions, a VTK window will be displayed that shows the results of the computation real-time.
- -n --num-threads <num>: for some supported functions, use pthread parallelism

Methods
-------

This program is a collection of other methods that can be run seperately or simultaneously.
Use the following links to find documentation and example input files for each method

- \ref Wield::Main::CSL Compute the thermalized coincident site lattice \f$\Sigma\f$ value of a bicrystal
- \ref Wield::Main::Energy1D Compute the thermalized grain boundary energy for an interface
- \ref Wield::Main::MainInterface1D Compute the interface energy as a function of interface orientation, parameterized by one angle
- \ref MainFacet2D Use the relaxation algorithm to compute the facet pattern and relaxed energy, given an energy surface

Documentation
=============

You can use doxygen to generate documentation for Wield by typing

    doxygen

in the main directory. (Note: you must have Doxygen installed.)
The HTML documentation main page is located at `dox/html/index.html`
