#include "DTrig6Int.h"

Vector6d DTrig6Int(int *_T, double *_a, double epsilon)
{
  double I;  double eps2 = epsilon*epsilon;
  int T[6]; double a[6]; int index[6];
  int ctr=0;
  
  for (int i=0;i<6;i++)
    if (_T[i]==0) 
      {
	T[ctr] = _T[i]; 
	a[ctr] = _a[i]; 
	index[ctr]=i;
	ctr++;
      }
  for (int i=0;i<6;i++)
    if (_T[i]==1) 
      {
	T[ctr] = _T[i]; 
	a[ctr] = _a[i]; 
	index[ctr]=i;
	ctr++;
      }
  
  Vector6d DI(6);

  double e,dI;

  if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == SIN ) // cos cos cos cos cos sin
    I = 0;
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos cos sin sin sin
    I = 0;
  else if (T[0] == COS && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos sin sin sin sin sin
    I = 0;
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == COS ) // cos cos cos cos cos cos
    {
      DI *= 0;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a[0] + MOD(i)*a[1] + MOD(m)*a[2] + MOD(j+m)*a[3] + MOD(l+m)*a[4] + MOD(l+k+m)*a[5]);
		  dI = exp(-e*e/eps2) * (-2*e/eps2);
		  DI(0) += dI * 1;
		  DI(1) += dI * MOD(i);
		  DI(2) += dI * MOD(m);
		  DI(3) += dI * MOD(j+m);
		  DI(4) += dI * MOD(l+m);
		  DI(5) += dI * MOD(l+k+m);
		}
      DI *= 1/(32*sqrt(PI)*epsilon);
    }
  else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == SIN && T[5] == SIN ) // cos cos cos cos sin sin
    {
      DI *= 0;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a[0] + MOD(i)*a[1] + MOD(m)*a[2] + MOD(j+m)*a[3] + MOD(l+m)*a[4] + MOD(l+k+m)*a[5]);
		  dI = MOD(k+1)*exp(-e*e/eps2) * (-2*e/eps2);
		  DI(0) += dI * 1;
		  DI(1) += dI * MOD(i);
		  DI(2) += dI * MOD(m);
		  DI(3) += dI * MOD(j+m);
		  DI(4) += dI * MOD(l+m);
		  DI(5) += dI * MOD(l+k+m);
		}
      DI *= 1/(32*sqrt(PI)*epsilon);
    }
  else if (T[0] == COS && T[1] == COS && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos sin sin sin sin
    {
      DI *= 0;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a[0] + MOD(i)*a[1] + MOD(m)*a[2] + MOD(j+m)*a[3] + MOD(l+m)*a[4] + MOD(l+k+m)*a[5]);
		  dI = MOD(j+k+2)*exp(-e*e/eps2) * (-2*e/eps2);
		  DI(0) += dI * 1;
		  DI(1) += dI * MOD(i);
		  DI(2) += dI * MOD(m);
		  DI(3) += dI * MOD(j+m);
		  DI(4) += dI * MOD(l+m);
		  DI(5) += dI * MOD(l+k+m);
		}
      DI *= 1/(32*sqrt(PI)*epsilon);
    }
  else if (T[0] == SIN && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // sin sin sin sin sin sin
    {
      DI *= 0;
      for (int i=0;i<2;i++)
	for (int j=0;j<2;j++)
	  for (int k=0;k<2;k++)
	    for (int l=0;l<2;l++)
	      for (int m=0;m<2;m++)
		{
		  e = (a[0] + MOD(i)*a[1] + MOD(m)*a[2] + MOD(j+m)*a[3] + MOD(l+m)*a[4] + MOD(l+k+m)*a[5]);
		  dI = MOD(i+j+k+3)*exp(-e*e/eps2) * (-2*e/eps2);
		  DI(0) += dI * 1;
		  DI(1) += dI * MOD(i);
		  DI(2) += dI * MOD(m);
		  DI(3) += dI * MOD(j+m);
		  DI(4) += dI * MOD(l+m);
		  DI(5) += dI * MOD(l+k+m);
		}
      DI *= 1/(32*sqrt(PI)*epsilon);
    }

  Vector6d DI_ret;
  for (int i=0; i<6; i++)
    DI_ret(index[i]) = DI(i);

  return DI_ret;
}
