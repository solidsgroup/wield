#ifndef WIELD_MAIN_ENERGYOFFSET_H
#define WIELD_MAIN_ENERGYOFFSET_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdexcept>


#include "solidsuccs-reader/Reader.h"

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
void EnergyOffset(Reader::Reader &reader)
{
  WIELD_EXCEPTION_TRY;
  
  double
    theta = reader.Read<double>("Theta"),
    epsilon = reader.Read<double>("Epsilon",0.2),
    tolerance = reader.Read<double>("Tolerance",1E-16);
  
  Wield::Series::FourierSeries<Wield::Series::GaussDirac>
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       //reader.Read<double>("Sigma1"),
       Wield::Series::GaussDirac(reader.Read<double>("Sigma1")), 
       reader.Read<std::vector<double> >("X1"),
       reader.Read<std::vector<double> >("Y1"),
       reader.Read<std::vector<double> >("Z1"));
  
  Wield::Series::FourierSeries<Wield::Series::GaussDirac>
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
       //reader.Read<double>("Sigma2"),
       Wield::Series::GaussDirac(reader.Read<double>("Sigma2")), 
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
  if (reader.Find("AxisY1") && reader.Find("AxisZ1")) rot1 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY1"),reader.Read<Eigen::Vector3d>("AxisZ1")).transpose() * rot1;
  if (reader.Find("AxisZ1") && reader.Find("AxisX1")) rot1 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ1"),reader.Read<Eigen::Vector3d>("AxisX1")).transpose() * rot1;
  if (reader.Find("AxisX1") && reader.Find("AxisY1")) rot1 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX1"),reader.Read<Eigen::Vector3d>("AxisY1")).transpose() * rot1;
  if (reader.Find("RotAxes1"))
    {
      std::vector<char> rotAxes1 = reader.Read<std::vector<char> >("RotAxes1");
      std::vector<double>  rots1 = reader.Read<std::vector<double> >("Rots1");
      for (int i=0; i<rotAxes1.size(); i++) rot1 = createMatrixFromAngle(rots1[i],rotAxes1[i]) * rot1;
    }

  Eigen::Matrix3d rot2 = Eigen::Matrix3d::Identity();
  if (reader.Find("AxisY2") && reader.Find("AxisZ2")) rot2 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY2"),reader.Read<Eigen::Vector3d>("AxisZ2")).transpose() * rot2;
  if (reader.Find("AxisZ2") && reader.Find("AxisX2")) rot2 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ2"),reader.Read<Eigen::Vector3d>("AxisX2")).transpose() * rot2;
  if (reader.Find("AxisX2") && reader.Find("AxisY2")) rot2 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX2"),reader.Read<Eigen::Vector3d>("AxisY2")).transpose() * rot2;
  if (reader.Find("RotAxes2"))
    {
      std::vector<char> rotAxes2 = reader.Read<std::vector<char> >("RotAxes2");
      std::vector<double>  rots2 = reader.Read<std::vector<double> >("Rots2");
      for (int i=0; i<rotAxes2.size(); i++) rot2 = createMatrixFromAngle(rots2[i],rotAxes2[i]) * rot2;
    }

  double tX1Min = reader.Read<double>("TX1Min",0.);
  double tY1Min = reader.Read<double>("TY1Min",0.);
  //double tZ1Min = reader.Read<double>("TZ1Min",0.);
  double tX1Max = reader.Read<double>("TX1Max",0.);
  double tY1Max = reader.Read<double>("TY1Max",0.);
  //double tZ1Max = reader.Read<double>("TZ1Max",0.);
  double dTX1   = reader.Read<double>("DTX1",1.);
  double dTY1   = reader.Read<double>("DTY1",1.);
  //double dTZ1   = reader.Read<double>("DTZ1",1.);

  double
    thetaRotX1 = reader.Read<double>("ThetaRotX1",0.),
    thetaRotY1 = reader.Read<double>("ThetaRotY1",0.),
    thetaRotZ1 = reader.Read<double>("ThetaRotZ1",0.),
    thetaRotX2 = reader.Read<double>("ThetaRotX2",0.),
    thetaRotY2 = reader.Read<double>("ThetaRotY2",0.),
    thetaRotZ2 = reader.Read<double>("ThetaRotZ2",0.);

  double w = 0;
  std::vector<Eigen::Vector3d > ts;
  std::vector<double> ws;

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

  for (double tX1 = tX1Min; tX1 <= tX1Max; tX1 += dTX1)
    for (double tY1 = tY1Min; tY1 <= tY1Max; tY1 += dTY1)
      // for (double tZ1 = tZ1Min; tZ1 <= tZ1Max; tZ1 += dTZ1)
	{
	  //Eigen::Vector3d t1(tX1,tY1,tZ1);
	  Eigen::Vector3d t1(tX1,tY1,0);
	  Eigen::Vector3d t2(0,0,0);
	  w = Wield::Integrator::Surface(C1,omega1,t1,
					 C2,omega2,t2,
					 epsilon, tolerance);
	  if (normalize)
	    w = 1-(w/ground);
	  else
	    w = -w;
	  ts.push_back(t1);
	  ws.push_back(w);
	  WIELD_PROGRESS("Computing energy", tX1-tX1Min, tX1Max-tX1Min, dTX1);
	}

  std::cout << std::endl;

  for (int i=0; i<ts.size(); i++)
    out << (ts[i])[0] << " " << (ts[i])[1] << " " << ws[i] << std::endl;
  //out << (ts[i])[0] << " " << (ts[i])[1] << " " << (ts[i])[2] << " " << ws[i] << endl;


  out.close();


  WIELD_EXCEPTION_CATCH;
}
}
}

#endif
