#ifndef WIELD_SERIES_FOURIERSERIES_H
#define WIELD_SERIES_FOURIERSERIES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "Reader.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"
#include "Utils/wieldWarnings.h"
#include "Utils/wieldProgress.h"

namespace Wield
{
namespace Series
{

template<class Mollifier>
class FourierSeries
{
public:  
  
  // convolution function: exp(||x||^2 / sigma^2) / (sigma sqrt(pi))^3
  // FS function: exp(- sigma^2||k||^2 / 4) / (2 pi)^{3/2}
  // inline double WHat(double x, double y, double z)
  // {
  //   return exp(-sigma*sigma*(x*x + y*y + z*z)/4.) / sqrt(8*pi*pi*pi);
  // }

  FourierSeries(int _order, 
		double _alphaX, 
		double _alphaY, 
		double _alphaZ,
		//double _sigma, 
		Mollifier _mollifier,
		std::vector<double> X, 
		std::vector<double> Y, 
		std::vector<double> Z):
    order(_order),
    alphaX(_alphaX),
    alphaY(_alphaY),
    alphaZ(_alphaZ),
    //sigma(_sigma)
    phiHat(_mollifier)
  {
    C.resize((2*order - 1)*(2*order - 1)*(2*order - 1));

    if ((X.size() != Y.size()) || (Y.size() != Z.size()) || (Z.size() != X.size()))
      WIELD_EXCEPTION_NEW("Error: X, Y, Z vectors must be the same size");

    std::complex<double> I(0,1);
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

		Eigen::Covector3d k(2.*pi*(double)l/alphaX, 2.*pi*(double)m/alphaY, 2.*pi*(double)n/alphaZ);
		Eigen::Vector3d x(X[i],Y[i],Z[i]);

		(*this)(l,m,n) +=
		  lambda
		  * phiHat(k)
		  * exp(-I * (double)(k*x))
		  / (alphaX * alphaY * alphaZ);
	      }
	  }
  }

  std::complex<double> & operator() (signed int i, signed int j, signed int k)
  {
    return C[(2*order-1)*(2*order-1)*(order + i - 1) + (2*order-1)*(order + j - 1) + (order + k - 1)];
  }      

  std::complex<double> operator() (double X, double Y, double Z)
  {
    Eigen::Vector3d x(X,Y,Z);
    std::complex<double> I(0,1), val(0,0);
    for (int l=-order+1; l<order; l++)
      for (int m=-order+1; m<order; m++)
      	for (int n=-order+1; n<order; n++)
	  {
	    Eigen::Covector3d k(2.*pi*(double)l / alphaX, 2.*pi*(double)m / alphaY, 2.*pi*(double)n / alphaZ); 
	    val += (*this)(l,m,n) * exp(I * (double)(k*x));
	  }
    return val;
  }      

  // Variables
  int order;      ///< Number of terms in each direction (times 2 + 1) \details
  double alphaX;  ///< \brief X Lattice coefficient
  double alphaY;  ///< \brief Y Lattice coefficient
  double alphaZ;  ///< \brief Z Lattice coefficient
  double sigma;
private:
  std::vector<std::complex<double> > C;          ///< Matrix of complex Fourier coefficients
  Mollifier phiHat;
};



}
}
#endif
