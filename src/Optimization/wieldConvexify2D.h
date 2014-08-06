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
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"

namespace Wield
{
namespace Optimization
{
///
/// \func Convexify2DAngles
/// \brief Compute the 2D geometric relaxation envelope
///
/// Compute 
/// \f[W_c(\mathbf{e}) =  \inf_{\mathbf{n}_1,\mathbf{n}_2,\mathbf{n}_3}\bigg(\lambda_1 W(\mathbf{n}_1) + \lambda_2 W(\mathbf{n}_2 + \lambda_3 W(\mathbf{n}_3)\bigg) \f]
/// subject to
/// \f[\lambda_1\mathbf{n}_1 + \lambda_2\mathbf{n}_2 + \lambda_2\mathbf{n}_2 = \mathbf{e}\f]
///
double
Convexify2DAngles(Vector3d e,       ///< Interface average normal vector
		  vector<double> X, ///< X coordinates of points
		  vector<double> Y, ///< Y coordinates of points
		  vector<double> Z) ///< Function values of points
{
  WIELD_EXCEPTION_TRY;
  if (X.size() != Y.size() || Y.size() != Z.size())
    WIELD_EXCEPTION_NEW("X, Y, Z not the same size");
  if (e.norm() < 1E-8)
    WIELD_EXCEPTION_NEW("Normal vector e too small");

  double W = *max_element(Z.begin(), Z.end());
  double Lambda1, Lambda2, Lambda3;
  Vector3d N1, N2, N3;

  Matrix3d n;
  for (int i =0; i < X.size(); i++) 
    {
      Vector3d n1(X[i], Y[i], sqrt(1 - X[i]*X[i] - Y[i]*Y[i]));
      n.col(0) = n1;
      for (int j =0; j < X.size(); j++) 
	{
	  Vector3d n2(X[j], Y[j], sqrt(1 - X[j]*X[j] - Y[j]*Y[j]));
	  n.col(1) = n2;
	  for (int k =0; k < X.size(); k++) 
	    {
	      Vector3d n3(X[k], Y[k], sqrt(1 - X[k]*X[k] - Y[k]*Y[k]));
	      n.col(2) = n2;

	      if (fabs(n.determinant()) < 1E-8) continue;

	      Vector3d lambda = n.FullPivLU().solve(e);

	      double w = lambda(0)*Z[i] + lambda(1)*Z[j] + lambda(2)*Z[k];
	      if (w < W)
		{
		  W = w;
		  Lambda1 = lambda(0); Lambda2 = lambda(1); Lambda3 = lambda(2);
		  N1      = n1;        N2      = n2;        N3      = n3;
		}
	    }
	}
    }

  // (j) -- (i) -- (k)
  // vector<double> Yc;
  // for (int i=0; i<X.size(); i++)  // With the simpler for loops, this has O(n^2) scaling
  //   {
  //     double inf = Y[i];
  //     T1[i] = X[i]; T2[i] = X[i];
  //     // for (int j=0; j<X.size(); j++)         // This for loop sequence gives an accurate
  //     // 	for (int k=0; k<X.size(); k++)  //    relaxation for *all* theta
  //     for (int j=0; j<i; j++)                   // But this one has O(n) scaling instead of
  // 	for (int k=i+1; k<X.size(); k++)        // O(n^2)!
  // 	  {
  // 	    if (j==k) continue;
  // 	    double theta1 = X[j]*pi/180, theta = X[i]*pi/180, theta2= X[k]*pi/180;
  // 	    double det = sin(theta1-theta2);
  // 	    double lambda1 = sin(theta - theta2)/det;
  // 	    double lambda2 = sin(theta1 - theta)/det;
  // 	    double w = fabs(lambda1)*Y[j] + fabs(lambda2)*Y[k];
  // 	    if (w < inf)
  // 	      {
  // 		T1[i] = X[j];
  // 		T2[i] = X[k];
  // 		inf = w;
  // 	      }
  // 	  }
  //     Yc.push_back(inf);
  //     WIELD_PROGRESS("Convexifying", i,X.size(),1);
  //   }
  // cout << endl;
  // return Yc;
  return Z;
  WIELD_EXCEPTION_CATCH;
}
}
}


#endif
