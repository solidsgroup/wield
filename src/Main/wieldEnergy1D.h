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

  Wield::Series::FourierSeries
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       reader.Read<double>("Sigma1"),
       reader.Read<std::vector<double> >("X1"),
       reader.Read<std::vector<double> >("Y1"),
       reader.Read<std::vector<double> >("Z1"));
  
  Wield::Series::FourierSeries
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
       reader.Read<double>("Sigma2"),
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
