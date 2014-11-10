#ifndef WIELD_MAIN_ENERGYINTERFACE1D_H
#define WIELD_MAIN_ENERGYINTERFACE1D_H

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
void EnergyInterface1D(Reader::Reader &reader,bool dynamicPlot)
{
  WIELD_EXCEPTION_TRY;

  // READ STANDARD VARIABLES
  WIELD_IO_READ_CRYSTAL(1);
  WIELD_IO_READ_CRYSTAL(2);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("EnergyInterface1D",1);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("EnergyInterface1D",2);
  WIELD_IO_READ_PARAMETERS("EnergyInterface1D");

  // Specify the range of the FREE VARIABLES:
  double phiMin       = reader.Read<double>("EnergyInterface1D","PhiMin",0.);
  double dPhi         = reader.Read<double>("EnergyInterface1D","DPhi",0.);
  double phiMax       = reader.Read<double>("EnergyInterface1D","PhiMax",0.);
  // Specify the rotation of the INTERFACE
  double phiRotX      = reader.Read<double>("EnergyInterface1D","PhiRotX",0.);
  double phiRotY      = reader.Read<double>("EnergyInterface1D","PhiRotY",0.);
  double phiRotZ      = reader.Read<double>("EnergyInterface1D","PhiRotZ",0.);
  // MISC
  double tolerance    = reader.Read<double>("EnergyInterface1D","Tolerance",0.);
  string distribution = reader.Read<string>("EnergyInterface1D","Distribution", "cauchy");
  bool fullConvexify  = reader.Find("EnergyInterface1D", "FullConvexify");
  // OUTPUT FILE STREAM
  bool printData      = reader.Find("EnergyInterface1D","OutFile");
  ofstream out;
  if (printData)
    {
      string outFile      = reader.Read<string>("EnergyInterface1D","OutFile"); 
      out.open(outFile.c_str());
      //open(out,outFile.c_str());
    }

  // ROTATE ORIENTATION RELATIONSHIP AND COMPUTE GRAIN BOUNDARY ENERGY
#ifdef WIELD_USE_VTK
  Wield::Utils::VTK::PlotLine *plotWindow;
  if (dynamicPlot) plotWindow = new Wield::Utils::VTK::PlotLine();
#endif
  vector<double> X,Y;
  for (double phi = phiMin; phi <= phiMax; phi += dPhi)
    {
      WIELD_PROGRESS("Computing energy curve", phi-phiMin, phiMax-phiMin, dPhi);

      Matrix3d N = 
	createMatrixFromXAngle(phi*phiRotX) *
	createMatrixFromYAngle(phi*phiRotY) *
	createMatrixFromZAngle(phi*phiRotZ);
      
      //if (fabs(N(2,2)) < 1E-8) continue;
	  
      double W = (a - b*Wield::Integrator::Surface(crystal1, omega1*N, crystal2, omega2*N, stdDev, tolerance, distribution));
      //if (areaNormalization) W /= N(2,2);
      X.push_back(phi);
      Y.push_back(W);
#ifdef WIELD_USE_VTK
      if (dynamicPlot) 
	if (X.size() > 1) 
	  {
	    plotWindow->clear(); 
	    plotWindow->SetData(X,Y);
	  }
#endif
    }

  cout << endl;
  
  vector<double> Yc = Wield::Optimization::Convexify1DAngles(X,Y,fullConvexify);
  if (printData)
    {
      for (int i=0; i<X.size(); i++)
	out << X[i] << " " << Y[i] << " " << Yc[i] << " " << endl;
      out.close();
    }
	
#ifdef WIELD_USE_VTK
  if (dynamicPlot) 
    {
      plotWindow->clear(); 
      plotWindow->SetData(X,Y);
      plotWindow->SetData(X,Yc, true);
    }
#endif
  WIELD_EXCEPTION_CATCH_FINAL;
}
}
}

#endif
