///
/// Input parameters
/// ================
/// 
/// This section describes the possible input parameters used by Wield to generate a 1D energy curve parameterized by a free variable \f$\theta\f$.
/// Note that the description of some parameters are condensed: for instance $Alpha(X/Y/Z)(1/2) means that there are six variables, $AlphaX1, $AlphaX2, $AlphaY1, and so on.
/// Paramaters can be specified in the input file, or can be passed through the command line using the -D flag.
///
/// Crystal structure
/// -----------------
///
/// \param $Alpha(X/Y/Z)(1/2) Dimension of the unit cell X/Y/Z direction for lattice 1/2
/// \param $Order(1/2) Number of terms in the Fourier series to keep
/// \param $(X/Y/Z)(1/2) A list of all X/Y/Z coordinates of each atom in the unit cell of lattice 1/2. 
///        Boundary atoms will be included, atoms outside the unit cell will be ignored.
///        \b Note: dimensions must match for each lattice, i.e. $X1, $Y1, $Z1 must have the same number of items in the list.
/// 
/// Example for constructing an FCC crystal for lattice 1:
///
///       $a 3.615
///       $Order1 8
///       $AlphaX1 $a
///       $AlphaY1 $a
///       $AlphaZ1 $a
///       $X1 0.    0.     0.     0.     0. $a/2. -$a/2.  $a/2. -$a/2. $a/2.  $a/2. -$a/2. -$a/2.
///       $Y1 0. $a/2.  $a/2. -$a/2. -$a/2.    0.     0.     0.     0. $a/2. -$a/2.  $a/2. -$a/2.
///       $Z1 0. $a/2. -$a/2.  $a/2. -$a/2. $a/2.  $a/2. -$a/2. -$a/2.    0.     0.     0.     0.
///
/// Note the use of the variable $a in constructing the crystal structure.
/// Also notice that the choice of unit cell is shifted from the usual FCC unit cell so that there is an atom at the origin.
///
/// Numerical parameters
/// --------------------
///
/// \param $Sigma1/2 Nondimensionalized temperature for lattice 1,2
/// \param $Epsilon Numerical window function parameter
/// 
/// Example:
///
///       $Epsilon 0.5
///       $Sigma1 0.05
///
/// Ground state energy
/// -------------------
///
/// The ground state energy is the minimum possible energy that can be taken by the boundary. 
/// It is a particular orientation of the interface when the top and bottom crystals are identical.
/// 
/// \param $Ground Provide a numerical value for the ground state energy (depricated -- use the other variables instead.)
/// \param $Ground(X/Z)(1/2) Compute the ground state by providing the X and Z vectors corresponding to the minimum energy state. 
///
/// The Ground variables are always the same for all FCC bicrystals and for all BCC bicrystals
/// Generally, the Z axis should correspond to one of the slip planes in the crystal, and then the choice of X axis needs only to be orthogonal.
/// Example:
///
///       #For FCC:
///       $GroundZ1 1 1 1
///       $GroundZ2 1 1 1
///       $GroundX1 -1 1 0
///       $GroundX2 -1 1 0
///       #For BCC:
///       $GroundZ1 1 1 0
///       $GroundZ2 1 1 0
///       $GroundX1 0 0 1
///       $GroundX2 0 0 1
///
/// Orientation parameters
/// ----------------------
/// 
/// All rotations are given in degrees.
///
/// \param $phi1_1/2 The first Bunge Euler angle for lattice 1/2 (default 0)
/// \param $Phi_1/2 The second Bunge Euler angle for lattice 1/2 (default 0)
/// \param $phi2_1/2 The third Bunge Euler angle for lattice 1/2 (default 0)
/// \param $Axis(X/Y/Z)(1/2) Generate a rotation matrix based on miller indices.  (default: none)
///        E.g. to generate a rotation such that the for lattice 1 X axis corresponds to the [111] direction and the Z axis corresponds to [10-1], set $AxisX1 to 1 1 1 and $AxisZ1 to 1 0 -1.
///        \b Note: for each lattice, specify only two of the three possible axes -- the third will be automatically computed.
///        \b Note: the right hand rule must be obeyed, but the vectors do not have to be orthonormal.
/// \param $RotAxes1/2 An arbitrarily long list of axes about which to rotate the lattice. \b Note: using $RotAxes1/2 and $Rots1/2 is the preferred way to configure lattices.
/// \param $Rots1/2 The angles by which to rotate each of the above axes. \b Note: number of rotation angles must correspond to the number of axes in $RotAxes1/2.
///
/// 1D range of rotations
/// ---------------------
/// 
/// \f$\theta\f$ is a free variable that is used to evaluate energy for a continuous range of rotations.
/// It is used to generate rotations for each lattice that are in addition to the orientation rotations (above).
/// \f$\theta\f$ ranges from ThetaMin to ThetaMax and is incremented by dTheta.
/// The ThetaRot parameters determine how much rotation to apply to each; for instance in symmetric tilt about the X axis, the following would be set:
///
///      $ThetaRotX1 0.5
///      $ThetaRotX1 -0.5
///
/// The rotation composition and order of operations is given by the following:
/// \f[ R_{total}(\theta) = R_{X}(($ThetaRotX1) \, \theta) R_{Y}(($ThetaRotY1) \, \theta) R_{Z}(($ThetaRotZ1) \, \theta) R_{orientation} \f]
/// By default, all Theta variables are zero so that if none of them are set, only the energy for the original orientation will be computed.
///
/// \param $ThetaMin Minimum value of \f$\theta\f$ (default: 0)
/// \param $ThetaMax Maximum value of \f$\theta\f$ (default: 0)
/// \param $dTheta Value by which to increment \f$\theta\f$ (default: 0)
/// \param $ThetaRot(X/Y/Z)(1/2) Amount of rotation of lattice 1/2 about axis X/Y/Z
///   
/// Example usage for symmetric tilt about the X axis from 0 to 90 degrees:
///
///       $ThetaMin 0
///       $ThetaMax 90
///       $DTheta 1
///       $ThetaRotX1 0.5
///       $ThetaRotX1 -0.5
///
/// Output file
/// -----------
///
/// All information is output to a single output file specified by OutFile:
///
/// \param $OutFile The path to the output file
///



