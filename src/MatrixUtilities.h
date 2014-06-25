#ifndef WIELD_MATRIX_UTILITIES
#define WIELD_MATRIX_UTILITIES
#include "Exception.h"

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

Matrix3d createMatrixFromXY(Vector3d ex, Vector3d ey)
{
  WIELD_TRY;
  if (fabs(ex.dot(ey)) < 1E-8)
    WIELD_NEW_EXCEPTION("ex not orthogonal to ey: ez=[" << ex.transpose() << "]; ey=[" << ey.transpose()<<"]");
  if (ex.norm() < 1E-8) WIELD_NEW_EXCEPTION("ex is a zero vector");
  if (ey.norm() < 1E-8) WIELD_NEW_EXCEPTION("ey is a zero vector");
  Vector3d ez = ex.cross(ey);
  Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega;
  WIELD_CATCH;
}

Matrix3d createMatrixFromYZ(Vector3d ey, Vector3d ez)
{
  WIELD_TRY;
  if (fabs(ey.dot(ez)) < 1E-8)
    WIELD_NEW_EXCEPTION("ey not orthogonal to ez: ey=[" << ey.transpose() << "]; ez=[" << ez.transpose()<<"]");
  if (ey.norm() < 1E-8) WIELD_NEW_EXCEPTION("ey is a zero vector");
  if (ez.norm() < 1E-8) WIELD_NEW_EXCEPTION("ez is a zero vector");
  Vector3d ex = ey.cross(ez);
  Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega;
  WIELD_CATCH;
}

Matrix3d createMatrixFromZX(Vector3d ez, Vector3d ex)
{
  WIELD_TRY;
  if (fabs(ez.dot(ex)) > 1E-8)
    WIELD_NEW_EXCEPTION("ez not orthogonal to ex: ez=[" << ez.transpose() << "]; ex=[" << ex.transpose()<<"]");
  if (ez.norm() < 1E-8) WIELD_NEW_EXCEPTION("ez is a zero vector");
  if (ex.norm() < 1E-8) WIELD_NEW_EXCEPTION("ex is a zero vector");
  Vector3d ey = ez.cross(ex);
  Matrix3d Omega;
  Omega.col(0) = ex / ex.norm();
  Omega.col(1) = ey / ey.norm();
  Omega.col(2) = ez / ez.norm();
  return Omega;
  WIELD_CATCH;
}
#endif
