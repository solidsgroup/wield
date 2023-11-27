#ifndef WIELD_UTILS_ROTATIONS_H
#define WIELD_UTILS_ROTATIONS_H

#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"
#include "Utils/wieldTypes.h"

Eigen::Matrix3d createMatrixFromXAngle(double theta)
{
  Eigen::Matrix3d Omega;
  Omega << 
    1,          0,         0,
    0, cos(theta*pi/180.),-sin(theta*pi/180.),
    0, sin(theta*pi/180.), cos(theta*pi/180.);
  return Omega;
}
Eigen::Matrix3d createMatrixFromYAngle(double theta)
{
  Eigen::Matrix3d Omega;
  Omega <<
    cos(theta*pi/180.), 0, sin(theta*pi/180.),
    0,          1,          0,
    -sin(theta*pi/180.),0, cos(theta*pi/180.);
  return Omega;
}
Eigen::Matrix3d createMatrixFromZAngle(double theta)
{
  Eigen::Matrix3d Omega;
  Omega << 
    cos(theta*pi/180.), -sin(theta*pi/180.), 0,
    sin(theta*pi/180.),cos(theta*pi/180.), 0,
    0,                   0, 1;
  return Omega;
}
Eigen::Matrix3d createMatrixFromAngle(double theta, char axis)
{
  if (axis=='x' || axis=='X') return createMatrixFromXAngle(theta);
  if (axis=='y' || axis=='Y') return createMatrixFromYAngle(theta);
  if (axis=='z' || axis=='Z') return createMatrixFromZAngle(theta);
  else return Eigen::Matrix3d::Identity();
}
Eigen::Matrix3d createMatrixFromXY(Eigen::Vector3d ex, Eigen::Vector3d ey, double tolerance=1E-8)
{
  WIELD_EXCEPTION_TRY;
  if (fabs(ex.dot(ey)) > tolerance)
    WIELD_EXCEPTION_NEW("ex not orthogonal to ey: ex=[" << ex.transpose() << "]; ey=[" << ey.transpose()<<"]");
  if (ex.norm() < tolerance) WIELD_EXCEPTION_NEW("ex is a zero vector");
  if (ey.norm() < tolerance) WIELD_EXCEPTION_NEW("ey is a zero vector");
  Eigen::Vector3d ez = ex.cross(ey);
  Eigen::Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega.transpose();
  WIELD_EXCEPTION_CATCH;
}

Eigen::Matrix3d createMatrixFromYZ(Eigen::Vector3d ey, Eigen::Vector3d ez, double tolerance=1E-8)
{
  WIELD_EXCEPTION_TRY;
  if (fabs(ey.dot(ez)) > tolerance)
    WIELD_EXCEPTION_NEW("ey not orthogonal to ez: ey=[" << ey.transpose() << "]; ez=[" << ez.transpose()<<"]");
  if (ey.norm() < tolerance) WIELD_EXCEPTION_NEW("ey is a zero vector");
  if (ez.norm() < tolerance) WIELD_EXCEPTION_NEW("ez is a zero vector");
  Eigen::Vector3d ex = ey.cross(ez);
  Eigen::Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega.transpose();
  WIELD_EXCEPTION_CATCH;
}

Eigen::Matrix3d createMatrixFromZX(Eigen::Vector3d ez, Eigen::Vector3d ex, double tolerance=1E-8)
{
  WIELD_EXCEPTION_TRY;
  if (fabs(ez.dot(ex)) > tolerance)
    WIELD_EXCEPTION_NEW("ez not orthogonal to ex: ez=[" << ez.transpose() << "]; ex=[" << ex.transpose()<<"]");
  if (ez.norm() < tolerance) WIELD_EXCEPTION_NEW("ez is a zero vector");
  if (ex.norm() < tolerance) WIELD_EXCEPTION_NEW("ex is a zero vector");
  Eigen::Vector3d ey = ez.cross(ex);
  Eigen::Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega.transpose();
  WIELD_EXCEPTION_CATCH;
}

Eigen::Matrix3d createMatrixFromNormalVector(Eigen::Vector3d n)
{
  WIELD_EXCEPTION_TRY;
  n /= n.norm();
  Eigen::Matrix3d N;
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

Eigen::Matrix3d createMatrixFromBungeEulerAngles(double phi1, double Phi, double phi2)
{
  WIELD_EXCEPTION_TRY;
  Eigen::Matrix3d Z1 = createMatrixFromZAngle(phi1);
  Eigen::Matrix3d X  = createMatrixFromXAngle(Phi);
  Eigen::Matrix3d Z2 = createMatrixFromZAngle(phi2);
  return Z2*X*Z1;
  WIELD_EXCEPTION_CATCH;
}

Eigen::Matrix3d createMatrixFromAxisAngle(Eigen::Vector3d u, double theta)
{
  WIELD_EXCEPTION_TRY;

  Eigen::Matrix3d ux;
  ux <<
    0, -u[2], u[1],
    u[2], 0, -u[0],
    -u[1], u[0], 0;
  Eigen::Matrix3d uu = u*u.transpose();

  return
    (Eigen::Matrix3d::Identity()*cos(theta*pi/180.))
    + (ux*sin(theta*pi/180.))
    + (uu*(1.-cos(theta*pi/180.)));

  WIELD_EXCEPTION_CATCH;
}



#endif
