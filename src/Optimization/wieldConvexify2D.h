///
/// \file wieldConvexify2D.h
/// \brief Compute the 2D geometric relaxation envelope
///
///
#ifndef WIELD_OPTIMIZATION_CONVEXIFY2D_H
#define WIELD_OPTIMIZATION_CONVEXIFY2D_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>


using namespace std;

#include "Reader.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"

bool ThetaInRange(double theta, double theta1, double theta2)
{
  // Get all of the angles in the range [0,360)
  while (theta < 0) theta += 360.;
  while (theta1 < 0) theta1 += 360.;
  while (theta2 < 0) theta2 += 360.;

  theta  = fmod(theta,360.);
  theta1 = fmod(theta1,360.);
  theta2 = fmod(theta2,360.);

  double thetaMin, thetaMax;
  if (theta2>theta1) {thetaMin = theta1; thetaMax = theta2;}
  else {thetaMin = theta2; thetaMax = theta1;}

  if (fmod((thetaMax-thetaMin),360) < 180)
    if (theta < thetaMax && theta > thetaMin) return true;
    else return false;
  else
    if (theta < thetaMax && theta > thetaMin) return false;
    else return true;
}

namespace Wield
{
namespace Optimization
{


template<int facetOrder>
double Convexify2D(//Vector3d e,       ///< Interface average normal vector
		   vector<double> x, ///< X component of normal
		   vector<double> y, ///< Y component of normal
		   vector<double> z, ///< Z component of normal
		   vector<double> w); ///< Function values of points

///
/// \func Convexify2D
/// \brief Compute the 2D geometric relaxation envelope
///
/// Compute 
/// \f[W_c(\mathbf{e}) =  \inf_{\mathbf{n}_1,\mathbf{n}_2,\mathbf{n}_3}\bigg(\lambda_1 W(\mathbf{n}_1) + \lambda_2 W(\mathbf{n}_2 + \lambda_3 W(\mathbf{n}_3)\bigg) \f]
/// subject to
/// \f[\lambda_1\mathbf{n}_1 + \lambda_2\mathbf{n}_2 + \lambda_2\mathbf{n}_2 = \mathbf{e}\f]
///
template<>
double Convexify2D<3>(//Vector3d e,       ///< Interface average normal vector
		      vector<double> x, ///< X component of normal
		      vector<double> y, ///< Y component of normal
		      vector<double> z, ///< Z component of normal
		      vector<double> w) ///< Function values of points
{
  WIELD_EXCEPTION_TRY;
  if (x.size() != y.size() || y.size() != z.size() || z.size() != w.size())
    WIELD_EXCEPTION_NEW("x, y, z, W not the same size");
  // if (e.norm() < 1E-8)
  //   WIELD_EXCEPTION_NEW("Normal vector e too small");

  // srand(time(NULL));
  // for (int i=0; i<100; i++)
  //   {
  //     double theta1 = (2.*(double)rand()/(double)RAND_MAX - 1.)*360.;
  //     double theta2 = (2.*(double)rand()/(double)RAND_MAX - 1.)*360.;
  //     double theta  = (2.*(double)rand()/(double)RAND_MAX - 1.)*360.;
  //     cout << theta1 << ", " << theta2 << ", " << theta << endl;
  //     if (ThetaInRange(theta,theta1,theta2))
  // 	cout << "====> in range" << endl << endl;
  //     else cout << "====> not in range" << endl << endl;
  //   }
  // exit(0);


  Vector3d e; e << 0, 0, 1; 

  vector<double> r(x.size()), theta(x.size());
  for (int i=0; i<x.size(); i++)
    {
      r[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
      theta[i] = fmod(atan2(y[i],x[i])*180./pi,360); // get the range to be [0,360)
    }

  double wMin = *max_element(w.begin(), w.end());
  Vector3d lambdaMin;
  Vector3d n1Min, n2Min, n3Min;

  Matrix3d n;
  for (int i =0; i < x.size(); i++) 
    {
      Vector3d n1(x[i], y[i], z[i]);
      n.col(0) = n1;
      for (int j =i+1; j < x.size(); j++) 
	{
	  Vector3d n2(x[j], y[j], z[j]);
	  n.col(1) = n2;
	  for (int k = j+1; k < x.size(); k++) 
	    {
	      //cout << "A: " << theta[k] << " " << theta[i]+180 << " " << theta[j]+180 << endl;
	      if (!ThetaInRange(theta[k],theta[i]+180,theta[j]+180)) continue;
	      //cout << "B" << endl;
	      Vector3d n3(x[k], y[k], z[k]);
	      n.col(2) = n3;

	      //cout << n << endl << endl;
	      if (fabs(n.determinant()) < 1E-8) continue;

	      Vector3d lambda = n.fullPivLu().solve(e);


	      // cout << (n*lambda).transpose() << endl;
	      // cout << "lambda=" << lambda << endl;

	      if (lambda[0] < 0 || lambda[1] < 0 || lambda[2] < 0) continue;


	      double wCurrent = lambda(0)*w[i] + lambda(1)*w[j] + lambda(2)*w[k];
	      //cout << "wcurrent=" << wCurrent << endl;


	      if (wCurrent < wMin)
		{
		  wMin = wCurrent;
		  lambdaMin = lambda;
		  n1Min = n1;
		  n2Min = n2;
		  n3Min = n3;
		  cout << endl;
		  cout << WIELD_COLOR_FG_YELLOW << wMin << WIELD_COLOR_RESET << endl;
		  cout << WIELD_COLOR_FG_RED << lambdaMin.transpose() << WIELD_COLOR_RESET << endl;
		  cout << WIELD_COLOR_FG_BLUE << n << WIELD_COLOR_RESET << endl;

		}
	    }
	}
      WIELD_PROGRESS("Faceting", i, x.size(), 1); 
    }
  //cout << endl;

  cout << wMin << endl;
  cout << lambdaMin.transpose() << endl;
  cout << n1Min.transpose() << endl;
  cout << n2Min.transpose() << endl;
  cout << n3Min.transpose() << endl;

  return wMin;
  WIELD_EXCEPTION_CATCH;
}
}
}


#endif
