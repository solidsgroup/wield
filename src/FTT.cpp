#include "FTT.h"
#include "Dirac.h"
#include "colors.h"
#include <iostream>
using namespace std;

double FTT(int typeA, int typeB, int typeC, double a, double b, double c, double omega, double sigma)
{
  double F;
  if (typeA==SIN)
    if (typeB==SIN)
      if (typeC==SIN) // Sin Sin Sin
	F =  (
	      + (c+a-b)/((c+a-b)*(c+a-b)-omega*omega)
	      - (-c+a-b)/((-c+a-b)*(-c+a-b)-omega*omega) 
	      - (c+a+b)/((c+a+b)*(c+a+b)-omega*omega) 
	      + (-c+a+b)/((-c+a+b)*(-c+a+b)-omega*omega)
	      ) * sqrt(1/8*PI);
      else // SIN SIN COS
	F =  (
	      - Dirac(omega-c-a-b,sigma)
	      + Dirac(omega-c-a+b,sigma)
	      + Dirac(omega-c+a-b,sigma)
	      - Dirac(omega-c+a+b,sigma)
	      + Dirac(omega+c-a+b,sigma)
	      + Dirac(omega+c+a-b,sigma)
	      - Dirac(omega+c-a-b,sigma)
	      - Dirac(omega+c+a+b,sigma)
	      ) * sqrt(2*PI)/8;
    else // SIN COS COS
      F =  (
	    + (c+a+b)/((c+a+b)*(c+a+b)-omega*omega) 
	    + (-c+a+b)/((-c+a+b)*(-c+a+b)-omega*omega)
	    + (c+a-b)/((c+a-b)*(c+a-b)-omega*omega) 
	    + (-c+a-b)/((-c+a-b)*(-c+a-b)-omega*omega)
	    ) * sqrt(1/(8*PI));
  else /// COS COS COS
    F = (
	 + Dirac(omega-c-a-b,sigma)
	 + Dirac(omega-c-a+b,sigma)
	 + Dirac(omega-c+a-b,sigma)
	 + Dirac(omega-c+a+b,sigma)
	 + Dirac(omega+c-a+b,sigma)
	 + Dirac(omega+c+a-b,sigma)
	 + Dirac(omega+c-a-b,sigma)
	 + Dirac(omega+c+a+b,sigma)
	 ) * sqrt(2*PI)/8;
  
  if (F != F) 
    {
      cout << B_ON << FG_YELLOW << "Warning: NAN detected" << RESET << endl;
      F = 0;
    }
  return F;
}
