#ifndef WIELD_TYPE_DEFINITIONS_H
#define WIELD_TYPE_DEFINITIONS_H

const double pi = 3.14159265358979323846264338327950288419716939937510582;


#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldCosSeries.h"

namespace Eigen
{
typedef Matrix<double,3,1> Vector3d;
}

namespace Reader
{
template<> struct Interpreter<Eigen::Vector3d >
{
  void operator() (const string varUnparsed, Eigen::Vector3d *varParsed)
  {
    WIELD_EXCEPTION_TRY;
    std::istringstream iss(varUnparsed); 
    string token;
    for (unsigned int i=0;i<3;i++)
      {
	iss >> token;
	(*varParsed)(i,0) = EvaluateMath(token);
      }
    WIELD_EXCEPTION_CATCH_MSG("Error parsing Vector3d: " << varUnparsed);
  }
};
}

typedef Matrix<double,6,1> Vector6d;
namespace Reader
{
template<> struct Interpreter<Vector6d >
{
  void operator() (const string varUnparsed, Vector6d *varParsed)
  {
    WIELD_EXCEPTION_TRY;
    std::istringstream iss(varUnparsed); 
    string token;
    for (unsigned int i=0;i<6;i++)
      {
	iss >> token;
	(*varParsed)(i,0) = EvaluateMath(token);
      }
    WIELD_EXCEPTION_CATCH_MSG("Error parsing Vector6d: " << varUnparsed);
  }
};
}

/*
class CosSeries
{
public:
  CosSeries(): order(4)
  {
    C = (double *)malloc(order*order*order*sizeof(double));
    for (unsigned int i=0;i<order*order*order; i++) C[i] = 0;
  }
  CosSeries(unsigned int _order): order(_order)
  {
    C = (double *)malloc(order*order*order*sizeof(double));
    for (unsigned int i=0;i<order*order*order; i++) C[i] = 0;
  }
  double & operator() (unsigned int i, unsigned int j, unsigned int k)
  {
    return C[order*order*i + order*j + k];
  }
  unsigned int order;
  double alpha1; ///<@brief Hello world
  double alpha2; 
  double alpha3;
private:
  double *C;
};


template<> struct Interpreter<Wield::Series::CosSeries>
{
  void operator() (const string varUnparsed, Wield::Series::CosSeries *varParsed)
  {
    std::istringstream iss(varUnparsed); 
    string token;
    int order = varParsed->order;
    for (unsigned int i=0;i<order;i++)
      for (unsigned int j=0;j<order;j++)
	for (unsigned int k=0;k<order;k++)
	  {
	    iss >> token;
	    (*varParsed)(i,j,k) = EvaluateMath(token);
	  }
  }
};

*/



#endif