///
/// \file wieldEnergy1D.h
/// \brief This is the short description for wieldEnergy1D.h
///


#ifndef WIELD_MAIN_ENERGY1D_H
#define WIELD_MAIN_ENERGY1D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdexcept>


#include "Reader.h"

#include "Utils/wieldExceptions.h"
#include "Series/wieldFourierSeries.h"
#include "Series/wieldGaussDirac.h"
#include "Utils/VTK/wieldVTK.h"
#include "Integrator/wieldSurface.h"
#include "Optimization/wieldConvexify1D.h"

namespace Wield
{
namespace Main
{
void Energy1D(Reader::Reader &reader)
{
  WIELD_EXCEPTION_TRY;
  
  double
    thetaMin = reader.Read<double>("ThetaMin"),
    thetaMax = reader.Read<double>("ThetaMax"),
    dTheta = reader.Read<double>("DTheta"),
    epsilon = reader.Read<double>("Epsilon",0.2),
    tolerance = reader.Read<double>("Tolerance",1E-16);
  
  bool 
    convexify     = reader.Find("Convexify"),
    fullConvexify = reader.Find("FullConvexify");

  Wield::Series::FourierSeries<Wield::Series::GaussDirac>
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       Wield::Series::GaussDirac(reader.Read<double>("Sigma1")),
       //reader.Read<double>("Sigma1"),
       reader.Read<std::vector<double> >("X1"),
       reader.Read<std::vector<double> >("Y1"),
       reader.Read<std::vector<double> >("Z1"));
  
  Wield::Series::FourierSeries<Wield::Series::GaussDirac>
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
       Wield::Series::GaussDirac(reader.Read<double>("Sigma2")),
       //reader.Read<double>("Sigma2"),
       reader.Read<std::vector<double> >("X2"),
       reader.Read<std::vector<double> >("Y2"),
       reader.Read<std::vector<double> >("Z2"));

