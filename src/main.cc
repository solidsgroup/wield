/// 
/// \mainpage WIELD: (W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries 
/// This is a small research program to compute the energy of a bicrystal interface using the Site Potential method.
/// 

///
/// \file main.cpp
/// \brief This is the short description for main.cpp
///
/// This is the long description for main.cpp
/// \f[\int_{\Omega}\nabla\cdot\mathbb{V}dV = \int_{\partial\Omega}\mathbb{V}\cdot\mathbb{n}dA\f]
///


#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>

#define eigen_assert(A) if (!(A)) throw new std::runtime_error("Eigen threw an exception");
#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;

#include "tclap/CmdLine.h"
#include "/home/brandon/Research/Reader/Reader.h"
#include "/home/brandon/Research/Reader/Arguments.h"

#include "SurfaceIntegrate.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldVTK.h"
#include "Utils/wieldProgress.h"
#include "Optimization/wieldConvexify2d.h"

void signalHandler(int signum)
{
  cout << endl;
  cout << WIELD_COLOR_RESET << "Program terminated" << endl;
  exit(signum);
}

int main(int argc, char* argv[])
{
  WIELD_EXCEPTION_TRY;

  signal(SIGINT, signalHandler);

  //
  // COMMAND LINE PARSING
  // {{{
  TCLAP::CmdLine cmd("(W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries");
  TCLAP::SwitchArg switchDynamicPlot("p", "dynamic-plot", "Show real-time VTK plot of energy", cmd, false);
  TCLAP::SwitchArg switchVisualize("s", "show-crystal", "Show VTK plot of initial OR", cmd, false);
  TCLAP::UnlabeledValueArg<string> argFileName("name", "Path to input file", true, "", "inputfile", cmd);
  cmd.parse(argc, argv);
  bool dynamicPlot = switchDynamicPlot.getValue();
  bool visualize = switchVisualize.getValue();
  string fileName = argFileName.getValue();
  // }}}

  // 
  // INPUT FILE PARSING
  // {{{ 
  // {{{ OPEN INPUT FILE READER
  Reader reader(fileName, "$", "#", "...");
  // }}}
  // {{{ SPECIFY ORIENTATION OF CRYSTAL 1
  Matrix3d Omega_1;
  if (reader.Find("X1") && reader.Find("Y1"))
    Omega_1 = createMatrixFromXY(reader.Read<Vector3d>("X1"), reader.Read<Vector3d>("Y1"));
  else if (reader.Find("Y1") && reader.Find("Z1"))
    Omega_1 = createMatrixFromYZ(reader.Read<Vector3d>("Y1"), reader.Read<Vector3d>("Z1"));
  else if (reader.Find("Z1") && reader.Find("X1"))
    Omega_1 = createMatrixFromZX(reader.Read<Vector3d>("Z1"), reader.Read<Vector3d>("X1"));
  else WIELD_EXCEPTION_NEW("Missing two vectors to specify Omega_1");
  // }}}
  // {{{ SPECIFY ORIENTATION OF CRYSTAL 2
  Matrix3d Omega_2; 
  if (reader.Find("X2") && reader.Find("Y2"))
    Omega_2 = createMatrixFromXY(reader.Read<Vector3d>("X2"), reader.Read<Vector3d>("Y2"));
  else if (reader.Find("Y2") && reader.Find("Z2"))
    Omega_2 = createMatrixFromYZ(reader.Read<Vector3d>("Y2"), reader.Read<Vector3d>("Z2"));
  else if (reader.Find("Z2") && reader.Find("X2"))
    Omega_2 = createMatrixFromZX(reader.Read<Vector3d>("Z2"), reader.Read<Vector3d>("X2"));
  else WIELD_EXCEPTION_NEW("Missing two vectors to specify Omega_2");
  // }}}
  // {{{ Specify the range of the FREE VARIABLES:
  double theta_min = reader.Read<double>("theta_min",0.);
  double dtheta    = reader.Read<double>("dtheta",0.);
  double theta_max = reader.Read<double>("theta_max",0.);
  double phi_min   = reader.Read<double>("phi_min",0.);
  double dphi      = reader.Read<double>("dphi",0.);
  double phi_max   = reader.Read<double>("phi_max",0.);
  // }}}
  // {{{ Specify the rotation of the CRYSTAL 
  double ThetaRotX1 = reader.Read<double>("ThetaRotX1",0.);
  double ThetaRotY1 = reader.Read<double>("ThetaRotY1",0.);
  double ThetaRotZ1 = reader.Read<double>("ThetaRotZ1",0.);
  double ThetaRotX2 = reader.Read<double>("ThetaRotX2",0.);
  double ThetaRotY2 = reader.Read<double>("ThetaRotY2",0.);
  double ThetaRotZ2 = reader.Read<double>("ThetaRotZ2",0.);
  // }}}
  // {{{ Specify the rotation of the INTERFACE
  double PhiRotX = reader.Read<double>("PhiRotX",0.);
  double PhiRotY = reader.Read<double>("PhiRotY",0.);
  double PhiRotZ = reader.Read<double>("PhiRotZ",0.);
  double PhiRotX1 = reader.Read<double>("PhiRotX1",0.); /* DEPRICATED */
  double PhiRotY1 = reader.Read<double>("PhiRotY1",0.); /* DEPRICATED */
  double PhiRotZ1 = reader.Read<double>("PhiRotZ1",0.); /* DEPRICATED */
  double PhiRotX2 = reader.Read<double>("PhiRotX2",0.); /* DEPRICATED */
  double PhiRotY2 = reader.Read<double>("PhiRotY2",0.); /* DEPRICATED */
  double PhiRotZ2 = reader.Read<double>("PhiRotZ2",0.); /* DEPRICATED */
  // }}}
  // {{{ ADJUSTABLE PARAMETERS
  double A,B,stdev;
  if (reader.Find("f_constants"))
    {
      string f_constants = reader.Read<string>("f_constants");
      Reader constantsReader(f_constants, "$", "#", "...");
      if (reader.Find("A"))     A = reader.Read<double>("A");
      else                      A = constantsReader.Read<double>("A");
      if (reader.Find("B"))     B = reader.Read<double>("B");
      else                      B = constantsReader.Read<double>("B");
      if (reader.Find("stdev")) stdev = reader.Read<double>("stdev");
      else                      stdev = constantsReader.Read<double>("stdev");
    }
  else // Otherwise, look in the current file
    {
      A = reader.Read<double>("A");
      B = reader.Read<double>("B");
      stdev = reader.Read<double>("stdev");
    }
  // }}}
  // {{{ LATTICE COEFFICIENTS: TOP CRYSTAL
  string f1 = reader.Read<string>("C_1");
  Reader crystal1Reader(f1, "$", "#", "...");
  int order1 = crystal1Reader.Read<int>("order");
  CosSeries C1(order1); crystal1Reader.Read<CosSeries>("C", &C1);
  C1.order = order1;
  C1.alpha1 = crystal1Reader.Read<double>("a1");
  C1.alpha2 = crystal1Reader.Read<double>("a2");
  C1.alpha3 = crystal1Reader.Read<double>("a3");
  // }}}
  // {{{ LATTICE COEFFICIENTS: BOTTOM CRYSTAL
  string f2 = reader.Read<string>("C_2");
  Reader crystal2Reader(f2, "$", "#", "...");
  int order2 = crystal2Reader.Read<int>("order");
  CosSeries C2(order2); crystal2Reader.Read<CosSeries>("C", &C2);
  C2.order = order2;
  C2.alpha1 = crystal2Reader.Read<double>("a1");
  C2.alpha2 = crystal2Reader.Read<double>("a2");
  C2.alpha3 = crystal2Reader.Read<double>("a3");
  // }}}
  // {{{ MISC
  bool areaNormalization = reader.Find("areaNormalization");
  double tolerance = reader.Read<double>("tolerance",0.);
  // }}}
  // {{{ OUTPUT FILE STREAM
  string outfile = reader.Read<string>("outfile"); // file to store computation data
  ofstream out(outfile.c_str());        // output stream
  // }}}
  // }}}

  // 
  // VTK VISUALIZATION
  // {{{ 
  if (visualize)
    {
      vector<Actor> actors;
      actors.push_back(drawCrystal(C1, 
				   Omega_1 *
				   createMatrixFromXAngle(theta_min*ThetaRotX1) *
				   createMatrixFromYAngle(theta_min*ThetaRotY1) *
				   createMatrixFromZAngle(theta_min*ThetaRotZ1) *
				   createMatrixFromXAngle(phi_min*PhiRotX) *
				   createMatrixFromYAngle(phi_min*PhiRotY) *
				   createMatrixFromZAngle(phi_min*PhiRotZ),
				   Matrix3d::Identity(),
				   0*C1.alpha1, -2*C1.alpha2, 0*C1.alpha3,
				   2*C1.alpha1,  2*C1.alpha2, 2*C1.alpha3,
				   (int)((double)reader.Read<double>("resolution",50)/C1.alpha1), 
				   0.6,0.));
      actors.push_back(drawCrystal(C2, 
				   Omega_2 *
				   createMatrixFromXAngle(theta_min*ThetaRotX2) *
				   createMatrixFromYAngle(theta_min*ThetaRotY2) *
				   createMatrixFromZAngle(theta_min*ThetaRotZ2) *
				   createMatrixFromXAngle(phi_min*PhiRotX) *
				   createMatrixFromYAngle(phi_min*PhiRotY) *
				   createMatrixFromZAngle(phi_min*PhiRotZ),
				   Matrix3d::Identity(),
				   0*C2.alpha1, -2*C2.alpha2, -2*C2.alpha3,
				   2*C2.alpha1,  2*C2.alpha2, 0*C2.alpha3,
				   (int)((double)reader.Read<double>("resolution",50)/C1.alpha1), 
				   0.6,0.));
      renderCrystals(actors);
    }	
  // }}}

  //
  // ROTATE ORIENTATION RELATIONSHIP AND COMPUTE GRAIN BOUNDARY ENERGY
  // {{{
  PlotWindow2D *plotWindow;
  if (dynamicPlot) plotWindow = new PlotWindow2D();
  vector<double> X,Y;
  if (fabs(theta_max-theta_min) > 1E-8)
    {
      for (double theta = theta_min; theta <= theta_max; theta += dtheta)
	{
	  Matrix3d Rot1 = 
	    Omega_1 *
	    createMatrixFromXAngle(theta*ThetaRotX1) *
	    createMatrixFromYAngle(theta*ThetaRotY1) *
	    createMatrixFromZAngle(theta*ThetaRotZ1);
	  Matrix3d Rot2 = 
	    Omega_2 *
	    createMatrixFromXAngle(theta*ThetaRotX2) *
	    createMatrixFromYAngle(theta*ThetaRotY2) *
	    createMatrixFromZAngle(theta*ThetaRotZ2);
      
	  double W = A - B*SurfaceIntegrate(C1, Rot1, C2, Rot2, stdev, tolerance);
	  out << theta << " " << W << endl;
	  X.push_back(theta);
	  Y.push_back(W);
	  if (dynamicPlot) if (X.size() > 1) {plotWindow->clear(); plotWindow->plotLine(X,Y);}

	  WIELD_PROGRESS("Computing energy curve", theta-theta_min, theta_max-theta_min, dtheta);
	}
      cout << endl;

      if (dynamicPlot) 
	{
	  plotWindow->clear(); 
	  plotWindow->plotLine(X,Y, true);
	}
    }
  else
    if (fabs(phi_max-phi_min) > 1E-8)
      {
	for (double phi = phi_min; phi <= phi_max; phi += dphi)
	  {
	    WIELD_PROGRESS("Computing energy curve", phi-phi_min, phi_max-phi_min, dphi);

	    Matrix3d N = 
	      createMatrixFromXAngle(phi*PhiRotX) *
	      createMatrixFromYAngle(phi*PhiRotY) *
	      createMatrixFromZAngle(phi*PhiRotZ);
      
	    if (fabs(N(2,2)) < 1E-8) continue;
	  
	    double W = (A - B*SurfaceIntegrate(C1, Omega_1*N, C2, Omega_2*N, stdev, tolerance));
	    if (areaNormalization) W /= N(2,2);
	    X.push_back(phi);
	    Y.push_back(W);
	    if (dynamicPlot) 
	      if (X.size() > 1) 
		{
		  plotWindow->clear(); 
		  plotWindow->plotLine(X,Y);
		}
	  }

	cout << endl;

	vector<double> Yc = Wield::Optimization::Convexify2D(X,Y);
	for (int i=0; i<X.size(); i++)
	  out << X[i] << " " << Y[i] << " " << Yc[i] << endl;

	if (dynamicPlot) 
	  {
	    plotWindow->clear(); 
	    plotWindow->plotLine(X,Y);
	    plotWindow->plotLine(X,Yc, true);
	  }

      }
  // }}}
  
  WIELD_EXCEPTION_CATCH_FINAL;
}


