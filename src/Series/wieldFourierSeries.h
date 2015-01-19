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
///
/// \fn complex<double> ComputeFourierCoefficient(int n, double x0, double sigma, double alpha)
///
/// This function evaluates the following integral
/// \f[ \int_{-\alpha}^\alpha \exp\left(-\frac{(x-x_0)^2}{\sigma^2}\right)\exp\left(-i\frac{n\pi x}{\alpha}\right) dx\f]
/// where \f$n,x_0,\sigma,\alpha\f$ are given in the function arguments. The complex valued solution is
/// \f[\frac{\sqrt{\pi}\alpha}{2}
///         \left(
///           {{\rm erf}\left({\frac {2\,\alpha-2\, x_0+i\,n\,\pi \,\alpha}{2\alpha}}\right)}
///         - {{\rm erf}\left({\frac {-2\,\alpha-2\, x_0+i\,n\,\pi \,\alpha}{2\alpha}}\right)}
///         \right)
///         \exp\left(-\frac {n\,\pi\,\left( 4\,i x_0+n\,\pi \,\alpha \right) }{4\alpha}\right)  \f]
///
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
  
  FourierSeries(string inFileName)
  {
    /// Read in series data from a file
    if (!ifstream(inFileName.c_str()))
      WIELD_EXCEPTION_NEW("File " + inFileName + " does not exist");
    Reader::Reader reader(inFileName, "$", "#", "...");
    order = reader.Read<int>("order");
    alphaX = reader.Read<double>("alphaX");
    alphaY = reader.Read<double>("alphaY");
    alphaZ = reader.Read<double>("alphaZ"); 
    reader.Read("C", &C);
    if (C.size() != order*order*order)
      WIELD_EXCEPTION_NEW("Incorrect number of Fourier coefficients: C.size()="<<C.size());
  }

  FourierSeries(int _order, double _alphaX, double _alphaY, double _alphaZ,
		double sigma, vector<double> X, vector<double> Y, vector<double> Z):
    order(_order),alphaX(_alphaX),alphaY(_alphaY),alphaZ(_alphaZ)
  {
    C.resize((2*order - 1)*(2*order - 1)*(2*order - 1));

    if ((X.size() != Y.size()) || (Y.size() != Z.size()) || (Z.size() != X.size()))
      WIELD_EXCEPTION_NEW("Error: X, Y, Z vectors must be the same size");

    int size = X.size();
    for (int l=-order+1; l<order; l++)
      {
	for (int m=-order+1; m<order; m++)
	  for (int n=-order+1; n<order; n++)
	    {
	      (*this)(l,m,n) = 0;
	      for (unsigned int i=0; i<size; i++)
		{
		  (*this)(l,m,n) += 
		    Wield::Series::ComputeFourierCoefficient(l,X[i],sigma,alphaX)	*
		    Wield::Series::ComputeFourierCoefficient(m,Y[i],sigma,alphaY)	*
		    Wield::Series::ComputeFourierCoefficient(n,Z[i],sigma,alphaZ);
		}
	      (*this)(l,m,n) *= 1./(8. * alphaX * alphaY * alphaZ);
	      //if (l==0 && m==0 && n==0)
	      //  (*this)(l,m,n)=0;
	    }
	WIELD_PROGRESS("Fourier Coefficients:", l+order-1, 2*order-1, 1);
      }
    cout << endl;
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
private:
  vector<complex<double> > C;          ///< Matrix of complex Fourier coefficients
};