  bool normalize = false;
  double ground  = 0.;
  if (reader.Find("GroundZ1"))
    {
      normalize = true;

      Eigen::Matrix3d groundRot1 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("GroundZ1"),
					       reader.Read<Eigen::Vector3d>("GroundX1")).transpose();
      Eigen::Matrix3d groundRot2 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("GroundZ2"),
					       reader.Read<Eigen::Vector3d>("GroundX2")).transpose();
      double g1 = Wield::Integrator::Surface(C1,groundRot1,C1,groundRot1,epsilon,tolerance);
      double g2 = Wield::Integrator::Surface(C2,groundRot2,C2,groundRot2,epsilon,tolerance);
      ground = sqrt(g1*g2);

      if (ground != ground) 
	WIELD_EXCEPTION_NEW("Computed ground state energy invalid: g1=" << g1 << ", g2=" << g2);

      if (fabs(ground) < 1E-32)
	WIELD_WARNING("Ground very small (" << ground << "). Maybe increase tolerance?")

      ground *= (1 + tolerance);
    }
  if (reader.Find("Ground"))
    {
      if (normalize) WIELD_WARNING("Ground value being overwritten!");
      
      normalize = true;

      ground = reader.Read<double>("Ground");
    }

  std::ofstream out(reader.Read<std::string>("OutFile").c_str());

  // Rotation matrix
  Eigen::Matrix3d rot1 = Eigen::Matrix3d::Identity();
  if (reader.Find("phi1_1") && reader.Find("Phi_1") && reader.Find("phi2_1"))
    {
      double phi1 = reader.Read<double>("phi1_1"); 
      double Phi = reader.Read<double>("Phi_1"); 
      double phi2 = reader.Read<double>("phi2_1"); 
      rot1 = createMatrixFromBungeEulerAngles(phi1,Phi,phi2)*rot1;
    }
  else if (reader.Find("AxisY1") && reader.Find("AxisZ1")) rot1 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY1"),reader.Read<Eigen::Vector3d>("AxisZ1")).transpose() * rot1;
  else if (reader.Find("AxisZ1") && reader.Find("AxisX1")) rot1 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ1"),reader.Read<Eigen::Vector3d>("AxisX1")).transpose() * rot1;
  else if (reader.Find("AxisX1") && reader.Find("AxisY1")) rot1 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX1"),reader.Read<Eigen::Vector3d>("AxisY1")).transpose() * rot1;
  else if (reader.Find("RotAxes1"))
    {
      std::vector<char> rotAxes1 = reader.Read<std::vector<char> >("RotAxes1");
      std::vector<double>  rots1 = reader.Read<std::vector<double> >("Rots1");
      for (int i=0; i<rotAxes1.size(); i++) rot1 = createMatrixFromAngle(rots1[i],rotAxes1[i]) * rot1;
    }

  Eigen::Matrix3d rot2 = Eigen::Matrix3d::Identity();
  if (reader.Find("phi1_2") && reader.Find("Phi_2") && reader.Find("phi2_2"))
    {
      double phi1 = reader.Read<double>("phi1_2"); 
      double Phi  = reader.Read<double>("Phi_2"); 
      double phi2 = reader.Read<double>("phi2_2"); 
      rot2 = createMatrixFromBungeEulerAngles(phi1,Phi,phi2)*rot2;
    }
  if (reader.Find("AxisY2") && reader.Find("AxisZ2")) rot2 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY2"),reader.Read<Eigen::Vector3d>("AxisZ2")).transpose() * rot2;
  if (reader.Find("AxisZ2") && reader.Find("AxisX2")) rot2 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ2"),reader.Read<Eigen::Vector3d>("AxisX2")).transpose() * rot2;
  if (reader.Find("AxisX2") && reader.Find("AxisY2")) rot2 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX2"),reader.Read<Eigen::Vector3d>("AxisY2")).transpose() * rot2;
  if (reader.Find("RotAxes2"))
    {
      std::vector<char> rotAxes2 = reader.Read<std::vector<char> >("RotAxes2");
      std::vector<double>  rots2 = reader.Read<std::vector<double> >("Rots2");
      for (int i=0; i<rotAxes2.size(); i++) rot2 = createMatrixFromAngle(rots2[i],rotAxes2[i]) * rot2;
    }

  double
    thetaRotX1 = reader.Read<double>("ThetaRotX1",0.),
    thetaRotY1 = reader.Read<double>("ThetaRotY1",0.),
    thetaRotZ1 = reader.Read<double>("ThetaRotZ1",0.),
    thetaRotX2 = reader.Read<double>("ThetaRotX2",0.),
    thetaRotY2 = reader.Read<double>("ThetaRotY2",0.),
    thetaRotZ2 = reader.Read<double>("ThetaRotZ2",0.);

  double w = 0;
  std::vector<double> thetas, ws;

  for (double theta = thetaMin; theta <= thetaMax ; theta += dTheta)
    {
      Eigen::Matrix3d
	omega1 =
	createMatrixFromXAngle(thetaRotX1*theta) *
	createMatrixFromYAngle(thetaRotY1*theta) *
	createMatrixFromZAngle(thetaRotZ1*theta) *
	rot1,
	omega2 =
	createMatrixFromXAngle(thetaRotX2*theta) *
	createMatrixFromYAngle(thetaRotY2*theta) *
	createMatrixFromZAngle(thetaRotZ2*theta) *
	rot2;      
      w = Wield::Integrator::Surface(C1,omega1,
				     C2,omega2,
				     epsilon, tolerance);
      if (normalize)
	w = 1-(w/ground);
      else
	w = -w;

      thetas.push_back(theta);
      ws.push_back(w);
      WIELD_PROGRESS("Computing energy", theta-thetaMin, thetaMax-thetaMin, dTheta)
    }
  std::cout << std::endl;

  if (convexify || fullConvexify)
    {
      std::vector<double> wulff;
      std::vector<double> wcs = Wield::Optimization::Convexify1DAngles(thetas,ws,wulff,fullConvexify);
      for (int i=0; i<thetas.size(); i++)
	out << thetas[i] << " " << ws[i] << " " << wcs[i] << " " << wulff[i] << std::endl;
    }
  else
    for (int i=0; i<thetas.size(); i++)
      out << thetas[i] << " " << ws[i] << std::endl;


  out.close();


  WIELD_EXCEPTION_CATCH;
}
}
}

#endif
