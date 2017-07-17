#ifndef WIELD_MAIN_ENERGY2D_H
#define WIELD_MAIN_ENERGY2D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdexcept>
//#include <pthread.h>
#include <omp.h>

#include "Reader.h"

#include "Utils/wieldExceptions.h"
#include "Utils/wieldNote.h"
#include "Utils/wieldDebug.h"
#include "Series/wieldFourierSeries.h"
#include "Series/wieldGaussDirac.h"
#include "Series/wieldSqrtGaussDirac.h"
#include "Utils/VTK/wieldVTK.h"
#include "Integrator/wieldSurface.h"
#include "Integrator/wieldVolume.h"

namespace Wield
{
namespace Main
{
// typedef struct {
//   int index,numThreads;
//   double epsilon, tolerance;
//   Eigen::Matrix3d rot1, rot2;
//   Wield::Series::FourierSeries *C1, *C2;
//   vector<double> *X, *Y, *Z, *W;
// } Energy2D_t;

void *Energy2D(void *args);
void Energy2D(Reader::Reader &reader, int numThreads=1)
{
  WIELD_EXCEPTION_TRY;

  double 
    thetaMin  = reader.Read<double>("ThetaMin",0.),
    thetaMax  = reader.Read<double>("ThetaMax",360.),
    dTheta    = reader.Read<double>("DTheta",1.),
    rMin      = reader.Read<double>("RMin",0.),
    rMax      = reader.Read<double>("RMax",1.),
    dR        = reader.Read<double>("DR",.05),
    epsilon   = reader.Read<double>("Epsilon",1.),
    tolerance = reader.Read<double>("Tolerance",1E-16);

  Wield::Series::FourierSeries<Wield::Series::GaussDirac>
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       Wield::Series::GaussDirac(reader.Read<double>("Sigma1")),
       reader.Read<std::vector<double> >("X1"),
       reader.Read<std::vector<double> >("Y1"),
       reader.Read<std::vector<double> >("Z1"));

  Wield::Series::FourierSeries<Wield::Series::GaussDirac>
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
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

  // Rotation matrix
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

  std::vector<double> X,Y,Z;
  for (double theta = thetaMin; theta <= thetaMax; theta += dTheta) 
    for (double r = rMin; r <= (rMax+tolerance); r += dR) 
      {
	X.push_back(r*cos(theta*pi/180.));
	Y.push_back(r*sin(theta*pi/180.));
	if (1.-(r*r) > 0) Z.push_back(sqrt(1.-(r*r)));
	else Z.push_back(0.);
      }
  std::vector<double> W(X.size());

  double 
    c1c1 = Wield::Integrator::Volume(C1,rot1,C1,rot1,epsilon,tolerance), 
    c2c2 = Wield::Integrator::Volume(C2,rot2,C2,rot2,epsilon,tolerance), 
    c1c2 = Wield::Integrator::Volume(C1,rot1,C2,rot2,epsilon,tolerance);



  //
  // Run computation with optional OpenMP parallelism
  //

  int num = X.size();

  #pragma omp parallel for num_threads(numThreads)
  for (int i=0; i<num; i++)
    {
      int index = omp_get_thread_num();

      if (i==0) 
	WIELD_NOTE("Number of threads: " << omp_get_num_threads())

      Eigen::Vector3d n(X[i],Y[i],Z[i]);
      Eigen::Matrix3d N = createMatrixFromNormalVector(n);
      
      W[i] = Wield::Integrator::Surface(C1,N.transpose()*rot1,
      					C2,N.transpose()*rot2,
      					epsilon, tolerance);

      if (index==0) WIELD_PROGRESS("Energy surface",i,X.size()/numThreads,1);
    }
  std::cout << std::endl;


  //
  // Print results to output file
  //

  std::ofstream out(reader.Read<std::string>("OutFile").c_str());

  for (int i=0; i<X.size(); i++)
    if (normalize) 
      out << X[i] << " " << Y[i] << " " << Z[i] << " " << 1-(W[i]/ground) << std::endl;
    else
      out << X[i] << " " << Y[i] << " " << Z[i] << " " << -W[i] << std::endl;
  out.close();

  WIELD_EXCEPTION_CATCH;
}
}
}

#endif
