#ifndef WIELD_SERIES_FOURIERSERIES_H
#define WIELD_SERIES_FOURIERSERIES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

#include "Reader.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"
#include "Utils/wieldWarnings.h"
#include "Utils/wieldProgress.h"

#include "Faddeeva/Faddeeva.h"

namespace Wield
{
namespace Series
{

complex<double> ComputeFourierCoefficient(int n, double x0, double sigma, double alpha)
{
  complex<double> I(0,1);
  return
    0.5*sqrt(pi)*sigma*
    (
     Faddeeva::erf((- 2*(alpha/2.)*(alpha/2.) - 2*(alpha/2.)*x0 + I*(double)n*pi*sigma*sigma)/(2*sigma*(alpha/2.))) -
     Faddeeva::erf((+ 2*(alpha/2.)*(alpha/2.) - 2*(alpha/2.)*x0 + I*(double)n*pi*sigma*sigma)/(2*sigma*(alpha/2.)))
     )
    * exp( - (double)n*pi*(4.*I*(alpha/2.)*x0 + (double)n*pi*sigma*sigma) / (4*(alpha/2.)*(alpha/2.)));
}

class FourierSeries
{
public:  
  
  // convolution function: exp(||x||^2 / sigma^2) / (sigma sqrt(pi))^3
  // FS function: exp(- sigma^2||k||^2 / 4) / (2 pi)^{3/2}
  inline double WHat(double x, double y, double z)
  {
    return exp(-sigma*sigma*(x*x + y*y + z*z)/4.) / sqrt(8*pi*pi*pi);
  }

  FourierSeries(int _order, double _alphaX, double _alphaY, double _alphaZ,
		double _sigma, vector<double> X, vector<double> Y, vector<double> Z):
    order(_order),alphaX(_alphaX),alphaY(_alphaY),alphaZ(_alphaZ),sigma(_sigma)
  {
    C.resize((2*order - 1)*(2*order - 1)*(2*order - 1));

    if ((X.size() != Y.size()) || (Y.size() != Z.size()) || (Z.size() != X.size()))
      WIELD_EXCEPTION_NEW("Error: X, Y, Z vectors must be the same size");

    complex<double> I(0,1);
    int size = X.size();
    for (int l=-order+1; l<order; l++)
      for (int m=-order+1; m<order; m++)
	for (int n=-order+1; n<order; n++)
	  {
	    (*this)(l,m,n) = 0;
	    for (unsigned int i=0; i<size; i++)
	      {
		if (fabs(X[i]) > 0.5*alphaX) WIELD_WARNING("X[i] = " << X[i] << " > 0.5*alphaX= " << 0.5*alphaX );
 		if (fabs(Y[i]) > 0.5*alphaY) WIELD_WARNING("Y[i] = " << Y[i] << " > 0.5*alphaY= " << 0.5*alphaY );
		if (fabs(Z[i]) > 0.5*alphaZ) WIELD_WARNING("Z[i] = " << Z[i] << " > 0.5*alphaZ= " << 0.5*alphaZ );

		double lambda = 1.;
		if (fabs(fabs(X[i]) - 0.5*alphaX) < 1E-8) lambda *= 0.5;
		if (fabs(fabs(Y[i]) - 0.5*alphaY) < 1E-8) lambda *= 0.5;
		if (fabs(fabs(Z[i]) - 0.5*alphaZ) < 1E-8) lambda *= 0.5;

		(*this)(l,m,n) +=
		  lambda
		  * WHat(2.*pi*(double)l/alphaX, 2.*pi*(double)m/alphaY, 2.*pi*(double)n/alphaZ)
		  * exp(-I * (2.*pi*(double)l*X[i]/alphaX + 2.*pi*(double)m*Y[i]/alphaY + 2.*pi*(double)n*Z[i]/alphaZ))
		  / (8. * pi * pi * pi * alphaX * alphaY * alphaZ);
	      }
	    //cout << "(" << l << "," << m << "," << n << ") " << (*this)(l,m,n) << endl;
	  }
    //    cout << endl;
  }

  complex<double> & operator() (signed int i, signed int j, signed int k)
  {
    return C[(2*order-1)*(2*order-1)*(order + i - 1) + (2*order-1)*(order + j - 1) + (order + k - 1)];
  }      

  complex<double> operator() (double x, double y, double z)
  {
    complex<double> I(0,1), val(0,0);
    for (int l=-order+1; l<order; l++)
      for (int m=-order+1; m<order; m++)
      	for (int n=-order+1; n<order; n++)
	  val += (*this)(l,m,n) * exp(I * 2. * pi * (l*x/alphaX + m*y/alphaY + n*z/alphaZ));
    return val;
  }      

  // Variables
  int order;      ///< Number of terms in each direction (times 2 + 1) \details
  double alphaX;  ///< \brief X Lattice coefficient
  double alphaY;  ///< \brief Y Lattice coefficient
  double alphaZ;  ///< \brief Z Lattice coefficient
  double sigma;
private:
  vector<complex<double> > C;          ///< Matrix of complex Fourier coefficients
};



}
}
#endif
