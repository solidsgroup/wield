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

using namespace std;

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
    tolerance = reader.Read<double>("Tolerance",1E-4);
  
  Wield::Series::FourierSeries
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       reader.Read<double>("Sigma1"),
       reader.Read<vector<double> >("X1"),
       reader.Read<vector<double> >("Y1"),
       reader.Read<vector<double> >("Z1"));
  
  Wield::Series::FourierSeries
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
       reader.Read<double>("Sigma2"),
       reader.Read<vector<double> >("X2"),
       reader.Read<vector<double> >("Y2"),
       reader.Read<vector<double> >("Z2"));

  ofstream out(reader.Read<string>("OutFile").c_str());

  Matrix3d
    rot1 =
    createMatrixFromZAngle(reader.Read<double>("RotZ1",0.))*
    createMatrixFromYAngle(reader.Read<double>("RotY1",0.))*
    createMatrixFromXAngle(reader.Read<double>("RotX1",0.)),
    rot2 = 
    createMatrixFromZAngle(reader.Read<double>("RotZ1",0.))*
    createMatrixFromYAngle(reader.Read<double>("RotY1",0.))*
    createMatrixFromXAngle(reader.Read<double>("RotX1",0.));

  double
    thetaRotX1 = reader.Read<double>("ThetaRotX1",0.),
    thetaRotY1 = reader.Read<double>("ThetaRotY1",0.),
    thetaRotZ1 = reader.Read<double>("ThetaRotZ1",0.),
    thetaRotX2 = reader.Read<double>("ThetaRotX2",0.),
    thetaRotY2 = reader.Read<double>("ThetaRotY2",0.),
    thetaRotZ2 = reader.Read<double>("ThetaRotZ2",0.);

  double w = 0;
  vector<double> thetas, energies;
  for (double theta = thetaMin; theta <= thetaMax ; theta += dTheta)
    {
      thetas.push_back(theta);
      Matrix3d
	omega1 =
	createMatrixFromXAngle(thetaRotX1*theta).transpose() *
	createMatrixFromYAngle(thetaRotY1*theta).transpose() *
	createMatrixFromZAngle(thetaRotZ1*theta).transpose() *
	rot1,
	omega2 =
	createMatrixFromXAngle(thetaRotX2*theta).transpose() *
	createMatrixFromYAngle(thetaRotY2*theta).transpose() *
	createMatrixFromZAngle(thetaRotZ2*theta).transpose() *
	rot2;
      
      w = Wield::Integrator::Surface(C1,omega1,
				     C2,omega2,
				     epsilon, tolerance);
      energies.push_back(-w);
      out << theta << " " << -w << endl;
      WIELD_PROGRESS("Computing energy", theta-thetaMin, thetaMax-thetaMin, dTheta)
    }
  cout << endl;
  out.close();


  WIELD_EXCEPTION_CATCH;
}
}
}

#endif
