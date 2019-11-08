#ifndef WIELD_MAIN_CSL_H
#define WIELD_MAIN_CSL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdexcept>
#include <omp.h>

#include "Reader/Reader.h"

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

/// Coincident Site Lattice Computation
/// ===================================
/// 
/// Compute the Coincident Site Lattice \f$\Sigma\f$ value for a bicrystal.
/// The setup for this function is very similar to that for grain boundary computations.
/// Here is an example input file to compute \f$\Sigma\f$ for FCC aluminum tilte about the
/// [100] axis:
/// 
///     $CSL
///     $a 3.597
///     $Sigma1 0.06
///     $Epsilon 0.3
///     $Order1 64
///     $AlphaX1 $a
///     $AlphaY1 $a
///     $AlphaZ1 $a
///     $X1 0.    0.     0.     0.     0. $a/2. -$a/2.  $a/2. -$a/2. $a/2.  $a/2. -$a/2. -$a/2.
///     $Y1 0. $a/2.  $a/2. -$a/2. -$a/2.    0.     0.     0.     0. $a/2. -$a/2.  $a/2. -$a/2.
///     $Z1 0. $a/2. -$a/2.  $a/2. -$a/2. $a/2.  $a/2. -$a/2. -$a/2.    0.     0.     0.     0.
///     $Tolerance 1E-8
///     $ThetaRotX1 0.5
///     $ThetaRotX2 -0.5
///     $ThetaMin 0
///     $ThetaMax 45
///     $DTheta 0.1
///     $OutFile csl_$Sigma1_$Epsilon.dat
///
/// Additional examples are included in the tests directory.
/// 
/// **Relevant Publications**
/// - B Runnels,
///   [A projection-based formulation of the coincident site lattice \f$\Sigma\f$ for arbitrary bicrystals at finite temperature](http://scripts.iucr.org/cgi-bin/paper?S205327331700122X)
///   *Acta Crystallographica A*, 2017
void CSL(Reader::Reader &reader, ///< [in] Reader object to parse input commands
	 int numThreads=1,       ///< [in] Number of OpenMP threads to spawn
	 bool verbose=false      ///< [in] Whether to include extra output information
	 )
{
  WIELD_EXCEPTION_TRY;
  if(verbose) WIELD_NOTE("Beginning CSL Computation")
  if(verbose) WIELD_NOTE("Reading in parameters")

  double 
     thetaMin  = reader.Read<double>("ThetaMin",0.),
     thetaMax  = reader.Read<double>("ThetaMax",0.),
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

  Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac> *C1, *C2;

  if(verbose) WIELD_NOTE("Generating crystal 1");

  
  C1 = new Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac>
    (reader.Read<int>("Order1"),
     reader.Read<double>("AlphaX1"),
     reader.Read<double>("AlphaY1"),
     reader.Read<double>("AlphaZ1"),
     Wield::Series::SqrtGaussDirac(reader.Read<double>("Sigma1")),
     reader.Read<std::vector<double> >("X1"),
     reader.Read<std::vector<double> >("Y1"),
     reader.Read<std::vector<double> >("Z1"),
     numThreads,
     verbose);
  
//  std::cout << "Start writing file" << std::endl;
//  std::ofstream myfile;
//  myfile.open("field.dat");
//  for (double x = -4*0.5*sqrt(3.); x < 4*0.5*sqrt(3.); x+=0.1)
//    for (double y = -4*1.5; y < 4*1.5; y+=0.1)
//    {
//      std::cout << "x = " << x << " y = " << y << " C = " << (*C1)(x,y,0.0).real() << std::endl;
//      myfile << x << " " << y << " " << (*C1)(x,y,0.0).real() << std::endl;
//    }
//  myfile.close();
//  std::cout << "Done writing file" << std::endl;


  
  if (reader.Find("Order2") 
      && reader.Find("AlphaX2") && reader.Find("AlphaY2") && reader.Find("AlphaZ2") 
      && reader.Find("Sigma2") 
      && reader.Find("X2") && reader.Find("Y2") && reader.Find("Z2"))
    {
      if(verbose) WIELD_NOTE("Generating crystal 2");
      C2 = new Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac>(reader.Read<int>("Order2"),
									     reader.Read<double>("AlphaX2"),
									     reader.Read<double>("AlphaY2"),
									     reader.Read<double>("AlphaZ2"),
									     Wield::Series::SqrtGaussDirac(reader.Read<double>("Sigma2")),
									     reader.Read<std::vector<double> >("X2"),
									     reader.Read<std::vector<double> >("Y2"),
									     reader.Read<std::vector<double> >("Z2"),
                       numThreads,
									     verbose);
    }
  else
    {
      if(verbose) WIELD_NOTE("Creating a copy of crystal 1");
      C2 = new Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac>(*C1);
    }

  //
  // Rotation matrix 1
  //
  if(verbose) WIELD_NOTE("Computing rotation matrices")

  Eigen::Matrix3d rot1 = Eigen::Matrix3d::Identity();
  if (reader.Find("AxisY1") && reader.Find("AxisZ1"))
    rot1 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY1"),reader.Read<Eigen::Vector3d>("AxisZ1")).transpose() * rot1;
  else if (reader.Find("AxisZ1") && reader.Find("AxisX1"))
    rot1 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ1"),reader.Read<Eigen::Vector3d>("AxisX1")).transpose() * rot1; // added transpose
  else if (reader.Find("AxisX1") && reader.Find("AxisY1"))
    rot1 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX1"),reader.Read<Eigen::Vector3d>("AxisY1")).transpose() * rot1; // added transpose
  else if (reader.Find("RotAxes1"))
    {
      std::vector<char> rotAxes1 = reader.Read<std::vector<char> >("RotAxes1");
      std::vector<double>  rots1 = reader.Read<std::vector<double> >("Rots1");
      for (int i=0; i<rotAxes1.size(); i++) rot1 = createMatrixFromAngle(rots1[i],rotAxes1[i]) * rot1;
    }
  if (verbose) WIELD_NOTE("Rot1 components: " << std::endl << rot1);
  if (verbose) WIELD_NOTE("Rot1 Euler angles: " << rot1.eulerAngles(2,0,2).transpose()*180./pi);

  //
  // Rotation matrix 2
  //

  Eigen::Matrix3d rot2 = Eigen::Matrix3d::Identity();
  if (reader.Find("AxisY2") && reader.Find("AxisZ2")) 
    rot2 = createMatrixFromYZ(reader.Read<Eigen::Vector3d>("AxisY2"),reader.Read<Eigen::Vector3d>("AxisZ2")).transpose() * rot2; // added transpose
  else if (reader.Find("AxisZ2") && reader.Find("AxisX2")) 
    rot2 = createMatrixFromZX(reader.Read<Eigen::Vector3d>("AxisZ2"),reader.Read<Eigen::Vector3d>("AxisX2")).transpose() * rot2; // added transpose
  else if (reader.Find("AxisX2") && reader.Find("AxisY2")) 
    rot2 = createMatrixFromXY(reader.Read<Eigen::Vector3d>("AxisX2"),reader.Read<Eigen::Vector3d>("AxisY2")).transpose() * rot2; // added transpose
  else if (reader.Find("RotAxes2"))
    {
      std::vector<char> rotAxes2 = reader.Read<std::vector<char> >("RotAxes2");
      std::vector<double>  rots2 = reader.Read<std::vector<double> >("Rots2");
      for (int i=0; i<rotAxes2.size(); i++) rot2 = createMatrixFromAngle(rots2[i],rotAxes2[i]) * rot2;
    }
  if (verbose) WIELD_NOTE("Rot2 components: " << std::endl << rot2);
  if (verbose) WIELD_NOTE("Rot2 Euler angles: " << rot2.eulerAngles(2,0,2).transpose()*180./pi);


  std::vector<double> thetas;
  for (double theta = thetaMin; theta <= thetaMax ; theta += dTheta) thetas.push_back(theta);
  std::vector<double> sigmas(thetas.size());
  if(verbose) WIELD_NOTE("Beginning computation: with thetaMin="<<thetaMin<<", thetaMax="<<thetaMax<<", dTheta="<<dTheta<<", # of computations = "<<thetas.size());

  
  if (verbose) WIELD_NOTE("Computing norm of crystal 1");
  double c1c1 = Wield::Integrator::Volume(*C1,rot1,*C1,rot1,epsilon,tolerance,false);
  if (verbose) WIELD_NOTE("Computing norm of crystal 2");
  double c2c2 = Wield::Integrator::Volume(*C2,rot2,*C2,rot2,epsilon,tolerance,false); 
  
  #pragma omp parallel for num_threads(numThreads)
  for ( int i = 0 ; i < thetas.size(); i++)
    {
      int index = omp_get_thread_num();
      //if (index != 0) verbose = false;

      //if (verbose){ WIELD_NOTE("Computing for theta " << i << " / " << thetas.size());}
      if (index==0) WIELD_PROGRESS("Computing CSL", thetas[i]-thetaMin, (thetaMax-thetaMin)/numThreads, dTheta);

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
	c1c2 = Wield::Integrator::Volume(*C1,omega1,*C2,omega2,epsilon,tolerance,false);

      sigmas[i] = sqrt(c1c1)*sqrt(c2c2) / c1c2;
    }
  WIELD_PROGRESS_COMPLETE("Computing CSL");

  std::ofstream out(reader.Read<std::string>("OutFile").c_str());

  for (int i=0; i<thetas.size(); i++)
    out << thetas[i] << " " << sigmas[i] << std::endl;
  out.close();



  WIELD_EXCEPTION_CATCH;
}
}
}

#endif
