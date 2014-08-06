#ifndef WIELD_MAIN_GAMMASURFACESPHERE_H
#define WIELD_MAIN_GAMMASURFACESPHERE_H

#include "Utils/VTK/wieldPlotSphere.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldProgress.h"
#include "SurfaceIntegrate.h"
#include "IO/wieldReaderMacros.h"

#include "Reader.h"

namespace Wield
{
namespace Main
{
void GammaSurfaceSphere(Reader::Reader &reader, bool dynamicPlotting)
{
  WIELD_EXCEPTION_TRY;

  // FILE INPUT/OUTPUT
  bool printOutput = reader.Find("GammaSurfaceSphere","OutFile");
  ofstream *out;
  if (printOutput) out = new ofstream(reader.Read<string>("GammaSurfaceSphere","OutFile").c_str());

  // READ THE STANDARD VARIABLES
  WIELD_IO_READ_CRYSTAL(1);
  WIELD_IO_READ_CRYSTAL(2);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("GammaSurfaceSphere",1);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("GammaSurfaceSphere",2);
  WIELD_IO_READ_PARAMETERS("GammaSurfaceSphere");
  // CALCULATION RANGE
  double thetaResolution = reader.Read<double>("GammaSurfaceSphere", "ThetaResolution", 20.);
  double thetaMin        = reader.Read<double>("GammaSurfaceSphere", "ThetaMin", 0.);
  double thetaMax        = reader.Read<double>("GammaSurfaceSphere", "ThetaMax", 360.);
  double phiResolution   = reader.Read<double>("GammaSurfaceSphere", "PhiResolution", 20.);
  double phiMin          = reader.Read<double>("GammaSurfaceSphere", "PhiMin", 0.);
  double phiMax          = reader.Read<double>("GammaSurfaceSphere", "PhiMax", 180.);
  // MISC
  double tolerance       = reader.Read<double>("GammaSurfaceSphere","Tolerance",0.);
  int    outputSkip      = reader.Read<int>   ("GammaSurfaceSphere","OutputSkip",1);


  // GENERATE A SPHERE USING VTK
  Wield::Utils::VTK::PlotSphere plotSphere(thetaResolution,phiResolution,thetaMin,thetaMax,phiMin,phiMax);
  vector<double> X,Y,Z;
  plotSphere.GetPointLocations(X,Y,Z);
  vector<double> vals;

  // GENERATE GAMMA SURFACE 
  for (int i=0; i<X.size(); i++)
    {
      Vector3d n(X[i],Y[i],Z[i]);
      Matrix3d N = createMatrixFromNormalVector(n);
      double W = a - b*SurfaceIntegrate(crystal1, omega1*N, crystal2, omega2*N, stdDev, tolerance, "cauchy");
      vals.push_back(W);
      if (!(i % outputSkip) || i==X.size()-1)
	{
	  plotSphere.SetData(vals);
	  WIELD_PROGRESS("Computing gamma surface", i, X.size(), 1);
	}      
      if (printOutput) *out << X[i] << " " << Y[i] << " " << Z[i] << " " << W << endl;
    }
  cout << endl;

  // CLEAN UP
  if (printOutput) {out->close(); delete out;}
  WIELD_EXCEPTION_CATCH;
} 
}
}


#endif


