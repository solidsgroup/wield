#include <iostream>
#include <cstdlib>
#include <vector>

#include "Utils/VTK/wieldVTK.h"

std::vector<double> DW(std::vector<double> x,
		       std::vector<double> y)
{
  std::vector<double> dw;
  
  for (int i=0; i<100; i++)
    {
      dw.push_back(2*(y[i+1]-y[i])/(x[i+1]-x[i]) + 2*y[i]*(x[i+1]-x[i]));
    }
  dw[0] = 0;
  dw[100] = 0;
  return dw;
}


int main(int argc, char ** argv)
{
  srand(time(NULL));

  std::vector<double> x,y;
  Wield::Utils::VTK::PlotLine plotter;

  for (int i=0; i<=100; i++)
    {
      x.push_back((double)i/100.);
      y.push_back((double)rand()/(double)RAND_MAX);
    }
  y[0] = 0; y[100] = 0;

  while(1)
    {
      std::vector<double> dw = DW(x,y);
      double norm; for (int i=0; i<=100; i++) norm += dw[i]*dw[i]; 
      cout << norm << endl;
      if (norm < 1E-5) break;
      for (int i=0;i<=100;i++)
	y[i] -= 0.001*dw[i];
      plotter.SetData(x,y,false);
    }


  plotter.SetData(x,y,true);

}
