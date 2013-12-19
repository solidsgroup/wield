#include "ElasticEnergy.h"

double ElasticEnergy(Vector6d C, Vector6d alpha)
{
  double W = 0;
  for (int i=0;i<6;i++)
    W += alpha(i)*C(i)*alpha(i);
  return W;
}
Vector6d DElasticEnergy(Vector6d C, Vector6d alpha)
{
  Vector6d DW;
  for (int i=0;i<6;i++)
    DW(i) = C(i)*alpha(i);
  return DW;
}
