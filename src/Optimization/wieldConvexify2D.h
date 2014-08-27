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

static inline
bool ThetaInRange(double theta, double theta1, double theta2)
{
  WIELD_EXCEPTION_TRY;
  if (theta  < 0 || theta  >= 360.) WIELD_EXCEPTION_NEW("Invalid theta  = " << theta);
  if (theta1 < 0 || theta1 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta1 = " << theta1);
  if (theta2 < 0 || theta2 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta2 = " << theta2);
 
  //cout << "theta1=" << theta1 << "\ttheta2=" << theta2 << "\ttheta=" << theta << endl;
  if (theta1 > 180) theta1 -= 180.;
  else theta1 += 180.;
  if (theta2 > 180) theta2 -= 180.;
  else theta2 += 180.;

  //cout << "theta1=" << theta1 << "\ttheta2=" << theta2 << "\ttheta=" << theta << endl;
  if (fabs(theta2-theta1) < 180)
    {
      
      if (theta2 >= theta && theta >= theta1) return true;//{cout << " ---> yes" << endl; return true;}
      if (theta1 >= theta && theta >= theta2) return true;//{cout << " ---> yes" << endl; return true;}
    }
  else
    {
      if (theta < theta1 && theta < theta2) return true;//{cout << " ---> yes" << endl; return true;}
      if (theta > theta1 && theta > theta2) return true;//{cout << " ---> yes" << endl; return true;}
    }
  //cout << " ---> no" << endl;
  return false;
  WIELD_EXCEPTION_CATCH;
}

static inline
bool PolarOpposites(double theta1, double theta2)
{
  WIELD_EXCEPTION_TRY;
  if (theta1 < 0 || theta1 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta1 = " << theta1);
  if (theta2 < 0 || theta2 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta2 = " << theta2);

  if (fabs(180-fabs(theta2-theta1)) < 1E-8) return true;
  else return false;
  WIELD_EXCEPTION_CATCH;
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

  //wMin = INFINITY;
  // Vector3d lambdaMin;
  // Vector3d n1Min, n2Min, n3Min;
  Vector3d lambda;
  Matrix3d n;
  for (int i =0; i < x.size(); i++) 
    {
      if ( i%numThreads != index ) continue;
      
      Eigen::Vector3d n1(x[i], y[i], z[i]);
      n.col(0) = n1;

      if (fabs(r[i])<1E-5)
	if (w[i] < wMin)
	  {
	    wMin = w[i];
	    lambdaMin << 1, 0, 0;
	    n1Min = n1;
	    n2Min << 0,0,0;
	    n3Min << 0,0,0;

	    if (index==0)
	      {
		cout << endl << WIELD_COLOR_B_ON << "Facet 1" << WIELD_COLOR_RESET << endl;
		cout << WIELD_COLOR_FG_YELLOW << wMin << WIELD_COLOR_RESET << endl;
		cout << WIELD_COLOR_FG_RED << lambdaMin.transpose() << WIELD_COLOR_RESET << endl;
		cout << WIELD_COLOR_FG_BLUE << n << WIELD_COLOR_RESET << endl;
	      }

	    continue;
	  }

      for (int j =i+1; j < x.size(); j++) 
	{
	  if (r[j] < 1E-8) continue;

	  Eigen::Vector3d n2(x[j], y[j], z[j]);
	  n.col(1) = n2;
	  
	  if (PolarOpposites(theta[i],theta[j]))
	    {
	      if (w[i] > wMin && w[j] > wMin) continue;
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

		  if (index==0)
		    {
		      cout << endl << WIELD_COLOR_B_ON << "Facet 2" << WIELD_COLOR_RESET << endl;
		      cout << WIELD_COLOR_FG_YELLOW << wMin << WIELD_COLOR_RESET << endl;
		      cout << WIELD_COLOR_FG_RED << lambdaMin.transpose() << WIELD_COLOR_RESET << endl;
		      cout << WIELD_COLOR_FG_BLUE << n << WIELD_COLOR_RESET << endl;
		    }

		  continue;
		}
	    }
	  else if (maxFacetOrder >= 3)
	    {
	      for (int k = j+1; k < x.size(); k++) 
		{
		  //if (!ThetaInRange(theta[k],theta[i]+180,theta[j]+180)) continue;
		  if (r[k] < 1E-8) continue;
		  if (!ThetaInRange(theta[k],theta[i],theta[j])) continue;
		  if (PolarOpposites(theta[i],theta[k]) || PolarOpposites(theta[j],theta[k])) continue; // 2d faceting, will get caught later
		  if (w[i]>wMin && w[j]>wMin && w[k]>wMin) continue;


		  Eigen::Vector3d n3(x[k], y[k], z[k]);
		  
		  n.col(2) = n3;

		  double det = 
		    + n(0,0)*n(1,1)*n(2,2) 
		    + n(0,1)*n(1,2)*n(2,0)
		    + n(0,2)*n(1,0)*n(2,1)
		    - n(0,0)*n(1,2)*n(2,1)
		    - n(0,1)*n(1,0)*n(2,2)
		    - n(0,2)*n(1,1)*n(2,0);
		  if (fabs(det)<1E-8) continue;

		  double lambda1 =
		    (+ e(0)  *n(1,1)*n(2,2) 
		     + n(0,1)*n(1,2)*e(2)
		     + n(0,2)*e(1)  *n(2,1)
		     - e(0)  *n(1,2)*n(2,1)
		     - n(0,1)*e(1)  *n(2,2)
		     - n(0,2)*n(1,1)*e(2)  )/det;
		  if (lambda1<0) continue;

		  double lambda2 = 
		    (+ n(0,0)*e(1)  *n(2,2) 
		     + e(0)  *n(1,2)*n(2,0)
		     + n(0,2)*n(1,0)*e(2)
		     - n(0,0)*n(1,2)*e(2)
		     - e(0)  *n(1,0)*n(2,2)
		     - n(0,2)*e(1)  *n(2,0))/det;
		  if (lambda2<0) continue;

		  double lambda3 = 
		    (+ n(0,0)*n(1,1)*e(2) 
		     + n(0,1)*e(1)  *n(2,0)
		     + e(0)  *n(1,0)*n(2,1)
		     - n(0,0)*e(1)  *n(2,1)
		     - n(0,1)*n(1,0)*e(2)
		     - e(0)  *n(1,1)*n(2,0))/det;
		  if (lambda3<0) continue;


		  lambda << lambda1 , lambda2 , lambda3;
		  if ((n*lambda - e).norm() > 1E-8)
		    WIELD_EXCEPTION_NEW("Linear solve did not work: (n*lambda - e).norm() = " << (n*lambda - e).norm() << endl
					<< "lambda = " << lambda.transpose() << endl
					<< "N = " << endl << n.transpose() << endl
					<< "e = " << e.transpose() << endl)

		  //Eigen::Vector3d lambda(lambda1,lambda2,lambda3);

		  // if ((lambda1*n1 + lambda2*n2 + lambda3*n3 - e).norm() > 1E-5)
		  //   cout << "Error in matrix solve" << endl;

		  //if (lambda[0] < 0 || lambda[1] < 0 || lambda[2] < 0) continue;


		  double wCurrent = lambda1*w[i] + lambda1*w[j] + lambda2*w[k];

		  if (wCurrent < wMin)
		    {
		      wMin = wCurrent;
		      lambdaMin << lambda1,lambda2,lambda3;
		      n1Min = n1;
		      n2Min = n2;
		      n3Min = n3;

		      if (index==0)
			{
			  cout << endl << WIELD_COLOR_B_ON << "Facet 3" << WIELD_COLOR_RESET << endl;
			  cout << WIELD_COLOR_FG_YELLOW << wMin << WIELD_COLOR_RESET << endl;
			  cout << WIELD_COLOR_FG_RED << lambdaMin.transpose() << WIELD_COLOR_RESET << endl;
			  cout << WIELD_COLOR_FG_BLUE << n << WIELD_COLOR_RESET << endl;
			}

		      continue;
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
