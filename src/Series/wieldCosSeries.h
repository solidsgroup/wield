#ifndef WIELD_SERIES_COSSERIES_H
#define WIELD_SERIES_COSSERIES_H

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
//#include "Utils/VTK/wieldVTK.h"
#include "Utils/wieldProgress.h"

#include "Faddeeva/Faddeeva.h"

// template<> struct Interpreter<Wield::Series::CosSeries>
// {
//   void operator() (const string varUnparsed, Wield::Series::CosSeries *varParsed)
//   {
//     std::istringstream iss(varUnparsed); 
//     string token;
//     int order = varParsed->order;
//     for (unsigned int i=0;i<order;i++)
//       for (unsigned int j=0;j<order;j++)
// 	for (unsigned int k=0;k<order;k++)
// 	  {
// 	    iss >> token;
// 	    (*varParsed)(i,j,k) = EvaluateMath(token);
// 	  }
//   }
// };


namespace Wield
{
namespace Series
{
double ComputeGaussCosIntegral(int n, double x0, double sigma, double alpha)
{
  complex<double> ret(0,0);
  complex<double> 
    firstErfArg (+x0/sigma, 0.5*sigma*n*pi/alpha), 
    secondErfArg(-x0/sigma, 0.5*sigma*n*pi/alpha), 
    thirdErfArg (+(x0-alpha)/sigma, 0.5*sigma*n*pi/alpha),
    fourthErfArg(-(x0-alpha)/sigma, 0.5*sigma*n*pi/alpha);
  complex<double>
    firstExpArg  (-0.25*n*n*pi*pi*sigma*sigma/(alpha*alpha),+x0*n*pi/alpha),
    secondExpArg (-0.25*n*n*pi*pi*sigma*sigma/(alpha*alpha),-x0*n*pi/alpha),
    thirdExpArg  = firstExpArg,
    fourthExpArg = secondExpArg;
  ret = 0.25 * sqrt(pi) * sigma *
    (+Faddeeva::erf(firstErfArg) *exp(firstExpArg)
     -Faddeeva::erf(secondErfArg)*exp(secondExpArg)
     -Faddeeva::erf(thirdErfArg) *exp(thirdExpArg)
     +Faddeeva::erf(fourthErfArg)*exp(fourthExpArg));
  if (fabs(ret.imag()/ret.real()) > 1E-10)
    WIELD_EXCEPTION_NEW("Fourier series integral returned imaginary part: ret="<<ret<<", n="<<n<<", x0="<<x0<<", alpha="<<alpha);
  if (n==0)
    return ret.real() / (alpha);
  else
    return ret.real() / (alpha/2.);
}

double ComputeGaussSinIntegral(int n, double x0, double sigma, double alpha)
{
  complex<double> ret(0,0);
  complex<double> I(0,1);
  complex<double>
    firstErfArg (+x0/sigma, 0.5*sigma*n*pi/alpha), //+
    secondErfArg(-x0/sigma,0.5*sigma*n*pi/alpha),//+
    thirdErfArg (+(x0-alpha)/sigma, 0.5*sigma*n*pi/alpha), //-
    fourthErfArg(-(x0-alpha)/sigma, 0.5*sigma*n*pi/alpha); //-
  complex<double>
    firstExpArg (-0.25*n*n*pi*pi*sigma*sigma/(alpha*alpha),+x0*n*pi/alpha),
    secondExpArg(-0.25*n*n*pi*pi*sigma*sigma/(alpha*alpha),-x0*n*pi/alpha),
    thirdExpArg  = firstExpArg,
    fourthExpArg = secondExpArg;
  ret = -0.25 * I * sqrt(pi) * sigma *
    (+ Faddeeva::erf(firstErfArg)*exp(firstExpArg)
     + Faddeeva::erf(secondErfArg)*exp(secondExpArg)
     - Faddeeva::erf(thirdErfArg)*exp(thirdExpArg)
     - Faddeeva::erf(fourthErfArg)*exp(fourthExpArg));
  if (fabs(ret.imag()/ret.real()) > 1E-10)
    WIELD_EXCEPTION_NEW("Fourier series integral returned imaginary part: ret="<<ret<<", n="<<n<<", x0="<<x0<<", alpha="<<alpha);
  if (n==0)
    return 0.;
  else
    return ret.real() / (alpha/2.);
}

class CosSeries
{
public:
  CosSeries(CosSeries *old) :
    order(old->order), alpha1(old->alpha1), alpha2(old->alpha2), alpha3(old->alpha3), C(old->C) {}
  CosSeries(string cosSeriesFileName)
  {
    ReadFromFile(cosSeriesFileName);
  }
  CosSeries(Reader::Reader &reader, string structName)
  {
    if (reader.Find(structName,"InFile"))
      {
	string infile = reader.Read<string>(structName,"InFile");
	ifstream testStream(infile.c_str());
	if (testStream)
	  {
	    ReadFromFile(infile);
	    return;
	  }
	else 
	  WIELD_WARNING("File " << infile << " does not exist. Attempting to compute.");
      }
    order            = reader.Read<int>(structName,"order");
    alpha1           = reader.Read<double>(structName,"alpha1");
    alpha2           = reader.Read<double>(structName,"alpha2");
    alpha3           = reader.Read<double>(structName,"alpha3");

    if (reader.Find(structName,"C"))
      {
	reader.Read(structName,"C",&C);
	return;
      }

    double sigma     = reader.Read<double>(structName,"sigma");
    vector<double> X = reader.Read<vector<double> >(structName,"X");
    vector<double> Y = reader.Read<vector<double> >(structName,"Y");
    vector<double> Z = reader.Read<vector<double> >(structName,"Z");


    if ((X.size() != Y.size()) || (Y.size() != Z.size()) || (Z.size() != X.size()))
      WIELD_EXCEPTION_NEW("Error: X, Y, Z vectors must be the same size");
    int size = X.size();

    C.resize(order*order*order);

    for (unsigned int l=0; l<order; l++)
      for (unsigned int m=0; m<order; m++)
	{
	  for (unsigned int n=0; n<order; n++)
	    {
	      (*this)(l,m,n) = 0;
	      for (unsigned int i=0; i<size; i++)
		{
		  (*this)(l,m,n) += 
		    ComputeGaussCosIntegral(l, X[i], sigma, alpha1)	*
		    ComputeGaussCosIntegral(m, Y[i], sigma, alpha2)	*
		    ComputeGaussCosIntegral(n, Z[i], sigma, alpha3);

		}
	      if (l==0 && m==0 & n==0)
		(*this)(l,m,n)=0;
	      WIELD_PROGRESS("Computing Coefficients", order*order*l + order*m + n, order*order*order , 1);
	    }
	}
    cout << endl;
    
    if (reader.Find(structName,"OutFile"))
      PrintToFile(reader.Read<string>(structName,"OutFile"));

  }
  double & operator() (unsigned int i, unsigned int j, unsigned int k)
  {
    return C[order*order*i + order*j + k];
  }

