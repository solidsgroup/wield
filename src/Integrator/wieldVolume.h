///
/// \file wieldVolume.h
/// \brief Compute the volume integral of two multiplied Fourier series
///
///

#ifndef WIELD_INTEGRATOR_VOLUME_D
#define WIELD_INTEGRATOR_VOLUME_D
#include <iostream>
#include <math.h>

#include "Utils/wieldTypes.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldFourierSeries.h"

namespace Wield
{
namespace Integrator
{
double Volume(Wield::Series::FourierSeries C1,
	      Eigen::Matrix3d R1,
	      Wield::Series::FourierSeries C2,
	      Eigen::Matrix3d R2,
	      double epsilon,
	      double tolerance=0)
{
  std::complex<double> w12 = 0;

  for (int l=1-C1.order; l < C1.order; l++)
    for (int m=1-C1.order; m < C1.order; m++)
      for (int n=1-C1.order; n < C1.order; n++)
	if (fabs(real(C1(l,m,n))<tolerance)) continue;
	else
	for (int p=1-C2.order; p < C2.order; p++)
	  for (int q=1-C2.order; q < C2.order; q++)
	    for (int r=1-C2.order; r < C2.order; r++)
	    if (fabs(real(C1(p,q,r))<tolerance)) continue;
		else
		  {
		    Eigen::Vector3d a1((double)l * 2.* pi / C1.alphaX,
				       (double)m * 2.* pi / C1.alphaY,
				       (double)n * 2.* pi / C1.alphaZ);
		    Eigen::Vector3d a2((double)p * 2.* pi / C2.alphaX,
				       (double)q * 2.* pi / C2.alphaY,
				       (double)r * 2.* pi / C2.alphaZ);
		    Eigen::Vector3d arg= R1*a1 - R2*a2;
		    w12 += C1(l,m,n)*conj(C2(p,q,r))*2.*pi*exp(- sqrt( arg[0]*arg[0] + arg[1]*arg[1] + arg[2]*arg[2] )/epsilon);
		  }
  return real(w12);
}
}
}
#endif 
