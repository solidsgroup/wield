///
/// \file wieldConvexify2D.h
/// \brief Compute the 2D geometric relaxation envelope
///
/// Compute 
/// \f[W_c(\mathbf{e}) =  \inf_{\mathbf{n}_1,\mathbf{n}_2,\mathbf{n}_3}\bigg(\lambda_1 W(\mathbf{n}_1) + \lambda_2 W(\mathbf{n}_2 + \lambda_3 W(\mathbf{n}_3)\bigg) \f]
/// subject to
/// \f[\lambda_1\mathbf{n}_1 + \lambda_2\mathbf{n}_2 + \lambda_2\mathbf{n}_2 = \mathbf{e}\f]
///
#ifndef WIELD_OPTIMIZATION_CONVEXIFY2D_H
#define WIELD_OPTIMIZATION_CONVEXIFY2D_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <pthread.h>

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

bool PolarOpposites(double theta1, double theta2)
{
  while (theta1>=0) theta1 -= 360;
  while (theta2>=0) theta2 -= 360;
  while (theta1 < 0) theta1 += 360.;
  while (theta2 < 0) theta2 += 360.;

  if (fabs(180-fabs(theta2-theta1)) < 1E-8) return true;
  else return false;
}

namespace Wield
{
namespace Optimization
{
template<int facetOrder>
struct ConvexifyData2D;

template<>
struct ConvexifyData2D<3>
{
  int index;
  int numThreads;
  int maxFacetOrder;
  vector<double> *x;
  vector<double> *y;
  vector<double> *z;
  vector<double> *r;
  vector<double> *theta;
  vector<double> *w;
  double wMin;
  Eigen::Vector3d lambdaMin;
  Eigen::Vector3d n1Min;
  Eigen::Vector3d n2Min;
  Eigen::Vector3d n3Min;
};


template<int facetOrder>
void *Convexify2D(void *args);

template<>
void *Convexify2D<3>(void *args) 
{
  WIELD_EXCEPTION_TRY;

  int index                  =   ((ConvexifyData2D<3> *)(args))->index;
  int numThreads             =   ((ConvexifyData2D<3> *)(args))->numThreads;
  int maxFacetOrder          =   ((ConvexifyData2D<3> *)(args))->maxFacetOrder;
  vector<double> &x          = *(((ConvexifyData2D<3> *)(args))->x);
  vector<double> &y          = *(((ConvexifyData2D<3> *)(args))->y);
  vector<double> &z          = *(((ConvexifyData2D<3> *)(args))->z);
  vector<double> &r          = *(((ConvexifyData2D<3> *)(args))->r);
  vector<double> &theta      = *(((ConvexifyData2D<3> *)(args))->theta);
  vector<double> &w          = *(((ConvexifyData2D<3> *)(args))->w);
  double &wMin               =   ((ConvexifyData2D<3> *)(args))->wMin;
  Eigen::Vector3d &lambdaMin =   ((ConvexifyData2D<3> *)(args))->lambdaMin;
  Eigen::Vector3d &n1Min     =   ((ConvexifyData2D<3> *)(args))->n1Min;
  Eigen::Vector3d &n2Min     =   ((ConvexifyData2D<3> *)(args))->n2Min;
  Eigen::Vector3d &n3Min     =   ((ConvexifyData2D<3> *)(args))->n3Min;


  if (x.size() != y.size() || y.size() != z.size() || z.size() != w.size())
    WIELD_EXCEPTION_NEW("x, y, z, w not the same size: x.size()=" <<x.size() << ", y.size()="<<y.size() << ", z.size()="<<z.size()<<", w.size() =" << w.size());

  Eigen::Vector3d e; e << 0, 0, 1; 

  wMin = *max_element(w.begin(), w.end());
  // Vector3d lambdaMin;
  // Vector3d n1Min, n2Min, n3Min;

  Matrix3d n;
  for (int i =0; i < x.size(); i++) 
    {
      if ( i%numThreads != index ) continue;
      
      Eigen::Vector3d n1(x[i], y[i], z[i]);
      n.col(0) = n1;
      for (int j =i+1; j < x.size(); j++) 
	{
	  Eigen::Vector3d n2(x[j], y[j], z[j]);
	  n.col(1) = n2;
	  
	  if (PolarOpposites(theta[i],theta[j]))
	    {
	      double theta1 = asin(r[i]); double theta2 = -asin(r[j]);
	      double det = sin(theta1-theta2);
	      if (fabs(det)<1E-5) continue;
	      double lambda1 = -sin(theta2)/det;
	      double lambda2 = sin(theta1)/det;
	      double wCurrent = fabs(lambda1)*w[i] + fabs(lambda2)*w[j];
	      if (wCurrent < wMin)
		{
		  wMin = wCurrent;
		  lambdaMin << lambda1, lambda2, 0;
		  n1Min = n1;
		  n2Min = n2;
		  n3Min << 0,0,0;
		}
	    }
	  else if (maxFacetOrder >= 3)
	    {
	      for (int k = j+1; k < x.size(); k++) 
		{
		  if (!ThetaInRange(theta[k],theta[i]+180,theta[j]+180)) continue;
		  if (PolarOpposites(theta[i],theta[k]) || PolarOpposites(theta[j],theta[k])) continue; // 2d faceting, will get caught later
		  Eigen::Vector3d n3(x[k], y[k], z[k]);
		  n.col(2) = n3;

		  if (fabs(n.determinant()) < 1E-8) continue;

		  Eigen::Vector3d lambda = n.fullPivLu().solve(e);


		  if (lambda[0] < 0 || lambda[1] < 0 || lambda[2] < 0) continue;


		  double wCurrent = lambda(0)*w[i] + lambda(1)*w[j] + lambda(2)*w[k];

		  if (wCurrent < wMin)
		    {
		      wMin = wCurrent;
		      lambdaMin = lambda;
		      n1Min = n1;
		      n2Min = n2;
		      n3Min = n3;
		    }
		}
	    }
	}
      if (index == 0) WIELD_PROGRESS("Faceting", i, x.size(), 1);
    }
  if (index == 0) cout << endl;

  pthread_exit(args);
  return NULL;
  WIELD_EXCEPTION_CATCH;
}
}
}


#endif
