#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"

Eigen::Matrix3d RotX(double theta)
{
  Eigen::Matrix3d Omega;
  Omega << 
    1,          0,         0,
    0, cos(theta),sin(theta),
    0,-sin(theta),cos(theta);
  return Omega;
}
Eigen::Matrix3d RotY(double theta)
{
  Eigen::Matrix3d Omega;
  Omega <<
    cos(theta), 0, sin(theta),
    0,          1,          0,
    -sin(theta),0, cos(theta);
  return Omega;
}
Eigen::Matrix3d RotZ(double theta)
{
  Eigen::Matrix3d Omega;
  Omega << 
    cos(theta), sin(theta), 0,
    -sin(theta),cos(theta), 0,
    0,                   0, 1;
  return Omega;
}

Eigen::Matrix3d RotXY(Eigen::Vector3d X, Eigen::Vector3d Y)
{
  X /= X.norm(); Y /= Y.norm();
  if (fabs(X.dot(Y)) > 1E-6) {cout << "X, Y not orthogonal" << endl; throw(0);}
  Eigen::Matrix3d Omega;
  Omega.col(0) = X;
  Omega.col(1) = Y;
  Omega.col(2) = X.cross(Y);
  return Omega;
}
Eigen::Matrix3d RotYZ(Eigen::Vector3d Y, Eigen::Vector3d Z)
{
  Y /= Y.norm(); Z /= Z.norm();
  if (fabs(Y.dot(Z)) > 1E-6) {cout << "Y, Z not orthogonal" << endl; throw(0);}
  Eigen::Matrix3d Omega;
  Omega.col(1) = Y;
  Omega.col(2) = Z;
  Omega.col(0) = Y.cross(Z);
  return Omega;
}
Eigen::Matrix3d RotZX(Eigen::Vector3d Z, Eigen::Vector3d X)
{
  Z /= Z.norm(); X /= X.norm();
  if (fabs(Z.dot(X)) > 1E-6) {cout << "Z, X not orthogonal" << endl; throw(0);}
  Eigen::Matrix3d Omega;
  Omega.col(2) = Z;
  Omega.col(0) = X;
  Omega.col(1) = Z.cross(X);
  return Omega;
}

