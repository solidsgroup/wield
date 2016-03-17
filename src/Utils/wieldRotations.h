#ifndef WIELD_UTILS_ROTATIONS_H
#define WIELD_UTILS_ROTATIONS_H

#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"
#include "Utils/wieldTypes.h"

using namespace std;
Matrix3d createMatrixFromXAngle(double theta)
{
  Matrix3d Omega;
  Omega << 
    1,          0,         0,
    0, cos(theta*pi/180.),sin(theta*pi/180.),
    0,-sin(theta*pi/180.),cos(theta*pi/180.);
  return Omega;
}
Matrix3d createMatrixFromYAngle(double theta)
{
  Matrix3d Omega;
  Omega <<
    cos(theta*pi/180.), 0, sin(theta*pi/180.),
    0,          1,          0,
    -sin(theta*pi/180.),0, cos(theta*pi/180.);
  return Omega;
}
Matrix3d createMatrixFromZAngle(double theta)
{
  Matrix3d Omega;
  Omega << 
    cos(theta*pi/180.), sin(theta*pi/180.), 0,
    -sin(theta*pi/180.),cos(theta*pi/180.), 0,
    0,                   0, 1;
  return Omega;
}
Matrix3d createMatrixFromAngle(double theta, char axis)
{
  if (axis=='x' || axis=='X') return createMatrixFromXAngle(theta);
  if (axis=='y' || axis=='Y') return createMatrixFromYAngle(theta);
  if (axis=='z' || axis=='Z') return createMatrixFromZAngle(theta);
  else return Matrix3d::Identity();
}
Matrix3d createMatrixFromXY(Eigen::Vector3d ex, Eigen::Vector3d ey)
{
  WIELD_EXCEPTION_TRY;
  if (fabs(ex.dot(ey)) > 1E-8)
    WIELD_EXCEPTION_NEW("ex not orthogonal to ey: ex=[" << ex.transpose() << "]; ey=[" << ey.transpose()<<"]");
  if (ex.norm() < 1E-8) WIELD_EXCEPTION_NEW("ex is a zero vector");
  if (ey.norm() < 1E-8) WIELD_EXCEPTION_NEW("ey is a zero vector");
  Eigen::Vector3d ez = ex.cross(ey);
  Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega;
  WIELD_EXCEPTION_CATCH;
}

Matrix3d createMatrixFromYZ(Eigen::Vector3d ey, Eigen::Vector3d ez)
{
  WIELD_EXCEPTION_TRY;
  if (fabs(ey.dot(ez)) > 1E-8)
    WIELD_EXCEPTION_NEW("ey not orthogonal to ez: ey=[" << ey.transpose() << "]; ez=[" << ez.transpose()<<"]");
  if (ey.norm() < 1E-8) WIELD_EXCEPTION_NEW("ey is a zero vector");
  if (ez.norm() < 1E-8) WIELD_EXCEPTION_NEW("ez is a zero vector");
  Eigen::Vector3d ex = ey.cross(ez);
  Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega;
  WIELD_EXCEPTION_CATCH;
}

Matrix3d createMatrixFromZX(Eigen::Vector3d ez, Eigen::Vector3d ex)
{
  WIELD_EXCEPTION_TRY;
  if (fabs(ez.dot(ex)) > 1E-8)
    WIELD_EXCEPTION_NEW("ez not orthogonal to ex: ez=[" << ez.transpose() << "]; ex=[" << ex.transpose()<<"]");
  if (ez.norm() < 1E-8) WIELD_EXCEPTION_NEW("ez is a zero vector");
  if (ex.norm() < 1E-8) WIELD_EXCEPTION_NEW("ex is a zero vector");
  Eigen::Vector3d ey = ez.cross(ex);
  Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega;
  WIELD_EXCEPTION_CATCH;
}

Matrix3d createMatrixFromNormalVector(Eigen::Vector3d n)
{
  WIELD_EXCEPTION_TRY;
  n /= n.norm();
  Matrix3d N;
  Eigen::Vector3d nOrth(1,0,0);
  if (nOrth.cross(n).norm() < 1E-4) nOrth << 0, 1, 0; // off chance that n is ex
  N.col(2) = n;    
  N.col(0) = nOrth - (nOrth.dot(n))*n;
  N.col(1) = N.col(2).cross(N.col(0)); // Problem occurs here
  N.col(0) /= N.col(0).norm();
  N.col(1) /= N.col(1).norm();
  N.col(2) /= N.col(2).norm();
  return N;
  WIELD_EXCEPTION_CATCH;
}

Matrix3d createMatrixFromBungeEulerAngles(double phi1, double Phi, double phi2)
{
  WIELD_EXCEPTION_TRY;
  Matrix3d Z1 = createMatrixFromZAngle(phi1);
  Matrix3d X  = createMatrixFromXAngle(Phi);
  Matrix3d Z2 = createMatrixFromZAngle(phi2);
  return Z2*X*Z1;
  WIELD_EXCEPTION_CATCH;
}



#endif
