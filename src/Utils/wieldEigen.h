#ifndef WIELD_UTILS_EIGEN_H
#define WIELD_UTILS_EIGEN_H

#include "Utils/wieldExceptions.h"

#define Success_tmp Success
#undef Success
#undef eigen_assert
#define eigen_assert(A) if (!(A)){ WIELD_EXCEPTION_NEW("Eigen Exception: the conditional (" << #A << ") failed");}
//#define eigen_assert(A) if (!(A)){ cout << "Problem here"<< endl;}

#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Geometry"
#include "eigen3/Eigen/LU"

#define Success Success_tmp
#undef  Success_tmp

#endif

