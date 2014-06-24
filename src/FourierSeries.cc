

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#define eigen_assert(A) if (!(A)) throw new std::runtime_error("Eigen threw an exception");
#include "Eigen/Core"
#include "Eigen/Geometry"
#include "Faddeeva/Faddeeva.h"

using namespace std;
using namespace Eigen;

#include "/home/brandon/Research/Reader/Reader.h"
#include "TypeDefinitions.h"
#include "MatrixUtilities.h"
#include "Exception.h"
#include "wieldVTK.h"

double computeGaussCosIntegral(int n, double x0, double sigma, double alpha)
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
    WIELD_NEW_EXCEPTION("Fourier series integral returned imaginary part: ret="<<ret<<", n="<<n<<", x0="<<x0<<", alpha="<<alpha);
  if (n==0)
    return ret.real() / (alpha);
  else
    return ret.real() / (alpha/2.);
}

int main(int argc, char* argv[])
{
  WIELD_TRY;

  Reader reader("fs.in");
  unsigned int order = reader.Read<int>("order");
  double sigma       = reader.Read<double>("sigma");
  double alpha1      = reader.Read<double>("alpha1");
  double alpha2      = reader.Read<double>("alpha2");
  double alpha3      = reader.Read<double>("alpha3");
  vector<double> X   = reader.Read<vector<double> >("X");
  vector<double> Y   = reader.Read<vector<double> >("Y");
  vector<double> Z   = reader.Read<vector<double> >("Z");
  string outfile     = reader.Read<string>("outfile");
  ofstream out(outfile.c_str());

  if ((X.size() != Y.size()) || (Y.size() != Z.size()) || (Z.size() != X.size()))
    WIELD_NEW_EXCEPTION("Error: X, Y, Z vectors must be the same size");
  int size = X.size();


  out << "$order " << order << endl;
  out << scientific;
  out << "$a1 " << alpha1 << endl;
  out << "$a2 " << alpha2 << endl;
  out << "$a3 " << alpha3 << endl;

  out << "$C ";
  CosSeries C(order);
  C.alpha1 = alpha1; C.alpha2 = alpha2; C.alpha3=alpha3;
  for (unsigned int l=0; l<order; l++)
    for (unsigned int m=0; m<order; m++)
      {
	out << "..." << endl;
	for (unsigned int n=0; n<order; n++)
	  {
	    C(l,m,n) = 0;
	    for (unsigned int i=0; i<size; i++)
	      C(l,m,n) += 
		computeGaussCosIntegral(l, X[i], sigma, alpha1)	*
		computeGaussCosIntegral(m, Y[i], sigma, alpha2)	*
		computeGaussCosIntegral(n, Z[i], sigma, alpha3);
	    if (l==0 && m==0 & n==0)
	      C(l,m,n)=0;
	    out.width(16);
	    out << C(l,m,n) << " ";
	  }
      }
  out << endl;

  out.close();


  //
  // Visualization
  //

  if (reader.Find("vtk"))
    {

      double xmin = reader.Read<double>("xmin");
      double ymin = reader.Read<double>("ymin");
      double zmin = reader.Read<double>("zmin");
      double xmax = reader.Read<double>("xmax");
      double ymax = reader.Read<double>("ymax");
      double zmax = reader.Read<double>("zmax");
      int resolution = reader.Read<int>("resolution");
      double FactorTop = reader.Read<double>("FactorTop", 0.);
      double FactorBottom= reader.Read<double>("FactorBottom",0.);


      renderCrystal(drawCrystal(C, Matrix3d::Identity(),
				reader.Read<double>("xmin"),
				reader.Read<double>("ymin"),
				reader.Read<double>("zmin"),
				reader.Read<double>("xmax"),
				reader.Read<double>("ymax"),
				reader.Read<double>("zmax"),
				reader.Read<int>("resolution"),
				reader.Read<double>("FactorTop"),
				reader.Read<double>("FactorBottom")));
 

    }


  
  WIELD_CATCH
}


