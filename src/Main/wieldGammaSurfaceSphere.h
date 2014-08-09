///
/// \file wieldGammaSurfaceSphere.h
/// \brief Wield::Main::GammaSurfaceSphere
///

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
///
/// \brief Compute the energy with Orientation Relationship fixed, and varying interface normal. 
///        The domain is specified by setting theta and phi ranges.
///
/// Input file options
///   - \b Crystal1: Parameters for the upper crystal
///   - \b Crystal2: Parameters for the lower crystal
///   - \b GammaSurfaceSphere: 
///     - (\b X1,\b Y1,\b Z1): Crystollographic axes corresponding to X,Y,Z axes. Two must be specified.
///     - (\b X2,\b Y2,\b Z2): Crystollographic axes corresponding to X,Y,Z axes. Two must be specified.
///     - \b PrePhiRotX: Additional rotation to apply about the X axis
///     - \b PrePhiRotY: Additional rotation to apply about the Y axis
///     - \b PrePhiRotZ: Additional rotation to apply about the Z axis
///     - \b AzimuthMin [0]: Minimum azimuthal angle (angle between orthogonal projection and X axis)
///     - \b AzimuthMin [360]: Maximum azimuthal angle
///     - \b AzimuthResolution [20]: Number of azimuthal points
///     - \b PolarMin [0]: Minimum polar angle (angle from Z axis)
///     - \b PolarMin [180]: Maximum polar angle
///     - \b PolarResolution [20]: Number of theta points
///     - \b Tolerance [0]: Threshold for throwing out terms from the SurfaceIntegral calculation
///     - \b OutputSkip [1]: Number of calculations between showing output visualization
///
void GammaSurfaceSphere(Reader::Reader &reader, ///< A Reader 
			bool dynamicPlotting)   ///< Toggle to specify if plot window should show during run
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
  // ADDITIONAL INTERFACE ROTATION
  double prePhiRotX = reader.Read<double>("GammaSurfaceSphere","PrePhiRotX",0.);
  double prePhiRotY = reader.Read<double>("GammaSurfaceSphere","PrePhiRotY",0.);
  double prePhiRotZ = reader.Read<double>("GammaSurfaceSphere","PrePhiRotZ",0.);		
  // CALCULATION RANGE
  double azimuthResolution = reader.Read<double>("GammaSurfaceSphere", "AzimuthResolution", 20.);
  double azimuthMin        = reader.Read<double>("GammaSurfaceSphere", "AzimuthMin", 0.);
  double azimuthMax        = reader.Read<double>("GammaSurfaceSphere", "AzimuthMax", 360.);
  double polarResolution   = reader.Read<double>("GammaSurfaceSphere", "PolarResolution", 20.);
  double polarMin          = reader.Read<double>("GammaSurfaceSphere", "PolarMin", 0.);
  double polarMax          = reader.Read<double>("GammaSurfaceSphere", "PolarMax", 180.);
  // MISC
  double tolerance       = reader.Read<double>("GammaSurfaceSphere","Tolerance",0.);
  int    outputSkip      = reader.Read<int>   ("GammaSurfaceSphere","OutputSkip",1);


  // GENERATE A SPHERE USING VTK
  Wield::Utils::VTK::PlotSphere plotSphere(azimuthResolution,polarResolution,azimuthMin,azimuthMax,polarMin,polarMax);
  vector<double> X,Y,Z;
  plotSphere.GetPointLocations(X,Y,Z);
  vector<double> vals;

  // GENERATE GAMMA SURFACE 
  for (int i=0; i<X.size(); i++)
    {
      Vector3d n(X[i],Y[i],Z[i]);
      Matrix3d N = 
	createMatrixFromXAngle(prePhiRotX)*
	createMatrixFromYAngle(prePhiRotY)*
	createMatrixFromZAngle(prePhiRotZ)*
	createMatrixFromNormalVector(n);
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


