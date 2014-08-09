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
Convexify1DAngles(vector<double> X, vector<double> Y,bool full=false)
{
  WIELD_EXCEPTION_TRY;
  if (X.size() != Y.size())
    WIELD_EXCEPTION_NEW("X and Y not the same size");
  
  vector<double> Yc;
  for (int i=0; i<X.size(); i++)  // With the simpler for loops, this has O(n^2) scaling
    {
      double inf = Y[i];
      
      int jmin, jmax, kmin, kmax;

      // These for loop parameters gives an accurate
      // relaxation for *all* theta
      if (full)
	{jmin = 0; jmax = X.size(); kmin = 0; kmax = X.size();}
      // But this one has O(n) scaling instead of O(n^2)
      else
	{jmin = 0; jmax = i; kmin = i+1; kmax = X.size();}

      for (int j=jmin; j<jmax; j++)                   
	for (int k=kmin; k<kmax; k++)        
	  {
	    if (j==k) continue;
	    double theta1 = X[j]*pi/180, theta = X[i]*pi/180, theta2= X[k]*pi/180;
	    double det = sin(theta1-theta2);
	    double lambda1 = sin(theta - theta2)/det;
	    double lambda2 = sin(theta1 - theta)/det;
	    double w = fabs(lambda1)*Y[j] + fabs(lambda2)*Y[k];
	    if (w < inf)
	      inf = w;
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
