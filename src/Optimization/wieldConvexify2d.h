#ifndef WIELD_UTILS_OPTIMIZATION_CONVEXIFY2D_H
#define WIELD_UTILS_OPTIMIZATION_CONVEXIFY2D_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#undef eigen_assert
#define eigen_assert(A) if (!(A)) throw new std::runtime_error("Eigen threw an exception");
#include "Eigen/Core"
#include "Eigen/Geometry"


using namespace std;
using namespace Eigen;

#include "/home/brandon/Research/Reader/Reader.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldExceptions.h"

namespace Wield
{
namespace Optimization
{
vector<double>
Convexify2D(vector<double> X, vector<double> Y)
{
  WIELD_EXCEPTION_TRY;
  if (X.size() != Y.size())
    WIELD_EXCEPTION_NEW("X and Y not the same size");

  vector<double> Yc;
  for (int i=0; i<X.size(); i++)
    {
      double inf = Y[i];
      for (int j=0; j<i; j++)
	for (int k=i+1; k<X.size(); k++)
	  {
	    double lambda = (X[i] - X[j])/(X[k] - X[j]);
	    double w = (1-lambda)*Y[j] + lambda*Y[k];
	    if (w < inf) inf = w;
	  }
      Yc.push_back(inf);
    }
  return Yc;
  WIELD_EXCEPTION_CATCH;
}

vector<double>
Convexify2DAngles(vector<double> X, vector<double> Y)
{
  WIELD_EXCEPTION_TRY;
  if (X.size() != Y.size())
    WIELD_EXCEPTION_NEW("X and Y not the same size");
  
  // (j) -- (i) -- (k)

  vector<double> Yc;
  for (int i=0; i<X.size(); i++)
    {
      double inf = Y[i];
      for (int j=0; j<i; j++)
	for (int k=i+1; k<X.size(); k++)
	  {
	    double theta1 = X[j], theta2= X[k];
	    double det = cos(theta1)*sin(theta2) - sin(theta1)*cos(theta2);
	    double lambda1 = -cos(theta2)/det;
	    double lambda2 =  cos(theta1)/det;
	    cout << lambda1 << " " << lambda2 << endl;
	    //double lambda = (X[i] - X[j])/(X[k] - X[j]);
	    double w = lambda1*Y[j] + lambda2*Y[k];
	    if (w < inf) inf = w;
	  }
      Yc.push_back(inf);
    }
  return Yc;
  WIELD_EXCEPTION_CATCH;
}
}
}


#endif
