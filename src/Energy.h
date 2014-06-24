#include "Eigen/Core"
#include "Eigen/Geometry"
#include "ElasticEnergy.h"

#include "SurfaceIntegrate.h"

typedef Matrix<double,6,1> Vector6d;

class Energy
{
 public:
  Energy(int _order,
	 double _C1[4][4][4],
	 double _C2[4][4][4],
	 Vector6d _alpha0,
	 double _epsilon,
	 double _tolerance,
	 string _distribution) :
    order(_order), alpha0(_alpha0), epsilon(_epsilon),tolerance(_tolerance),distribution(_distribution)
  {
    for (int i=0;i<4;i++) 
      for (int j=0; j<4; j++)
	for (int k=0; k<4; k++)
	  {C1[i][j][k] = _C1[i][j][k]; C2[i][j][k] = _C2[i][j][k];}

  };

  int SetR(Matrix3d _R1, Matrix3d _R2)
  {R1 = _R1; R2 = _R2;};
  int SetEpsilon(double _epsilon)
  {epsilon=_epsilon;};

  double W(Vector6d alpha)
  {
    return
      - SurfaceIntegrate(4, C2, C2,
			 R1.col(2), R1.col(0), R2.col(2), R2.col(0),
			 alpha,
			 epsilon, tolerance, distribution);// * (epsilon * sqrt(PI)) * (epsilon * sqrt(PI));
  };

private:
  int order;
  double C1[4][4][4];
  double C2[4][4][4];
  Matrix3d R1;
  Matrix3d R2;
  Vector6d C;
  Vector6d alpha0;
  double epsilon;
  double tolerance;
  string distribution;
};
