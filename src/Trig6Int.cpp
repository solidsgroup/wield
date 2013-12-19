#include "Trig6Int.h"
#define COS 0
#define SIN 1
#define MOD(a) (double)(1 - 2*((a)%2))

#include <iostream>
using namespace std;
double Trig6Int(int *_T, double *_a, double epsilon)
{
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


double Trig6Int_epsilon(int *_T, double *_a, double epsilon)
{
  double I;  double dI; double eps2 = epsilon*epsilon; double eps3 = epsilon*epsilon*epsilon;
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
      dI = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  dI += exp(-e*e/(eps2)) * (2*e*e/eps3);
		}
      dI /= 32.;
    }
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == SIN && T[5] == SIN ) // cos cos cos cos sin sin
    {
      I = 0;
      dI = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  dI += MOD(k+1)*exp(-e*e/(eps2)) * (2*e*e/eps3);
		}
      dI /= 32.;
    }
  else if (T[0] == COS && T[1] == COS && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos sin sin sin sin
    {
      I = 0;
      dI = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  dI += MOD(j+k+2)*exp(-e*e/eps2) * (2*e*e/eps3);
		}
      dI /= 32.;
    }
  else if (T[0] == SIN && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // sin sin sin sin sin sin
    {
      I = 0;
      dI = 0;
      double e;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
		  dI += MOD(i+j+k+3)*exp(-e*e/eps2) * (2*e*e/eps3);
		}
      dI /= 32.;
    }
  return dI;
}
