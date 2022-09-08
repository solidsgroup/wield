# WIELD - (W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries 

This is a small research program to compute the energy of a bicrystal interface. 

Dependencies
============

The following external packages are required for Wield.

1. MuParser: available in the Ubuntu repository as `libmuparser-dev`

2. TCLAP: available in the Ubuntu repository as `libtclap-dev`

3. Python developer tools: available in the Ubuntu repository as `python3-dev`


Installation - Python
=====================

Clone the repository:

    git clone https://github.com/solidsgroup/wield.git

Install using pip:

    pip3 install wield/py

Now you can import wield and use wield functions in python, e.g.

    import wield
    wield.createMatrixFromXAngle(0.0)


Installation
============


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
