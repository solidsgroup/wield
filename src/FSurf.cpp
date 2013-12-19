#include "FSurf.h"
#include "FTT.h"
#include "math.h"
#include "colors.h"

double FSurf(int order, double ***C, vector<double> n1, vector<double> n2, double a0, double omega1, double omega2, double sigma, double tol)
{
  double F = 0;
  for (int i=0;i<order;i++)
    for (int j=0;j<order;j++)
      for (int k=0;k<order;k++)
	{
	  if (fabs(C[i][j][k]) > tol)
	    {
	      double a1 = n1[0]*i*PI/a0;
	      double b1 = n1[1]*j*PI/a0;
	      double c1 = n1[2]*k*PI/a0;
	      double a2 = n2[0]*i*PI/a0;
	      double b2 = n2[1]*j*PI/a0;
	      double c2 = n2[2]*k*PI/a0;

	      F = F + C[i][j][k] * 
		( 
		  FTT(COS,COS,COS,a1,b1,c1,omega1,sigma)*
		  FTT(COS,COS,COS,a2,b2,c2,omega2,sigma) 
		  -
		  FTT(SIN,COS,COS,c1,a1,b1,omega1,sigma)*
		  FTT(SIN,COS,COS,c2,a2,b2,omega2,sigma)
		  - 
		  FTT(SIN,COS,COS,b1,a1,c1,omega1,sigma)*
		  FTT(SIN,COS,COS,b2,a2,c2,omega2,sigma)
		  - 
		  FTT(SIN,COS,COS,a1,b1,c1,omega1,sigma)*
		  FTT(SIN,COS,COS,a2,b2,c2,omega2,sigma)
		  +
		  FTT(SIN,SIN,COS,c1,a1,b1,omega1,sigma)*
		  FTT(SIN,SIN,COS,c2,a2,b2,omega2,sigma)
		  + 
		  FTT(SIN,SIN,COS,b1,a1,c1,omega1,sigma)*
		  FTT(SIN,SIN,COS,b2,a2,c2,omega2,sigma)
		  +
		  FTT(SIN,SIN,COS,a1,b1,c1,omega1,sigma)*
		  FTT(SIN,SIN,COS,a2,b2,c2,omega2,sigma)
		  - 
		  FTT(SIN,SIN,SIN,a1,b1,c1,omega1,sigma)*
		  FTT(SIN,SIN,SIN,a2,b2,c2,omega2,sigma)
		  );
	    }
	}
  if (F != F) 
    {
      cout << B_ON << FG_YELLOW << "Warning: NAN detected" << RESET << endl;
      F = 0;
    }
  return F;
}
