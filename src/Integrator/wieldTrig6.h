///
/// @file wieldTrig6.h
/// \brief Compute an integral with 6 cosines in the integrand
///
/// Compute the following integral
/// \f[\int_{-\infty}^\infty\int_{-\infty}^\infty g_\varepsilon(x,y)T^a_1(a_1x)T^a_2(a_2x)T^a_3(a_3x)T^a_4(a_4x)T^a_5(a_5x)T^a_6(a_6x)T^b_1(b_1y)T^b_2(b_2y)T^b_3(b_3y)T^b_4(b_4y)T^b_5(b_5y)T^b_6(b_6y)\f]
/// Where \f$T_1\ldots T_6\f$ are given in the T arrays and \f$a_1\ldots a_6\f$ are given in the a arrays. 
/// Elements in the T array can take values of 0 or 1, and indicate whether the function is a sine or cosine. For instance, if T[2]==1 then \f$T_2(a_2x)=\sin(a_2 x)\f$
///
/// The function \f$g_\varepsilon(x,y)\f$ is unique to the different functions listed below.
///

#ifndef WIELD_INTEGRATOR_TRIG6_H
#define WIELD_INTEGRATOR_TRIG6_H

#include <iostream>
#include <math.h>
#include "Utils/wieldTypes.h"

/// \cond SUPERFLUOUS
#define COS 0
#define SIN 1
//#define MOD(a) (double)(1 - 2*((a)%2))
#define MOD(a) (1 - 2*((a) & 1))
/// \endcond

using namespace std;

///
/// \fn Trig6_Gaussian
/// \brief Use a Gaussian weighted function
///
double Trig6_Gaussian(int *_T,         ///< Trig indicator functions (must be size 6)
		      double *_a,      ///< Argument for trig functions
		      double epsilon)  ///< Std. dev. for the Gaussian weight function
{
  ///
  /// This function uses a weight function of the form
  /// \f[g_\varepsilon(x,y) = \exp\bigg(-\frac{(x^2+y^2)}{\varepsilon^2}\bigg)\f]
  /// Because of the nature of Gaussian integrals, a full 12 trig integral can be decoupled and evaluated as 
  /// Trig6_Gaussian(T1...T6,a1...a6,epsilon)Trig6_Gaussian(T7..T12,a7...a12,epsilon) 
  /// which is much faster.
  ///
  double I;  double eps2 = epsilon*epsilon;
  int T[6]; double a[6];
  int ctr=0;
  
  for (int i=0;i<6;i++)
    if (_T[i]==0) 
      {
	T[ctr] = _T[i]; 
	a[ctr] = _a[i]; 
	ctr++;
      }
  for (int i=0;i<6;i++)
    if (_T[i]==1) 
      {
	T[ctr] = _T[i]; 
	a[ctr] = _a[i]; 
	ctr++;
      }
  double a1=a[0], a2=a[1], a3=a[2], a4=a[3], a5=a[4], a6=a[5];
  
  if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == SIN ) // cos cos cos cos cos sin
    I = 0;
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos cos sin sin sin
    I = 0;
  else if (T[0] == COS && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos sin sin sin sin sin
    I = 0;
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == COS ) // cos cos cos cos cos cos
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += exp(-e*e/eps2);
		}
      I /= 32.;
    }
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == SIN && T[5] == SIN ) // cos cos cos cos sin sin
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += MOD(k+1)*exp(-e*e/eps2);
		}
      I /= 32.;
    }
  else if (T[0] == COS && T[1] == COS && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos sin sin sin sin
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += MOD(j+k+2)*exp(-e*e/eps2);
		}
      I /= 32.;
    }
  else if (T[0] == SIN && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // sin sin sin sin sin sin
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += MOD(i+j+k+3)*exp(-e*e/eps2);
		}
      I /= 32.;
    }
  return I;
}

