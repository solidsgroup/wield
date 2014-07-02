///
/// \file SurfaceIntegrate.h
/// \brief Compute the surface integral of two multiplied Fourier series
///
/// The purpose of the SurfaceIntegrate function is to compute the integral of two functions \f$\phi_1,\phi_2\f$ with a measure function \f$g_\varepsilon\f$
/// \f[\int_{-\infty}^\infty\int_{-\infty}^\infty \phi_1(\Omega_1\mathbf{x})\phi_2(\Omega_2\mathbf{x})g_\varepsilon(\mathbf{x})dxdy\bigg|_{z=0}\f]
/// where the functions \f$\Omega_1,\Omega_2\f$ are given by Fourier Cosine series specified in variables C1 and C2. The rotation matrices \f$\Omega_1,\Omega_2\f$ specify the orientation of the crystals. Specifically,
/// \f[\Omega = \begin{bmatrix}\mathbb{n}_1,\mathbb{n}_1,\mathbb{n}_1\end{bmatrix}\f]
/// where \f$\mathbb{n}_3\f$ represents the crystallographic direction which is <i>normal</i> to the interface. The vectors \f$\mathbb{n}_1,\mathbb{n}_2\f$ represent the in-plane crystallographic directions. Orthogonality of these vectors is enforced by ensuring that \f$\Omega_1,\Omega_2\in SO(3)\f$
///

#ifndef SURFACEINTEGRATE_D
#define SURFACEINTEGRATE_D
#include <iostream>
#include <math.h>
#include "Eigen/Core"
#include "Eigen/Geometry"

#include "Utils/wieldTypes.h"
#include "Integrator/wieldTrig6.h"

using namespace Eigen;
using namespace std;




double SurfaceIntegrate(CosSeries C1, 
			Matrix3d R1,
			CosSeries C2, 
			Matrix3d R2,
			double epsilon, 
			double tolerance = 0, 
			string distribution = "cauchy")
{
  WIELD_TRY;
  int type; 
  if (distribution=="gaussian") type = 0;
  else if (distribution=="cauchy") type = 1;
  else if (distribution=="fakecauchy") type = 2;
  else {cout << "Error: Distribution type not specified" << endl; throw(0);}

  if ((R1.transpose()*R1 - Matrix3d::Identity()).norm() > 1E-10)
    WIELD_NEW_EXCEPTION("R1 is not a rotation matrix");
  if ((R2.transpose()*R2 - Matrix3d::Identity()).norm() > 1E-10)
    WIELD_NEW_EXCEPTION("R2 is not a rotation matrix");

  Vector3d na1 = R1.col(0);
  Vector3d nb1 = R2.col(0);
  Vector3d na3 = R1.col(2);
  Vector3d nb3 = R2.col(2);

  Vector3d na2 = na3.cross(na1); Vector3d nb2 = nb3.cross(nb1);
  double S=0;
  for (int i=0;i<C1.order;i++)
    for (int j=0;j<C1.order;j++) 
      for (int k=0;k<C1.order;k++) 
	for (int l=0;l<C2.order;l++)
	  for (int m=0;m<C2.order;m++)
	    for (int n=0;n<C2.order;n++)
	      for (int p=0;p<2;p++)
		for (int q=0;q<2;q++)
		  for (int r=0;r<2;r++)
		    for (int s=0;s<2;s++)
		      for (int t=0;t<2;t++)
			for (int u=0;u<2;u++)
			  if ( (p+q+r+s+t+u)%2 == 0 ) // only do if p+q+r+s+t+u is even
			    if (abs(C1(i,j,k)*C2(l,m,n)) > tolerance) // skip terms with low coefficients
			      {
				double Ia1_1 = (double)i*pi*na1[0]/C1.alpha1; double Ia2_1 = (double)i*pi*na2[0]/C1.alpha1;
				double Ja1_2 = (double)j*pi*na1[1]/C1.alpha2; double Ja2_2 = (double)j*pi*na2[1]/C1.alpha2;
				double Ka1_3 = (double)k*pi*na1[2]/C1.alpha3; double Ka2_3 = (double)k*pi*na2[2]/C1.alpha3;
				double Lb1_1 = (double)l*pi*nb1[0]/C2.alpha1; double Lb2_1 = (double)l*pi*nb2[0]/C2.alpha1;
				double Mb1_2 = (double)m*pi*nb1[1]/C2.alpha2; double Mb2_2 = (double)m*pi*nb2[1]/C2.alpha2;
				double Nb1_3 = (double)n*pi*nb1[2]/C2.alpha3; double Nb2_3 = (double)n*pi*nb2[2]/C2.alpha3;

				int F[6] = {p, q, r, s, t, u};
				double a1[6] = {Ia1_1, Ja1_2, Ka1_3, Lb1_1, Mb1_2, Nb1_3};
				double a2[6] = {Ia2_1, Ja2_2, Ka2_3, Lb2_1, Mb2_2, Nb2_3};

				if ((i+j+k == 0) || (l+m+n == 0)) continue;
				
				if (type==0) // Gaussian
				  S += 
				    C1(i,j,k)*C2(l,m,n)
				    * Trig6_Gaussian(F, a1, epsilon)
				    * Trig6_Gaussian(F, a2, epsilon);
				else if (type==1) // Cauchy
				  S += 
				    C1(i,j,k)*C2(l,m,n)
				    * Trig6_Cauchy(F,F,a1,a2,epsilon);
				else // Fake Cauchy
				  S += 
				    C1(i,j,k)*C2(l,m,n)
				    * Trig6_FakeCauchy(F, a1, epsilon)
				    * Trig6_FakeCauchy(F, a2, epsilon);
				if (S != S)
				  WIELD_NEW_EXCEPTION("Nan detected! S="<<S<<", ijklmnpqrstu="<<i<<j<<k<<l<<m<<n<<p<<q<<r<<s<<t<<u);
			      }
  return S;
  //return S * (epsilon * sqrt(pi)) * (epsilon * sqrt(pi));
  WIELD_CATCH;
}

#endif //SURFACEINTEGRATE_D
