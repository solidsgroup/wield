#ifndef WIELD_OPTIMIZATION_CONVEXIFY1D_H
#define WIELD_OPTIMIZATION_CONVEXIFY1D_H
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
vector<double>
Convexify1D(vector<double> X, vector<double> Y)
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
Convexify1DAngles(vector<double> X, vector<double> Y, vector<double> &T1, vector<double> &T2)
{
  WIELD_EXCEPTION_TRY;
  if (X.size() != Y.size())
    WIELD_EXCEPTION_NEW("X and Y not the same size");
  
  // (j) -- (i) -- (k)

  vector<double> Yc;
  for (int i=0; i<X.size(); i++)  // With the simpler for loops, this has O(n^2) scaling
    {
      double inf = Y[i];
      T1[i] = X[i]; T2[i] = X[i];
      // for (int j=0; j<X.size(); j++)         // This for loop sequence gives an accurate
      // 	for (int k=0; k<X.size(); k++)  //    relaxation for *all* theta
      for (int j=0; j<i; j++)                   // But this one has O(n) scaling instead of
	for (int k=i+1; k<X.size(); k++)        // O(n^2)!
	  {
	    if (j==k) continue;
	    double theta1 = X[j]*pi/180, theta = X[i]*pi/180, theta2= X[k]*pi/180;
	    double det = sin(theta1-theta2);
	    double lambda1 = sin(theta - theta2)/det;
	    double lambda2 = sin(theta1 - theta)/det;
	    double w = fabs(lambda1)*Y[j] + fabs(lambda2)*Y[k];
	    if (w < inf)
	      {
		T1[i] = X[j];
		T2[i] = X[k];
		inf = w;
	      }
	  }
      Yc.push_back(inf);
      WIELD_PROGRESS("Convexifying", i,X.size(),1);
    }
  cout << endl;
  return Yc;
  WIELD_EXCEPTION_CATCH;
}
}
}


#endif
