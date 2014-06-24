///
/// \file Crystal.cpp
///
#include "Crystal.h"

// int Generate(int order,
// 	     vector<double> alpha,
//           vector<pair<vector<double>, double> > atoms)
int Generate()
{
  int order=4;
  complex<double> x1(1,2);


  vector<double> cx(order), cy(order), cz(order);
  for (int i = 0; i < order; i++)
    {
      for (int j = 0; j < order; j++)
	{
	  

	}
    }


};

double CosExpInt(int n, double alpha, double epsilon, double x0)
{
  complex<double> A(-x0/epsilon, epsilon*n*PI/2/alpha);  // erf
  complex<double> B(-epsilon*epsilon*n*n*PI*PI/4/alpha/alpha, x0*n*PI/alpha); //exp

  // return
  //   (epsilon*sqrt(PI)/4)*
  //   (cerf(A)*exp(B) + cerf(conj(A))*exp(B) + cerf(A)*exp(conj(B)) + cerf(conj(A))*exp(conj(B)));

}
