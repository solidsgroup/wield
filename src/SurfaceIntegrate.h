#ifndef SURFACEINTEGRATE_D
#define SURFACEINTEGRATE_D
#include <iostream>
#include <math.h>
#include "Eigen/Core"
#include "Eigen/Geometry"
#include "Trig6Int.h"
#include "Trig6Int_RS.h"
#include "Trig6Int2_RS.h"
#include "DTrig6Int.h"

#define PI 3.14159265369
using namespace Eigen;
using namespace std;

double SurfaceIntegrate(int order, 
			double Ca[4][4][4], double Cb[4][4][4], 
			Vector3d na3, Vector3d na1, Vector3d nb3, Vector3d nb1, 
			Vector6d alpha,
			//double alpha1, double alpha2, double alpha3, double beta1, double beta2, double beta3,
			double epsilon, double tol,string distribution,double selfenergyfactor);
double SurfaceIntegrate_epsilon(int order, 
				double Ca[4][4][4], double Cb[4][4][4], 
				Vector3d na3, Vector3d na1, Vector3d nb3, Vector3d nb1, 
				Vector6d alpha,
				double epsilon, double tol);
Vector6d DSurfaceIntegrate(int order, 
			   double Ca[4][4][4], double Cb[4][4][4], 
			   Vector3d na3, Vector3d na1, Vector3d nb3, Vector3d nb1, 
			   Vector6d alpha,
			   //double alpha1, double alpha2, double alpha3, double beta1, double beta2, double beta3,
			   double epsilon, double tol);


#endif //SURFACEINTEGRATE_D
