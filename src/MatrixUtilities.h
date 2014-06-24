#ifndef WIELD_MATRIX_UTILITIES
#define WIELD_MATRIX_UTILITIES
#include "Exception.h"

Matrix3d createMatrixFromXAngle(double theta)
{
  Matrix3d Omega;
  Omega << 
    1,          0,         0,
    0, cos(theta),sin(theta),
    0,-sin(theta),cos(theta);
  return Omega;
}
Matrix3d createMatrixFromYAngle(double theta)
{
  Matrix3d Omega;
  Omega <<
    cos(theta), 0, sin(theta),
    0,          1,          0,
    -sin(theta),0, cos(theta);
  return Omega;
}
Matrix3d createMatrixFromZAngle(double theta)
{
  Matrix3d Omega;
  Omega << 
    cos(theta), sin(theta), 0,
    -sin(theta),cos(theta), 0,
    0,                   0, 1;
  return Omega;
}

Matrix3d createMatrixFromXY(Vector3d ex, Vector3d ey)
{
  WIELD_TRY;
  if (ex.cross(ey).norm() < 1E-8)
    WIELD_NEW_EXCEPTION("ez not orthogonal to ey");
  Vector3d ez = ex.cross(ey);
  Matrix3d Omega;
  Omega.row(0) = ex / ex.norm();
  Omega.row(1) = ey / ey.norm();
  Omega.row(2) = ez / ez.norm();
  return Omega;
  WIELD_CATCH;
}

Matrix3d createMatrixFromYZ(Vector3d ey, Vector3d ez)
{
  WIELD_TRY;
  if (ey.cross(ez).norm() < 1E-8)
    WIELD_NEW_EXCEPTION("ey not orthogonal to ez");
  Vector3d ex = ey.cross(ez);
  Matrix3d Omega;
  Omega.row(0) = ex / ex.norm();
  Omega.row(1) = ey / ey.norm();
  Omega.row(2) = ez / ez.norm();
  return Omega;
  WIELD_CATCH;
}

Matrix3d createMatrixFromZX(Vector3d ez, Vector3d ex)
{
  WIELD_TRY;
  if (ez.cross(ex).norm() < 1E-8)
    WIELD_NEW_EXCEPTION("ez not orthogonal to ex");
  Vector3d ey = ez.cross(ex);
  Matrix3d Omega;
  Omega.row(0) = ex / ex.norm();
  Omega.row(1) = ey / ey.norm();
  Omega.row(2) = ez / ez.norm();
  return Omega;
  WIELD_CATCH;
}
#endif
