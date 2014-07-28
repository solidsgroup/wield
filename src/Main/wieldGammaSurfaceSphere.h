#ifndef WIELD_MAIN_GAMMASURFACESPHERE_H
#define WIELD_MAIN_GAMMASURFACESPHERE_H

#include "Utils/VTK/wieldPlotSphere.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldProgress.h"
#include "SurfaceIntegrate.h"

#include "Reader.h"

namespace wield
{
namespace main
{
void gammaSurfaceSphere(Reader reader, bool dynamicPlotting)
{
  WIELD_EXCEPTION_TRY;

  // {{{ FILE INPUT/OUTPUT
  bool printOutput = reader.Find("GammaSurfaceSphere","OutFile");
  ofstream *out;
  if (printOutput) out = new ofstream(reader.Read<string>("GammaSurfaceSphere","OutFile").c_str());
  // }}}
  // {{{ SPECIFY ORIENTATION OF CRYSTAL 1
  Matrix3d Omega_1;
  if (reader.Find("GammaSurfaceSphere","X1") && reader.Find("GammaSurfaceSphere","Y1"))
    Omega_1 = createMatrixFromXY(reader.Read<Vector3d>("GammaSurfaceSphere","X1"), reader.Read<Vector3d>("GammaSurfaceSphere","Y1"));
  else if (reader.Find("GammaSurfaceSphere","Y1") && reader.Find("GammaSurfaceSphere","Z1"))
    Omega_1 = createMatrixFromYZ(reader.Read<Vector3d>("GammaSurfaceSphere","Y1"), reader.Read<Vector3d>("GammaSurfaceSphere","Z1"));
  else if (reader.Find("GammaSurfaceSphere","Z1") && reader.Find("GammaSurfaceSphere","X1"))
    Omega_1 = createMatrixFromZX(reader.Read<Vector3d>("GammaSurfaceSphere","Z1"), reader.Read<Vector3d>("GammaSurfaceSphere","X1"));
  else WIELD_EXCEPTION_NEW("Missing two vectors to specify Omega_1");
  // }}}
  // {{{ SPECIFY ORIENTATION OF CRYSTAL 2
  Matrix3d Omega_2; 
  if (reader.Find("GammaSurfaceSphere","X2") && reader.Find("GammaSurfaceSphere","Y2"))
    Omega_2 = createMatrixFromXY(reader.Read<Vector3d>("GammaSurfaceSphere","X2"), reader.Read<Vector3d>("GammaSurfaceSphere","Y2"));
  else if (reader.Find("GammaSurfaceSphere","Y2") && reader.Find("GammaSurfaceSphere","Z2"))
    Omega_2 = createMatrixFromYZ(reader.Read<Vector3d>("GammaSurfaceSphere","Y2"), reader.Read<Vector3d>("GammaSurfaceSphere","Z2"));
  else if (reader.Find("GammaSurfaceSphere","Z2") && reader.Find("GammaSurfaceSphere","X2"))
    Omega_2 = createMatrixFromZX(reader.Read<Vector3d>("GammaSurfaceSphere","Z2"), reader.Read<Vector3d>("GammaSurfaceSphere","X2"));
  else WIELD_EXCEPTION_NEW("Missing two vectors to specify Omega_2");
  // }}}
  // {{{ LATTICE COEFFICIENTS: TOP CRYSTAL
  string f1 = reader.Read<string>("GammaSurfaceSphere","Crystal1");
  Reader crystal1Reader(f1, "$", "#", "...");
  int order1 = crystal1Reader.Read<int>("order");
  CosSeries C1(order1); crystal1Reader.Read<CosSeries>("C", &C1);
  C1.order = order1;
  C1.alpha1 = crystal1Reader.Read<double>("a1");
  C1.alpha2 = crystal1Reader.Read<double>("a2");
  C1.alpha3 = crystal1Reader.Read<double>("a3");
  // }}}
  // {{{ LATTICE COEFFICIENTS: BOTTOM CRYSTAL
  string f2 = reader.Read<string>("GammaSurfaceSphere","Crystal2");
  Reader crystal2Reader(f2, "$", "#", "...");
  int order2 = crystal2Reader.Read<int>("order");
  CosSeries C2(order2); crystal2Reader.Read<CosSeries>("C", &C2);
  C2.order = order2;
  C2.alpha1 = crystal2Reader.Read<double>("a1");
  C2.alpha2 = crystal2Reader.Read<double>("a2");
  C2.alpha3 = crystal2Reader.Read<double>("a3");
  // }}}
  // {{{ ADJUSTABLE PARAMETERS
  double A,B,stdev;
  if (reader.Find("GammaSurfaceSphere","f_constants"))
    {
      string f_constants = reader.Read<string>("GammaSurfaceSphere","f_constants");
      Reader constantsReader(f_constants, "$", "#", "...");
      if (reader.Find("GammaSurfaceSphere","A"))     A = reader.Read<double>("GammaSurfaceSphere","A");
      else                      A = constantsReader.Read<double>("A");
      if (reader.Find("GammaSurfaceSphere","B"))     B = reader.Read<double>("GammaSurfaceSphere","B");
      else                      B = constantsReader.Read<double>("B");
      if (reader.Find("GammaSurfaceSphere","StdDev")) stdev = reader.Read<double>("GammaSurfaceSphere","StdDev");
      else                      stdev = constantsReader.Read<double>("StdDev");
    }
  else // Otherwise, look in the current file
    {
      A = reader.Read<double>("GammaSurfaceSphere","A");
      B = reader.Read<double>("GammaSurfaceSphere","B");
      stdev = reader.Read<double>("GammaSurfaceSphere","StdDev");
    }
  // }}}
  // {{{ CALCULATION RANGE
  double thetaResolution = reader.Read<double>("GammaSurfaceSphere", "ThetaResolution", 20.);
  double thetaMin = reader.Read<double>("GammaSurfaceSphere", "ThetaMin", 0.);
  double thetaMax = reader.Read<double>("GammaSurfaceSphere", "ThetaMax", 360.);
  double phiResolution = reader.Read<double>("GammaSurfaceSphere", "ThetaResolution", 20.);
  double phiMin = reader.Read<double>("GammaSurfaceSphere", "PhiMin", 0.);
  double phiMax = reader.Read<double>("GammaSurfaceSphere", "PhiMax", 180.);
  // }}}
  // {{{ MISC
  double tolerance = reader.Read<double>("GammaSurfaceSphere","Tolerance",0.);
  int outputSkip = reader.Read<int>("GammaSurfaceSphere","OutputSkip",1);
  // }}}

  wield::utils::vtk::PlotSphere plotSphere(thetaResolution,phiResolution,thetaMin,thetaMax,phiMin,phiMax);
  vector<double> X,Y,Z;
  plotSphere.GetPointLocations(X,Y,Z);
  vector<double> vals;
  for (int i=0; i<X.size(); i++)
    {
      Vector3d n(X[i],Y[i],Z[i]);
      Matrix3d N = createMatrixFromNormalVector(n);
      double W = A - B*SurfaceIntegrate(C1, Omega_1*N, C2, Omega_2*N, stdev, tolerance, "cauchy");
      vals.push_back(W);
      if (!(i % outputSkip) || i==X.size()-1)
	{
	  plotSphere.SetScalarValues(vals);
	  WIELD_PROGRESS("Computing gamma surface", i, X.size(), 1);
	}      
      if (printOutput) *out << X[i] << " " << Y[i] << " " << Z[i] << " " << W << endl;
    }
  cout << endl;
  if (printOutput) out->close();
  WIELD_EXCEPTION_CATCH;
} 
}
}


#endif


