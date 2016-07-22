#ifndef WIELD_MAIN_CSL_H
#define WIELD_MAIN_CSL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdexcept>
#include <omp.h>

#include "Reader.h"

#include "Utils/wieldExceptions.h"
#include "Utils/wieldNote.h"
#include "Utils/wieldDebug.h"
#include "Series/wieldFourierSeries.h"
#include "Series/wieldGaussDirac.h"
#include "Series/wieldSqrtGaussDirac.h"
#include "Integrator/wieldVolume.h"

namespace Wield
{
namespace Main
{
void CSL(Reader::Reader &reader, int numThreads=1)
{
  WIELD_EXCEPTION_TRY;

  double 
     thetaMin  = reader.Read<double>("ThetaMin",0.),
     thetaMax  = reader.Read<double>("ThetaMax",360.),
     dTheta    = reader.Read<double>("DTheta",1.),
    // rMin      = reader.Read<double>("RMin",0.),
    // rMax      = reader.Read<double>("RMax",1.),
    // dR        = reader.Read<double>("DR",.05),
    epsilon   = reader.Read<double>("Epsilon",1.),
    tolerance = reader.Read<double>("Tolerance",1E-16);

  double
    thetaRotX1 = reader.Read<double>("ThetaRotX1",0.),
    thetaRotY1 = reader.Read<double>("ThetaRotY1",0.),
    thetaRotZ1 = reader.Read<double>("ThetaRotZ1",0.),
    thetaRotX2 = reader.Read<double>("ThetaRotX2",0.),
    thetaRotY2 = reader.Read<double>("ThetaRotY2",0.),
    thetaRotZ2 = reader.Read<double>("ThetaRotZ2",0.);


  Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac>
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       Wield::Series::SqrtGaussDirac(reader.Read<double>("Sigma1")),
       reader.Read<std::vector<double> >("X1"),
       reader.Read<std::vector<double> >("Y1"),
       reader.Read<std::vector<double> >("Z1"));

  Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac>
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
       Wield::Series::SqrtGaussDirac(reader.Read<double>("Sigma2")),
       reader.Read<std::vector<double> >("X2"),
       reader.Read<std::vector<double> >("Y2"),
       reader.Read<std::vector<double> >("Z2"));

  //
  // CONSTRUCT ROTATION MATRIX FOR CRYSTAL 1
  //

  Eigen::Matrix3d rot1 = Eigen::Matrix3d::Identity();
  if (reader.Find("AxisY1") && reader.Find("AxisZ1")) 
    rot1 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY1"),reader.Read<Eigen::Vector3d>("AxisZ1")).transpose() * rot1;
  if (reader.Find("AxisZ1") && reader.Find("AxisX1")) 
    rot1 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ1"),reader.Read<Eigen::Vector3d>("AxisX1")).transpose() * rot1;
  if (reader.Find("AxisX1") && reader.Find("AxisY1")) 
    rot1 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX1"),reader.Read<Eigen::Vector3d>("AxisY1")).transpose() * rot1;

  if (reader.Find("phi1_1") && reader.Find("Phi_1") && reader.Find("phi2_1"))
    {
      double phi1 = reader.Read<double>("phi1_1"); 
      double Phi = reader.Read<double>("Phi_1"); 
      double phi2 = reader.Read<double>("phi2_1"); 
      rot1 = createMatrixFromBungeEulerAngles(phi1,Phi,phi2)*rot1;
    }

  if (reader.Find("RotAxes1"))
    {
      std::vector<char> rotAxes1 = reader.Read<std::vector<char> >("RotAxes1");
      std::vector<double>  rots1 = reader.Read<std::vector<double> >("Rots1");
      for (int i=0; i<rotAxes1.size(); i++) rot1 = createMatrixFromAngle(rots1[i],rotAxes1[i]) * rot1;
    }

  //
  // CONSTRUCT ROTATION MATRIX FOR CRYSTAL 2
  //

  Eigen::Matrix3d rot2 = Eigen::Matrix3d::Identity();
  if (reader.Find("AxisY2") && reader.Find("AxisZ2")) rot2 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY2"),reader.Read<Eigen::Vector3d>("AxisZ2")).transpose() * rot2;
  if (reader.Find("AxisZ2") && reader.Find("AxisX2")) rot2 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ2"),reader.Read<Eigen::Vector3d>("AxisX2")).transpose() * rot2;
  if (reader.Find("AxisX2") && reader.Find("AxisY2")) rot2 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX2"),reader.Read<Eigen::Vector3d>("AxisY2")).transpose() * rot2;
  
  if (reader.Find("phi1_2") && reader.Find("Phi_2") && reader.Find("phi2_2"))
    {
      double phi1 = reader.Read<double>("phi1_2"); 
      double Phi = reader.Read<double>("Phi_2"); 
      double phi2 = reader.Read<double>("phi2_2"); 
      rot2 = createMatrixFromBungeEulerAngles(phi1,Phi,phi2)*rot2;
    }
  
  if (reader.Find("RotAxes2"))
    {
      std::vector<char> rotAxes2 = reader.Read<std::vector<char> >("RotAxes2");
      std::vector<double>  rots2 = reader.Read<std::vector<double> >("Rots2");
      for (int i=0; i<rotAxes2.size(); i++) rot2 = createMatrixFromAngle(rots2[i],rotAxes2[i]) * rot2;
    }

  // for (double x = -10; x < 10.0; x += 0.01)
  //   std::cout << x << " " << C1(x,0.0,0.0).real() << std::endl;
  // exit(0);

  std::cout << "computing..." << std::endl;


  std::vector<double> thetas;
  for (double theta = thetaMin; theta <= thetaMax ; theta += dTheta) thetas.push_back(theta);
  std::vector<double> sigmas(thetas.size());
  
  #pragma omp parallel for num_threads(numThreads)
  for ( int i = 0 ; i < thetas.size(); i++)
    {
      int index = omp_get_thread_num();

      Eigen::Matrix3d
	omega1 =
	createMatrixFromXAngle(thetaRotX1*thetas[i]) *
	createMatrixFromYAngle(thetaRotY1*thetas[i]) *
	createMatrixFromZAngle(thetaRotZ1*thetas[i]) *
	rot1,
	omega2 =
	createMatrixFromXAngle(thetaRotX2*thetas[i]) *
	createMatrixFromYAngle(thetaRotY2*thetas[i]) *
	createMatrixFromZAngle(thetaRotZ2*thetas[i]) *
	rot2;      
      double 
	c1c1 = Wield::Integrator::Volume(C1,omega1,C1,omega1,epsilon,tolerance), 
	c2c2 = Wield::Integrator::Volume(C2,omega2,C2,omega2,epsilon,tolerance), 
	c1c2 = Wield::Integrator::Volume(C1,omega1,C2,omega2,epsilon,tolerance);

      sigmas[i] = sqrt(c1c1)*sqrt(c2c2) / c1c2;
      //std::cout << theta << " " << c1c1 << " " << c2c2 << " " << c1c2 << " --> " << sqrt(c1c1)*sqrt(c2c2) / c1c2 << std::endl;

      //ws.push_back(w);
      if (index==0) WIELD_PROGRESS("Computing CSL", thetas[i]-thetaMin, (thetaMax-thetaMin)/numThreads, dTheta)
    }

  std::ofstream out(reader.Read<std::string>("OutFile").c_str());

  for (int i=0; i<thetas.size(); i++)
    out << thetas[i] << " " << sigmas[i] << std::endl;
  out.close();



  WIELD_EXCEPTION_CATCH;
}
}
}

#endif