  void ReadFromFile(string inFileName)
  {
    Reader::Reader reader(inFileName, "$", "#", "...");
    order = reader.Read<int>("order");
    reader.Read("C", &C);
    if (C.size() != order*order*order)
      WIELD_EXCEPTION_NEW("Incorrect number of Fourier coefficients: C.size()="<<C.size());
    alpha1 = reader.Read<double>("alpha1");
    alpha2 = reader.Read<double>("alpha2");
    alpha3 = reader.Read<double>("alpha3"); 
  }

  void PrintToFile(string outFileName)
  {
    ofstream out(outFileName.c_str());
    out << "$order " << order << endl;
    out << scientific;
    out << "$alpha1 " << alpha1 << endl;
    out << "$alpha2 " << alpha2 << endl;
    out << "$alpha3 " << alpha3 << endl;
    out << "$C ";
    for (unsigned int l=0; l<order; l++)
      for (unsigned int m=0; m<order; m++)
	{
	  out << "..." << endl;
	  for (unsigned int n=0; n<order; n++)
	    {
	      out.width(16);
	      out << (*this)(l,m,n) << " ";
	    }
	}
    out << endl;
    out.close();
  }

  double EvaluateAt(double x, double y, double z)
  {
    WIELD_EXCEPTION_TRY;
    double phi = 0;
    for (int l=0; l<order; l++)
      for (int m=0; m<order; m++)
	for (int n=0; n<order; n++)
	  phi += 
	    (*this)(l,m,n) *
	    cos(l*pi*x/alpha1) *
	    cos(m*pi*y/alpha2) *
	    cos(n*pi*z/alpha3);
    return phi;
    WIELD_EXCEPTION_CATCH;
  }


  unsigned int order; ///< Number of terms in each direction
  double alpha1;      ///< X Lattice coefficient
  double alpha2;      ///< Y Lattice coefficient
  double alpha3;      ///< Z Lattice coefficient
private:
  vector<double> C;          ///< Matrix of Fourier coefficients
};

}
}

#endif
