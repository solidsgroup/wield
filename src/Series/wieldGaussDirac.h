#ifndef WIELD_SERIES_GAUSSDIRACMOLLIFIER_H
#define WIELD_SERIES_GAUSSDIRACMOLLIFIER_H

#include "Utils/wieldEigen.h"
#include "Utils/wieldTypes.h"

namespace Wield
{
namespace Series
{

class GaussDirac
{
public:
  GaussDirac(double _sigma): sigma(_sigma) {} 
  std::complex<double> operator () (Eigen::Covector3d k)
  {
    return exp(-sigma*sigma*(k.dot(k))/4.) / sqrt(8*pi*pi*pi);
  }
private:
  double sigma;
};

}
}



#endif
