#ifndef WIELD_SERIES_SQRTGAUSSDIRACMOLLIFIER_H
#define WIELD_SERIES_SQRTGAUSSDIRACMOLLIFIER_H

#include "Utils/wieldEigen.h"
#include "Utils/wieldTypes.h"

namespace Wield
{
namespace Series
{

class SqrtGaussDirac
{
public:
  SqrtGaussDirac(double _sigma): 
    sigma(_sigma),
    coeff(sqrt(sigma*sigma*sigma) / sqrt(sqrt(8.0)) / sqrt(sqrt(pi * pi * pi))) {}
  std::complex<double> operator () (Eigen::Covector3d k)
  {
    return coeff * exp(- (sigma*sigma/4.) * k.squaredNorm());
    //return exp(-sigma*sigma*(k.dot(k))/4.) / sqrt(8*pi*pi*pi);
  }
private:
  double sigma;
  double coeff;
};

}
}



#endif
