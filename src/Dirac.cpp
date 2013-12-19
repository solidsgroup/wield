#include "Dirac.h"
double Dirac(double x, double sigma)
{
  return (1/(sigma*sqrt(PI))) * exp(-(x*x) / (sigma*sigma));
}
