///
/// \file Trig6Int2_RS
/// \brief This is the short description for Trig2Int2_RS
///

#include "Trig6Int2_RS.h"

double RS::Trig6Int_2(int *_T1, int *_T2, double *_a, double *_b, double epsilon)
{
  double eps2 = epsilon*epsilon;
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
  S2 = 6-ctr2; // the number of sinse
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
	    for (int p=0;p<2;p++)
	      for (int q=0;q<2;q++)
		for (int r=0;r<2;r++)
		  for (int s=0;s<2;s++)
		    for (int t=0;t<2;t++)
		      {
			e1 = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
			e2 = (b1 + MOD(p)*b2 + MOD(t)*b3 + MOD(q+t)*b4 + MOD(s+t)*b5 + MOD(s+r+t)*b6);
			tI = exp(-sqrt(e1*e1 + e2*e2)/epsilon);
			//tI = exp(-(e1*e1 + e2*e2)/eps2);
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
  I /= 1024.;

  // if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == SIN ) // cos cos cos cos cos sin
  //   I = 0;
  // else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos cos sin sin sin
  //   I = 0;
  // else if (T[0] == COS && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos sin sin sin sin sin
  //   I = 0;
  // else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == COS && T[5] == COS ) // cos cos cos cos cos cos
  //   {
  //     I = 0;
  //     double e;
  //     for (int i=0;i<2;i++)
  // 	for (int j=0;j<2;j++)
  // 	  for (int k=0;k<2;k++)
  // 	    for (int l=0;l<2;l++)
  // 	      for (int m=0;m<2;m++)
  // 		{
  // 		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
  // 		  I += exp(-fabs(e)/epsilon);
  // 		}
  //     I /= 32.;
  //   }
  // else if (T[0] == COS && T[1] == COS && T[2] == COS && T[3] == COS && T[4] == SIN && T[5] == SIN ) // cos cos cos cos sin sin
  //   {
  //     I = 0;
  //     double e;
  //     for (int i=0;i<2;i++)
  // 	for (int j=0;j<2;j++)
  // 	  for (int k=0;k<2;k++)
  // 	    for (int l=0;l<2;l++)
  // 	      for (int m=0;m<2;m++)
  // 		{
  // 		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
  // 		  I += MOD(k+1)*exp(-fabs(e)/epsilon);
  // 		}
  //     I /= 32.;
  //   }
  // else if (T[0] == COS && T[1] == COS && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // cos cos sin sin sin sin
  //   {
  //     I = 0;
  //     double e;
  //     for (int i=0;i<2;i++)
  // 	for (int j=0;j<2;j++)
  // 	  for (int k=0;k<2;k++)
  // 	    for (int l=0;l<2;l++)
  // 	      for (int m=0;m<2;m++)
  // 		{
  // 		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
  // 		  I += MOD(j+k+2)*exp(-fabs(e)/epsilon);
  // 		}
  //     I /= 32.;
  //   }
  // else if (T[0] == SIN && T[1] == SIN && T[2] == SIN && T[3] == SIN && T[4] == SIN && T[5] == SIN ) // sin sin sin sin sin sin
  //   {
  //     I = 0;
  //     double e;
  //     for (int i=0;i<2;i++)
  // 	for (int j=0;j<2;j++)
  // 	  for (int k=0;k<2;k++)
  // 	    for (int l=0;l<2;l++)
  // 	      for (int m=0;m<2;m++)
  // 		{
  // 		  e = (a1 + MOD(i)*a2 + MOD(m)*a3 + MOD(j+m)*a4 + MOD(l+m)*a5 + MOD(l+k+m)*a6);
  // 		  I += MOD(i+j+k+3)*exp(-fabs(e)/epsilon);
  // 		}
  //     I /= 32.;
  //   }
  return I;
}