///
/// \fn Trig6_Cauchy
/// \brief Use a Cauchy (like) weight function
///
double Trig6_Cauchy(int *_T1,         ///< Trig indicator functions (size 6)
		    int *_T2,         ///< Trig indicator functions (size 6)
		    double *_a,       ///< Coefficients for the first six trig functions (size 6)
		    double *_b,       ///< Coefficients for the second six trig functions (size 6)
		    double epsilon)   ///< Std. dev. for the Gaussian weight function
{
  ///
  /// This function uses a weight function \f$g_\varepsilon\f$ which is <i>unknown</i>; however its Fourier transform is
  /// \f[\mathcal{F}[g_\varepsilon](\omega_1,\omega_2) = G_\varepsilon(\omega_1,\omega_2) = \exp\bigg(-\frac{\sqrt{\omega_1^2+\omega_2^2}}{\sigma}\bigg)\f]
  ///
  /// Because of the way that the integral is computed, the peaks in the energy curve will have the form of \f$G_\varepsilon\f$; 
  /// furthermore \f$G_{\varepsilon}\f$ is all that is required to compute the integral.
  /// 
  int T1[6], T2[6]; double a[6], b[6];
  int ctr1=0, ctr2=0;
  int S1, S2;
  
  for (int i=0;i<6;i++)
    {
      if (_T1[i]==0) 
	{
	  T1[ctr1] = _T1[i]; 
	  a[ctr1] = _a[i]; 
	  ctr1++;
	}
      if (_T2[i]==0) 
	{
	  T2[ctr2] = _T2[i]; 
	  b[ctr2] = _b[i]; 
	  ctr2++;
	}
    }      

  S1 = 6-ctr1; // the number of sines
  S2 = 6-ctr2; // the number of sines
  if (S1%2 || S2%2) return 0; // return if there is an odd number of sines

  for (int i=0;i<6;i++)
    {
      if (_T1[i]==1) 
	{
	  T1[ctr1] = _T1[i]; 
	  a[ctr1] = _a[i]; 
	  ctr1++;
	}
      if (_T2[i]==1) 
	{
	  T2[ctr2] = _T2[i]; 
	  b[ctr2] = _b[i]; 
	  ctr2++;
	}
    }
  double a1=a[0], a2=a[1], a3=a[2], a4=a[3], a5=a[4], a6=a[5];
  double b1=b[0], b2=b[1], b3=b[2], b4=b[3], b5=b[4], b6=b[5];

  
  double tI;
  double I = 0;
  double e1,e2;

  for (int i=0;i<2;i++)
    for (int j=0;j<2;j++)
      for (int k=0;k<2;k++)
  	for (int l=0;l<2;l++)
  	  for (int m=0;m<2;m++)
	    {
	      e1 = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
	      for (int p=0;p<2;p++)
		for (int q=0;q<2;q++)
		  for (int r=0;r<2;r++)
		    for (int s=0;s<2;s++)
		      for (int t=0;t<2;t++)
			{
			  e2 = (b1 + MOD(p)*b2 + MOD(t)*b3 + MOD(q+t)*b4 + MOD(s+t)*b5 + MOD(s+r+t)*b6);
			  tI = exp(-sqrt(e1*e1 + e2*e2)/epsilon);
			  if (S1==6) // SSSSSS
			    tI *= MOD(i+j+k+3);
			  else if (S1==4) // CCSSSS
			    tI *= MOD(j+k+2);
			  else if (S1==2) // CCCCSS
			    tI *= MOD(k+1);
			  if (S2==6)
			    tI *= MOD(p+q+r+3);
			  else if (S2==4)
			    tI *= MOD(q+r+2);
			  else if (S2==2)
			    tI *= MOD(r+1);
			  I += tI;
			}
	    }

  I /= 1024.;
  return I;
}

///
/// \fn Trig6_FakeCauchy
/// \brief <b>DANGER</b>: do not use, I don't remember what this function does.
///
double Trig6_FakeCauchy(int *_T, double *_a, double epsilon)
{
  ///
  /// DO NOT USE
  ///
  double I;
  int T[6]; double a[6];
  int ctr=0;
  
  for (int i=0;i<6;i++)
    if (_T[i]==0) 
      {
	T[ctr] = _T[i]; 
	a[ctr] = _a[i]; 
	ctr++;
      }
  for (int i=0;i<6;i++)
    if (_T[i]==1) 
      {
	T[ctr] = _T[i]; 
	a[ctr] = _a[i]; 
	ctr++;
      }
  double a1=a[0], a2=a[1], a3=a[2], a4=a[3], a5=a[4], a6=a[5];
  
  if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == SIN ) // cos cos cos cos cos sin
    I = 0;
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos cos sin sin sin
    I = 0;
  else if (T[0] == COS && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos sin sin sin sin sin
    I = 0;
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == COS ) // cos cos cos cos cos cos
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += exp(-fabs(e)/epsilon);
		}
      I /= 32.;
    }
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == SIN && T[5] == SIN ) // cos cos cos cos sin sin
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += MOD(k+1)*exp(-fabs(e)/epsilon);
		}
      I /= 32.;
    }
  else if (T[0] == COS && T[1] == COS && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos sin sin sin sin
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += MOD(j+k+2)*exp(-fabs(e)/epsilon);
		}
      I /= 32.;
    }
  else if (T[0] == SIN && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // sin sin sin sin sin sin
    {
      I = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  I += MOD(i+j+k+3)*exp(-fabs(e)/epsilon);
		}
      I /= 32.;
    }
  return I;
}



#endif