// class CosSeries
// {
// public:
//   CosSeries(CosSeries *old) :
//     order(old->order), alphaX(old->alphaX), alphaY(old->alphaY), alphaZ(old->alphaZ), C(old->C) {}
//   CosSeries(string cosSeriesFileName)
//   {
//     ReadFromFile(cosSeriesFileName);
//   }
//   CosSeries(Reader::Reader &reader, string structName)
//   {
//     if (reader.Find(structName,"InFile"))
//       {
// 	string infile = reader.Read<string>(structName,"InFile");
// 	ifstream testStream(infile.c_str());
// 	if (testStream)
// 	  {
// 	    ReadFromFile(infile);
// 	    return;
// 	  }
// 	else 
// 	  WIELD_WARNING("File " << infile << " does not exist. Attempting to compute.");
//       }
//     order            = reader.Read<int>(structName,"order");
//     alphaX           = reader.Read<double>(structName,"alphaX");
//     alphaY           = reader.Read<double>(structName,"alphaY");
//     alphaZ           = reader.Read<double>(structName,"alphaZ");

//     if (reader.Find(structName,"C"))
//       {
// 	reader.Read(structName,"C",&C);
// 	return;
//       }

//     double sigma     = reader.Read<double>(structName,"sigma");
//     vector<double> X = reader.Read<vector<double> >(structName,"X");
//     vector<double> Y = reader.Read<vector<double> >(structName,"Y");
//     vector<double> Z = reader.Read<vector<double> >(structName,"Z");


//     if ((X.size() != Y.size()) || (Y.size() != Z.size()) || (Z.size() != X.size()))
//       WIELD_EXCEPTION_NEW("Error: X, Y, Z vectors must be the same size");
//     int size = X.size();

//     C.resize(order*order*order);

//     for (unsigned int l=0; l<order; l++)
//       for (unsigned int m=0; m<order; m++)
// 	{
// 	  for (unsigned int n=0; n<order; n++)
// 	    {
// 	      (*this)(l,m,n) = 0;
// 	      for (unsigned int i=0; i<size; i++)
// 		{
// 		  (*this)(l,m,n) += 
// 		    ComputeGaussCosIntegral(l, X[i], sigma, alphaX)	*
// 		    ComputeGaussCosIntegral(m, Y[i], sigma, alphaY)	*
// 		    ComputeGaussCosIntegral(n, Z[i], sigma, alphaZ);

// 		}
// 	      if (l==0 && m==0 & n==0)
// 		(*this)(l,m,n)=0;
// 	      WIELD_PROGRESS("Computing Coefficients", order*order*l + order*m + n, order*order*order , 1);
// 	    }
// 	}
//     cout << endl;
    
//     if (reader.Find(structName,"OutFile"))
//       PrintToFile(reader.Read<string>(structName,"OutFile"));

//   }
//   double & operator() (unsigned int i, unsigned int j, unsigned int k)
//   {
//     return C[order*order*i + order*j + k];
//   }


//   void PrintToFile(string outFileName)
//   {
//     ofstream out(outFileName.c_str());
//     out << "$order " << order << endl;
//     out << scientific;
//     out << "$alphaX " << alphaX << endl;
//     out << "$alphaY " << alphaY << endl;
//     out << "$alphaZ " << alphaZ << endl;
//     out << "$C ";
//     for (unsigned int l=0; l<order; l++)
//       for (unsigned int m=0; m<order; m++)
// 	{
// 	  out << "..." << endl;
// 	  for (unsigned int n=0; n<order; n++)
// 	    {
// 	      out.width(16);
// 	      out << (*this)(l,m,n) << " ";
// 	    }
// 	}
//     out << endl;
//     out.close();
//   }

//   double EvaluateAt(double x, double y, double z)
//   {
//     WIELD_EXCEPTION_TRY;
//     double phi = 0;
//     for (int l=0; l<order; l++)
//       for (int m=0; m<order; m++)
// 	for (int n=0; n<order; n++)
// 	  phi += 
// 	    (*this)(l,m,n) *
// 	    cos(l*pi*x/alphaX) *
// 	    cos(m*pi*y/alphaY) *
// 	    cos(n*pi*z/alphaZ);
//     return phi;
//     WIELD_EXCEPTION_CATCH;
//   }


// };

}
}
#endif
