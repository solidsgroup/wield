///
/// \page MainOR1D EnergyOR1D
///
/// Description
/// -----------
/// An interface with an orientation relationship is considered.
/// A free paramater (theta) is given a specified range and resolution, and the parameter is used to rotate one or both of the crystals about an axis.
/// The result is printed to a file.
///
/// Input file options
/// ------------------
///   - \b *Crystal1: Parameters for the upper crystal
///   - \b *Crystal2: Parameters for the lower crystal
///   - \b EnergySurfaceSphere: 
///     - *(\b X1,\b Y1,\b Z1): Crystollographic axes corresponding to X,Y,Z axes. Two must be specified.
///     - *(\b X2,\b Y2,\b Z2): Crystollographic axes corresponding to X,Y,Z axes. Two must be specified.
///     - \b ThetaRotX1 [0]: How much theta affects the rotation of Crystal 1 about the X axis
///     - \b ThetaRotY1 [0]: How much theta affects the rotation of Crystal 1 about the Y axis
///     - \b ThetaRotZ1 [0]: How much theta affects the rotation of Crystal 1 about the Z axis
///     - \b ThetaRotX2 [0]: How much theta affects the rotation of Crystal 2 about the X axis
///     - \b ThetaRotY2 [0]: How much theta affects the rotation of Crystal 2 about the Y axis
///     - \b ThetaRotZ2 [0]: How much theta affects the rotation of Crystal 2 about the Z axis
///     - \b ThetaMin [0]: Minimum value of theta
///     - \b ThetaMax [0]: Maximum value of theta
///     - \b DTheta [0]: Increment of theta
///     - \b Distribution [cauchy]: choice of thermal smoothing function
///     - \b Tolerance [0]: Tolerance for throwing out small terms
///     - \b OutFile: Location of output data
///
/// *=Required
///

#ifndef WIELD_MAIN_ENERGYOR1D_H
#define WIELD_MAIN_ENERGYOR1D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>

#include "tclap/CmdLine.h"
#include "Reader.h"

#include "Utils/wieldExceptions.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldCosSeries.h"
#include "Optimization/wieldConvexify1D.h"
#include "Integrator/wieldSurface.h"
#include "IO/wieldReaderMacros.h"
#ifdef WIELD_USE_VTK
#include "Utils/VTK/wieldVTK.h"
#endif

using namespace std;

namespace Wield
{
namespace Main
{
void EnergyOR1D(Reader::Reader &reader,bool dynamicPlot)
{
  WIELD_EXCEPTION_TRY;

  //
  // INPUT FILE PARSING
  //

  // read standard variables
  WIELD_IO_READ_CRYSTAL(1);
  WIELD_IO_READ_CRYSTAL(2);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("EnergyOR1D",1);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("EnergyOR1D",2);
  WIELD_IO_READ_PARAMETERS("EnergyOR1D");
  // specify how the crystal rotates
  double thetaRotX1   = reader.Read<double>("EnergyOR1D","ThetaRotX1",0.);
  double thetaRotY1   = reader.Read<double>("EnergyOR1D","ThetaRotY1",0.);
  double thetaRotZ1   = reader.Read<double>("EnergyOR1D","ThetaRotZ1",0.);
  double thetaRotX2   = reader.Read<double>("EnergyOR1D","ThetaRotX2",0.);
  double thetaRotY2   = reader.Read<double>("EnergyOR1D","ThetaRotY2",0.);
  double thetaRotZ2   = reader.Read<double>("EnergyOR1D","ThetaRotZ2",0.);
  // specify the rotation range
  double thetaMin     = reader.Read<double>("EnergyOR1D","ThetaMin",0.);
  double dTheta       = reader.Read<double>("EnergyOR1D","DTheta",0.);
  double thetaMax     = reader.Read<double>("EnergyOR1D","ThetaMax",0.);
  // miscellaneous
  string distribution = reader.Read<string>("EnergyOR1D", "Distribution","cauchy");
  double tolerance    = reader.Read<double>("EnergyOR1D","Tolerance",0.);
  // output
  string outFile      = reader.Read<string>("EnergyOR1D","OutFile"); 
  ofstream out(outFile.c_str());       

  //
  // ROTATE ORIENTATION RELATIONSHIP AND COMPUTE GRAIN BOUNDARY ENERGY
  // 
#ifdef WIELD_USE_VTK
  Wield::Utils::VTK::PlotLine *plotWindow;
  if (dynamicPlot) plotWindow = new Wield::Utils::VTK::PlotLine();
#endif
  vector<double> X,Y;
  for (double theta = thetaMin; theta <= thetaMax; theta += dTheta)
    {
      // Generate rotation matrices
      Matrix3d Rot1 = 
	omega1 *
	createMatrixFromXAngle(theta*thetaRotX1) *
	createMatrixFromYAngle(theta*thetaRotY1) *
	createMatrixFromZAngle(theta*thetaRotZ1);
      Matrix3d Rot2 = 
	omega2 *
	createMatrixFromXAngle(theta*thetaRotX2) *
	createMatrixFromYAngle(theta*thetaRotY2) *
	createMatrixFromZAngle(theta*thetaRotZ2);
      
      // Compute the energy
      double W = a - b*Wield::Integrator::Surface(crystal1, Rot1, crystal2, Rot2, stdDev, tolerance, distribution);

      // Store results
      out << theta << " " << W << endl;
      X.push_back(theta);
      Y.push_back(W);
#ifdef WIELD_USE_VTK
      if (dynamicPlot) if (X.size() > 1) {plotWindow->clear(); plotWindow->SetData(X,Y);}
#endif
      WIELD_PROGRESS("Computing energy curve", theta-thetaMin, thetaMax-thetaMin, dTheta);
    }
  cout << endl;

  //
  // CLEAN UP
  //
  
#ifdef WIELD_USE_VTK
  if (dynamicPlot) 
    {
      plotWindow->clear(); 
      plotWindow->SetData(X,Y, true);
    }
#endif
  WIELD_EXCEPTION_CATCH_FINAL;
}
}
}

#endif
