#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;

Matrix3d RotX(double theta)
{
  Matrix3d Omega;
  Omega << 
    1,          0,         0,
    0, cos(theta),sin(theta),
    0,-sin(theta),cos(theta);
  return Omega;
}
Matrix3d RotY(double theta)
{
  Matrix3d Omega;
  Omega <<
    cos(theta), 0, sin(theta),
    0,          1,          0,
    -sin(theta),0, cos(theta);
  return Omega;
}
Matrix3d RotZ(double theta)
{
  Matrix3d Omega;
  Omega << 
    cos(theta), sin(theta), 0,
    -sin(theta),cos(theta), 0,
    0,                   0, 1;
  return Omega;
}

Matrix3d RotXY(Vector3d X, Vector3d Y)
{
  X /= X.norm(); Y /= Y.norm();
  if (fabs(X.dot(Y)) > 1E-6) {cout << "X, Y not orthogonal" << endl; throw(0);}
  Matrix3d Omega;
  Omega.col(0) = X;
  Omega.col(1) = Y;
  Omega.col(2) = X.cross(Y);
  return Omega;
}
Matrix3d RotYZ(Vector3d Y, Vector3d Z)
{
  Y /= Y.norm(); Z /= Z.norm();
  if (fabs(Y.dot(Z)) > 1E-6) {cout << "Y, Z not orthogonal" << endl; throw(0);}
  Matrix3d Omega;
  Omega.col(1) = Y;
  Omega.col(2) = Z;
  Omega.col(0) = Y.cross(Z);
  return Omega;
}
Matrix3d RotZX(Vector3d Z, Vector3d X)
{
  Z /= Z.norm(); X /= X.norm();
  if (fabs(Z.dot(X)) > 1E-6) {cout << "Z, X not orthogonal" << endl; throw(0);}
  Matrix3d Omega;
  Omega.col(2) = Z;
  Omega.col(0) = X;
  Omega.col(1) = Z.cross(X);
  return Omega;
}

