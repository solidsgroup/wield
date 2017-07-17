///
/// \file wieldSurface.h
/// \brief Compute the surface integral of two multiplied Fourier series
///
/// The purpose of the Integrator::Surface function is to compute the integral of two functions \f$\phi_1,\phi_2\f$ with a measure function \f$g_\varepsilon\f$
/// \f[\int_{-\infty}^\infty\int_{-\infty}^\infty \phi_1(\Omega_1\mathbf{x})\phi_2(\Omega_2\mathbf{x})g_\varepsilon(\mathbf{x})dxdy\bigg|_{z=0}\f]
/// where the functions \f$\Omega_1,\Omega_2\f$ are given by Fourier Cosine series specified in variables C1 and C2. The rotation matrices \f$\Omega_1,\Omega_2\f$ specify the orientation of the crystals. Specifically,
/// \f[\Omega = \begin{bmatrix}\mathbb{n}_1,\mathbb{n}_1,\mathbb{n}_1\end{bmatrix}\f]
/// where \f$\mathbb{n}_3\f$ represents the crystallographic direction which is <i>normal</i> to the interface. The vectors \f$\mathbb{n}_1,\mathbb{n}_2\f$ represent the in-plane crystallographic directions. Orthogonality of these vectors is enforced by ensuring that \f$\Omega_1,\Omega_2\in SO(3)\f$
///

#ifndef WIELD_INTEGRATOR_SURFACE_D
#define WIELD_INTEGRATOR_SURFACE_D
#include <iostream>
#include <math.h>

#include "Utils/wieldTypes.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldFourierSeries.h"

namespace Wield
{
namespace Integrator
{

template<class Mollifier>
double Surface(Wield::Series::FourierSeries<Mollifier> C1,
	       Eigen::Matrix3d R1,
	       Wield::Series::FourierSeries<Mollifier> C2,
	       Eigen::Matrix3d R2,
	       double epsilon,
	       double tolerance=0)
{
  std::complex<double> w12 = 0;
  double mod_tolerance = (epsilon * log(1.0/tolerance));

  for (int l=1-C1.order; l < C1.order; l++)
    for (int m=1-C1.order; m < C1.order; m++)
      for (int n=1-C1.order; n < C1.order; n++)
	{
	  if (fabs(real(C1(l,m,n))<tolerance)) continue;

	  Eigen::Vector3d a1((double)l * 2.* pi / C1.alphaX,
			     (double)m * 2.* pi / C1.alphaY,
			     (double)n * 2.* pi / C1.alphaZ);
	  Eigen::Vector3d Ra1 = R2.transpose()*R1*a1;

	  int xmin = std::max(1-C2.order, (int)((C2.alphaX/2./pi)*(Ra1[0]-2*mod_tolerance)));
	  int xmax = std::min(C2.order,   (int)((C2.alphaX/2./pi)*(Ra1[0]+2*mod_tolerance)));
	  int ymin = std::max(1-C2.order, (int)((C2.alphaY/2./pi)*(Ra1[1]-2*mod_tolerance)));
	  int ymax = std::min(C2.order,   (int)((C2.alphaY/2./pi)*(Ra1[1]+2*mod_tolerance)));
	  int zmin = std::max(1-C2.order, (int)((C2.alphaZ/2./pi)*(Ra1[2]-2*mod_tolerance)));
	  int zmax = std::min(C2.order,   (int)((C2.alphaZ/2./pi)*(Ra1[2]+2*mod_tolerance)));


	  // for (int p=1-C2.order; p < C2.order; p++)
	  //   for (int q=1-C2.order; q < C2.order; q++)
	  //     for (int r=1-C2.order; r < C2.order; r++)
	
	  for (int p=xmin; p < xmax; p++)
	    for (int q=ymin; q < ymax; q++)
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

		  Eigen::Vector3d arg= R2*(Ra1 - a2);

		  w12 += C1(l,m,n)*conj(C2(p,q,r))*2.*pi*exp(- sqrt(arg[0]*arg[0]+arg[1]*arg[1])/epsilon);
		}
	}
  return real(w12);
}

template<class Mollifier>
double Surface(Wield::Series::FourierSeries<Mollifier> C1,
	       Eigen::Matrix3d R1,
	       Eigen::Vector3d t1,
	       Wield::Series::FourierSeries<Mollifier> C2,
	       Eigen::Matrix3d R2,
	       Eigen::Vector3d t2,
	       double epsilon,
	       double tolerance=0)
{
  std::complex<double> w12 = 0, I(0,1);

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

		    w12 += C1(l,m,n)*conj(C2(p,q,r))*2.*pi*exp(- sqrt(arg[0]*arg[0]+arg[1]*arg[1])/epsilon)
		      * exp(-I*(t1.dot(R1*a1) - t2.dot(R2*a2)));
		  }
  return real(w12);
}


}
}
#endif //SURFACEINTEGRATE_D
