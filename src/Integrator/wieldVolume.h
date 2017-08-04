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
#include "Utils/wieldWarnings.h"
#include "Utils/wieldExceptions.h"
#include "Series/wieldFourierSeries.h"

namespace Wield
{
namespace Integrator
{

/// 
/// This function computes the following integral:
/// \f[ 
///     \int \rho^A_\sigma(x) \overline{\rho^B_\sigma(x)}\hat{\Psi}_\varepsilon dx 
/// \f]
/// where \f$\rho^A_\sigma,\rho^B_\sigma\f$ are the functions describing the two crystals, and are
/// passed to this function using the FourierSeries structures C1 and C2.
/// The integral can be evaluated exactly as the following series:
/// \f[ 
///     \sum_{m,n\in\mathbb{Z}^3} \mu^A_m\,\mu^B_n\,\hat{\phi}^A_\sigma[k^A(m)]\,\hat{\phi}^B_\sigma[k^B(n)]\,\Psi_\varepsilon[R^{A}k^A(m)-R^Bk^B(n)]
/// \f]
/// In this code, \f$\mu^{A,B}_{m,n}\hat{\phi}^{A,B}_\sigma[k^{A,B}(m,n)]\f$ are precomputed in the FourierSeries structures and are accessible 
/// using the bracket operator C1[l,m,n] where (l,m,n) are integers making up the three-tuple $m,n\in\mathbb{Z}^3$.
///
/// The double sum is actually a 6-nested sum, resulting in Order^6 operations, which is computationally prohibitive.
/// Some shortcuts are taken using the tolerance parameter to preemptively identify negligible terms.
///
template<class Mollifier>
double Volume(Wield::Series::FourierSeries<Mollifier> &C1, ///< [in] Structure for the first Fourier Series crystal
	      Eigen::Matrix3d R1,                          ///< [in] Rotation matrix describing the first crystal rotation
	      Wield::Series::FourierSeries<Mollifier> &C2, ///< [in] Structure for the first Fourier Series crystal
	      Eigen::Matrix3d R2,                          ///< [in] Rotation matrix describing the first crystal rotation
	      double epsilon,                              ///< [in] Numerical parameter that controls the stdev of the window function
	      double tolerance=0,                          ///< [in] Numerical tolerance -- by default, ignore no terms
	      bool verbose=false)                          ///< [in] Toggle to turn on extra output information                         
{
  WIELD_EXCEPTION_TRY;
  std::complex<double> w12 = 0;
  double mod_tolerance = epsilon * sqrt( -log(tolerance) );

  int order_max = 0;

  for (int l=1-C1.order; l < C1.order; l++)
    {
      if(verbose) WIELD_PROGRESS("Computing CSL", l-(1-C1.order), 2*C1.order, 1);
      for (int m=1-C1.order; m < C1.order; m++)
	{
	  for (int n=1-C1.order; n < C1.order; n++)
	    {
	      if (fabs(real(C1(l,m,n))<tolerance)) continue;
	      Eigen::Vector3d a1((double)l * 2.* pi / C1.alphaX,
				 (double)m * 2.* pi / C1.alphaY,
				 (double)n * 2.* pi / C1.alphaZ);
	      Eigen::Vector3d Ra1 = R2.transpose()*R1*a1;

	      // int xmin = std::max(1-C2.order, (int)((C2.alphaX/2./pi)*(Ra1[0]-2*mod_tolerance)));
	      // int xmax = std::min(C2.order,   (int)((C2.alphaX/2./pi)*(Ra1[0]+2*mod_tolerance)));
	      // int ymin = std::max(1-C2.order, (int)((C2.alphaY/2./pi)*(Ra1[1]-2*mod_tolerance)));
	      // int ymax = std::min(C2.order,   (int)((C2.alphaY/2./pi)*(Ra1[1]+2*mod_tolerance)));
	      // int zmin = std::max(1-C2.order, (int)((C2.alphaZ/2./pi)*(Ra1[2]-2*mod_tolerance)));
	      // int zmax = std::min(C2.order,   (int)((C2.alphaZ/2./pi)*(Ra1[2]+2*mod_tolerance)));

	      int xmin = (int)((C2.alphaX/2./pi)*(Ra1[0])) - 2;
	      int xmax = (int)((C2.alphaX/2./pi)*(Ra1[0])) + 2;
	      int ymin = (int)((C2.alphaY/2./pi)*(Ra1[1])) - 2;
	      int ymax = (int)((C2.alphaY/2./pi)*(Ra1[1])) + 2;
	      int zmin = (int)((C2.alphaZ/2./pi)*(Ra1[2])) - 2;
	      int zmax = (int)((C2.alphaZ/2./pi)*(Ra1[2])) + 2;

	      //std::cout << xmax<<"-"<<xmin << " " << ymax<<"-"<<ymin << " " << zmax<<"-"<<zmin << std::endl;

	      for (int p=xmin; p < xmax; p++)
		{
		  for (int q=ymin; q < ymax; q++)
		    {
		      for (int r=zmin; r < zmax; r++)
			{
			  if (fabs(real(C1(p,q,r))<tolerance)) continue;
			  if (l==(1-C1.order) || l==(C1.order-1) ||
			      m==(1-C1.order) || m==(C1.order-1) ||
			      n==(1-C1.order) || n==(C1.order-1) ||
			      p==(1-C2.order) || p==(C2.order-1) ||
			      q==(1-C2.order) || q==(C2.order-1) ||
			      r==(1-C2.order) || r==(C2.order-1))
			    WIELD_EXCEPTION_NEW("Reached the bound of Fourier expansion; try increasing Order");

			  Eigen::Vector3d a2((double)p * 2.* pi / C2.alphaX,
					     (double)q * 2.* pi / C2.alphaY,
					     (double)r * 2.* pi / C2.alphaZ);
			  Eigen::Vector3d arg= Ra1 - a2;

			  if (arg.dot(arg)>mod_tolerance) continue;

			  std::complex<double> add = C1(l,m,n)*conj(C2(p,q,r))*2.*pi*exp(- (arg[0]*arg[0] + arg[1]*arg[1] + arg[2]*arg[2] )/(epsilon*epsilon));
			  w12 += add;

			  if (abs(l) > order_max) order_max = abs(l);
			  if (abs(m) > order_max) order_max = abs(m);
			  if (abs(n) > order_max) order_max = abs(n);
			  if (abs(p) > order_max) order_max = abs(p);
			  if (abs(q) > order_max) order_max = abs(q);
			  if (abs(r) > order_max) order_max = abs(r);
			}
		    }
		}
	    }
	}
    }
  if (verbose) WIELD_PROGRESS_COMPLETE("Computing CSL");
  if (verbose) WIELD_NOTE("Highest order term used: "<< order_max << std::endl);
  return real(w12);
  WIELD_EXCEPTION_CATCH;
}
}
}
#endif 
