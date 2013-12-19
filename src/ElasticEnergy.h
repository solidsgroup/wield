#include "Eigen/Core"
#include "Eigen/Geometry"
using namespace Eigen;
typedef Matrix<double, 6, 1> Vector6d;

double ElasticEnergy(Vector6d C, Vector6d alpha);
Vector6d DElasticEnergy(Vector6d C, Vector6d alpha);
