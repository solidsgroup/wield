#include "Trig6Int.h"
#include "DTrig6Int.h"

int DTrig6IntTest()
{
  int T[6] = {1,1,1,1,1,1};
  double a[6] = {1,1,1,1,1,1};
  double im1,i1;
  double da=0.000001;
  for (int i=0;i<6;i++)
    {
      a[i] += da;
      im1 = Trig6Int(T,a,1);
      a[i] -= 2*da;
      i1 = Trig6Int(T,a,1);
      a[i] += da;
      cout << (im1 - i1) / (2*da) << "     " << DTrig6Int(T,a,1)(i) << endl;
    }  
}
