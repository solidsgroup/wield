#define COS 0
#define SIN 1
#define MOD(a) (double)(1 - 2*((a)%2))
#include "Eigen/Core"
#include "Eigen/Geometry"
#define PI 3.14159265369
using namespace Eigen;
typedef Matrix<double,6,1> Vector6d;
Vector6d DTrig6Int(int *_T, double *_a, double epsilon);
