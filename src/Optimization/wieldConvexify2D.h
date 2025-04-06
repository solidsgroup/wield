///
/// \file wieldConvexify2D.h
/// \brief Compute the 2D geometric relaxation envelope
///
/// Compute 
/// \f[W_c(\mathbf{e}) =  \inf_{\mathbf{n}_1,\mathbf{n}_2,\mathbf{n}_3}\bigg(\lambda_1 W(\mathbf{n}_1) + \lambda_2 W(\mathbf{n}_2 + \lambda_3 W(\mathbf{n}_3)\bigg) \f]
/// subject to
/// \f[\lambda_1\mathbf{n}_1 + \lambda_2\mathbf{n}_2 + \lambda_2\mathbf{n}_2 = \mathbf{e}\f]
///
#ifndef WIELD_OPTIMIZATION_CONVEXIFY2D_H
#define WIELD_OPTIMIZATION_CONVEXIFY2D_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <pthread.h>

#include "Reader/Reader.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldEigen.h"

static inline
bool ThetaInRange(double theta, double theta1, double theta2)
{
    WIELD_EXCEPTION_TRY;
    if (theta  < 0 || theta  >= 360.) WIELD_EXCEPTION_NEW("Invalid theta  = " << theta);
    if (theta1 < 0 || theta1 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta1 = " << theta1);
    if (theta2 < 0 || theta2 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta2 = " << theta2);
 

    if (theta1 > 180) theta1 -= 180.;
    else theta1 += 180.;
    if (theta2 > 180) theta2 -= 180.;
    else theta2 += 180.;

    if (fabs(theta2-theta1) < 180)
    {
      
        if (theta2 >= theta && theta >= theta1) return true;
        if (theta1 >= theta && theta >= theta2) return true;
    }
    else
    {
        if (theta < theta1 && theta < theta2) return true;
        if (theta > theta1 && theta > theta2) return true;
    }

    return false;
    WIELD_EXCEPTION_CATCH;
}

static inline
bool PolarOpposites(double theta1, double theta2)
{
    WIELD_EXCEPTION_TRY;
    if (theta1 < 0 || theta1 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta1 = " << theta1);
    if (theta2 < 0 || theta2 >= 360.) WIELD_EXCEPTION_NEW("Invalid theta2 = " << theta2);

    if (fabs(180-fabs(theta2-theta1)) < 1E-8) return true;
    else return false;
    WIELD_EXCEPTION_CATCH;
}

namespace Wield
{
namespace Optimization
{

template<int facetOrder>
struct ConvexifyData2D;

template<>
struct ConvexifyData2D<3>
{
    int index;
    int numThreads;
    int maxFacetOrder;
    std::vector<double> *x;
    std::vector<double> *y;
    std::vector<double> *z;
    std::vector<double> *r;
    std::vector<double> *theta;
    std::vector<double> *w;
    double wMin;
    Eigen::Vector3d lambdaMin;
    Eigen::Vector3d n1Min;
    Eigen::Vector3d n2Min;
    Eigen::Vector3d n3Min;
    int coarsen;
    double searchRadius;
    int refining;
    bool symmetricY;
};


template<int facetOrder>
void *Convexify2D(void *args);

static inline
Eigen::Vector2d ConvexCoefficients(Eigen::Vector3d n1, Eigen::Vector3d n2, Eigen::Vector3d e)
{
	double inf = abs(std::numeric_limits<double>::infinity());
	Eigen::Vector2d lambda(inf,inf);

	//double det = n1[0]*n2[1] - n2[0]*n1[1];
	//if (fabs(det) < 1E-8) return lambda;

	//lambda(0) = ( n2(1)*e(0) - n2(0)*e(1)) / det;
	//lambda(1) = (-n1(1)*e(0) + n1(0)*e(1)) / det;
	
	double theta1 = asin(sqrt(n1(0)*n1(0) + n1(1)*n1(1)));
	double theta2 = -asin(sqrt(n2(0)*n2(0) + n2(1)*n2(1)));
	double det = sin(theta1-theta2);
	if (fabs(det)<1E-5) return lambda;
	lambda(0) = -sin(theta2)/det;
	lambda(1) = sin(theta1)/det;
	return lambda;
}
static inline
Eigen::Vector3d ConvexCoefficients(Eigen::Vector3d n1, Eigen::Vector3d n2, Eigen::Vector3d n3, Eigen::Vector3d e)
{
	double inf = abs(std::numeric_limits<double>::infinity());
	Eigen::Vector3d lambda(inf,inf,inf);
	double det = 
		+ n1[0]*n2[1]*n3[2] 
		+ n1[1]*n2[2]*n3[0]
		+ n1[2]*n2[0]*n3[1]
		- n1[0]*n2[2]*n3[1]
		- n1[1]*n2[0]*n3[2]
		- n1[2]*n2[1]*n3[0];
	if (fabs(det) < 1E-8) return lambda;
	lambda(0) = 
		(+  e[0]*n2[1]*n3[2] 
		 + n2[0]*n3[1]* e[2]
		 + n3[0]* e[1]*n2[2]
		 -  e[0]*n3[1]*n2[2]
		 - n2[0]* e[1]*n3[2]
		 - n3[0]*n2[1]* e[2] )/det;
	lambda(1) = 
		(+ n1[0]* e[1]*n3[2]
		 +  e[0]*n3[1]*n1[2]
		 + n3[0]*n1[1]* e[2]
		 - n1[0]*n3[1]* e[2]
		 -  e[0]*n1[1]*n3[2]
		 - n3[0]* e[1]*n1[2] )/det;
	lambda(2) = 
		(+ n1[0]*n2[1]* e[2]
		 + n2[0]* e[1]*n1[2]
		 +  e[0]*n1[1]*n2[2]
		 - n1[0]* e[1]*n2[2]
		 - n2[0]*n1[1]* e[2]
		 -  e[0]*n2[1]*n1[2])/det;
	if (lambda(0) < 0 || lambda(1) < 0 || lambda(2) < 0) lambda = Eigen::Vector3d(inf,inf,inf);
	return lambda;
}




void Convexify2D(unsigned int index,
				 int numThreads,
				 int maxFacetOrder,
				 std::vector<double> &x,
				 std::vector<double> &y,
				 std::vector<double> &z,
				 std::vector<double> &r,
				 std::vector<double> &theta,
				 std::vector<double> &w,
				 double &wMin,
				 Eigen::Vector3d &lambdaMin,
				 Eigen::Vector3d &n1Min,
				 Eigen::Vector3d &n2Min,
				 Eigen::Vector3d &n3Min,
				 int coarsen,
				 double searchRadius,
				 int refining,
				 bool symmetricY) 
{
    WIELD_EXCEPTION_TRY;

    Eigen::Vector3d n3MinOld=n3Min;

    if (x.size() != y.size() || y.size() != z.size() || z.size() != w.size())
        WIELD_EXCEPTION_NEW("x, y, z, w not the same size: x.size()=" <<x.size() << ", y.size()="<<y.size() << ", z.size()="<<z.size()<<", w.size() =" << w.size());

    Eigen::Vector3d e; e << 0, 0, 1; 

    Eigen::Vector3d lambda;
    Eigen::Matrix3d n;
    for (unsigned int i =0; i < x.size(); i++) 
    {
        Eigen::Vector3d n1(x[i], y[i], z[i]);
        if (symmetricY) if (fabs(x[i]) > 1E-8) continue;
        //if ( i%coarsen != 0 ) continue;
        if ( i%numThreads != index ) continue;
        //if (refining) if (sqrt((n1MinOld[0]-n1[0])*(n1MinOld[0]-n1[0]) + (n1MinOld[1]-n1[1])*(n1MinOld[1]-n1[1])) > searchRadius) continue;
      
        if (fabs(r[i])<1E-8)
        {
            if (w[i] < wMin)
            {
                //cout << __LINE__ << ": " << w[i] << " --> " << wMin << endl;
                wMin = w[i];
                lambdaMin << 1, 0, 0;
                n1Min = n1;
                n2Min << 0,0,0;
                n3Min << 0,0,0;
            }
            continue;
        }
        // cout << "min=" << wMin << endl;
        //for (int j =i+1; j < x.size(); j++) 
        for (unsigned int j = 0; j < x.size(); j++) 
        {
            if (j==i) continue;
            if (symmetricY) if (x[j] > 1E-8) continue; // only consider x<0
            Eigen::Vector3d n2(x[j], y[j], z[j]);
	  
            //if ( j%coarsen != 0 ) continue;
            //if (r[j] < 1E-8) continue;
            //if (refining) if (fabs(n2MinOld[0]-n2[0]) > searchRadius || fabs(n2MinOld[1]-n2[1]) > searchRadius ) continue; // taxicab norm


            if (PolarOpposites(theta[i],theta[j]))
            {
                if (w[i] > wMin && w[j] > wMin) continue;

                Eigen::Vector2d lambda = ConvexCoefficients(n1,n2,e);
                double wCurrent = fabs(lambda[0])*w[i] + fabs(lambda[1])*w[j];
                if (lambda[0] + lambda[1] < 1.) continue;
                if (wCurrent < wMin)
                {
                    //cout << __LINE__ << ": " << wCurrent << " --> " << wMin << endl;

                    wMin = wCurrent;
                    // if (index==0) cout << lambda.transpose() << endl;
                    lambdaMin << lambda[0], lambda[1], 0;
                    n1Min = n1;
                    n2Min = n2;
                    n3Min << 0,0,0;
                    continue;
                }
            }
            else if (maxFacetOrder >= 3)
            {
                if (symmetricY)
                {
                    //if (index==0) cout << lambda.transpose() << endl;
                    //if ((y[i]>0 && y[j] > 0) || (y[i] < 0 && y[j] < 0)) {cout << __LINE__<< endl;continue;}
                    Eigen::Vector3d n3(-x[j], y[j], z[j]);
                    // double theta3 = 0.; 
                    // if (y[j] > 0) theta3 = 180 - theta[j];
                    // else theta3 = 
                    Eigen::Vector3d lambda = ConvexCoefficients(n1, n2, n3, e); 
                    //cout << lambda.transpose() << endl;
                    //cout << (lambda[0]*n1 + lambda[1]*n2 + lambda[2]*n3).transpose() << endl;
                    double wCurrent = lambda[0]*w[i] + lambda[1]*w[j] + lambda[2]*w[j]; 
                    //cout << "(" << n1.transpose() << ") (" << n2.transpose() << ") (" << n3.transpose() << ") : " << lambda.transpose() << endl; 
                    if (lambda[0] < 0 || lambda[1] < 0 || lambda[2] < 0) {continue;}  
                    if (lambda[0] + lambda[1] + lambda[2] < 1.) continue;
                    if (wCurrent < wMin)
                    {
                        //cout << __LINE__ << ": " << wCurrent << " --> " << wMin << ",   " << lambda << endl;
                        wMin = wCurrent;
                        lambdaMin << lambda[0],lambda[1],lambda[2];
                        n1Min = n1;
                        n2Min = n2;
                        n3Min = n3;
                        continue;
                    }
                }
                else
                {

                    for (unsigned int k = j+1; k < x.size(); k++) 
                    {
                        Eigen::Vector3d n3(x[k], y[k], z[k]);
		  
                        if (symmetricY) if (fabs(x[k]+x[j]) > 1E-8 || fabs(y[k]-y[j]) > 1E-8) continue;
                        if (k%coarsen != 0 ) continue; 
                        if (r[k] < 1E-8) continue; // if this point is the origin, this case has already been considered
                        if (refining) if (sqrt((n3MinOld[0]-n3[0])*(n3MinOld[0]-n3[0]) + (n3MinOld[1]-n3[1])*(n3MinOld[1]-n3[1])) > searchRadius) continue; // small radius
                        if (!ThetaInRange(theta[k],theta[i],theta[j])) continue; // is the origin in the feasible set?
                        if (PolarOpposites(theta[i],theta[k]) || PolarOpposites(theta[j],theta[k])) continue; // 2d faceting, will get caught later
                        if (w[i]>wMin && w[j]>wMin && w[k]>wMin) continue; // pointless! this will definitely be greater than wMin
		  
                        Eigen::Vector3d lambda = ConvexCoefficients(n1, n2, n3, e);
                        double wCurrent = lambda[0]*w[i] + lambda[1]*w[j] + lambda[2]*w[k];

                        if (wCurrent < wMin)
                        {
                            //cout << __LINE__ << ": " << w[i] << " --> " << wMin << endl;
                            wMin = wCurrent;
                            lambdaMin << lambda[0],lambda[1],lambda[2];
                            n1Min = n1;
                            n2Min = n2;
                            n3Min = n3;
                            continue;
                        }
                    }
                }
            }
        }
        if (index == 0) WIELD_PROGRESS("Faceting", i, x.size(), 1);
    }
    if (index == 0) {WIELD_PROGRESS("Faceting", x.size(), x.size(), 1); std::cout << std::endl;}
    WIELD_EXCEPTION_CATCH;
}

template<>
void *Convexify2D<3>(void *args) 
{
    WIELD_EXCEPTION_TRY;
    int index                  =   ((ConvexifyData2D<3> *)(args))->index;
    int numThreads             =   ((ConvexifyData2D<3> *)(args))->numThreads;
    int maxFacetOrder          =   ((ConvexifyData2D<3> *)(args))->maxFacetOrder;
    std::vector<double> &x          = *(((ConvexifyData2D<3> *)(args))->x);
    std::vector<double> &y          = *(((ConvexifyData2D<3> *)(args))->y);
    std::vector<double> &z          = *(((ConvexifyData2D<3> *)(args))->z);
    std::vector<double> &r          = *(((ConvexifyData2D<3> *)(args))->r);
    std::vector<double> &theta      = *(((ConvexifyData2D<3> *)(args))->theta);
    std::vector<double> &w          = *(((ConvexifyData2D<3> *)(args))->w);
    double &wMin               =   ((ConvexifyData2D<3> *)(args))->wMin;
    Eigen::Vector3d &lambdaMin =   ((ConvexifyData2D<3> *)(args))->lambdaMin;
    Eigen::Vector3d &n1Min     =   ((ConvexifyData2D<3> *)(args))->n1Min;
    Eigen::Vector3d &n2Min     =   ((ConvexifyData2D<3> *)(args))->n2Min;
    Eigen::Vector3d &n3Min     =   ((ConvexifyData2D<3> *)(args))->n3Min;
    int coarsen                =   ((ConvexifyData2D<3> *)(args))->coarsen;
    double searchRadius        =   ((ConvexifyData2D<3> *)(args))->searchRadius;
    int refining               =   ((ConvexifyData2D<3> *)(args))->refining;
    bool symmetricY            =   ((ConvexifyData2D<3> *)(args))->symmetricY;

    Convexify2D(index,numThreads,maxFacetOrder,x,y,z,r,theta,w,wMin,lambdaMin,
                n1Min,n2Min,n3Min,coarsen,searchRadius,refining,symmetricY);
    pthread_exit(args);
    WIELD_EXCEPTION_CATCH;
}


//void Convexify2D(int index,
//				 int numThreads,
//				 int maxFacetOrder,
//				 std::vector<double> &x,
//				 std::vector<double> &y,
//				 std::vector<double> &z,
//				 std::vector<double> &r,
//				 std::vector<double> &theta,
//				 std::vector<double> &w,
//				 double &wMin,
//				 Eigen::Vector3d &lambdaMin,
//				 Eigen::Vector3d &n1Min,
//				 Eigen::Vector3d &n2Min,
//				 Eigen::Vector3d &n3Min,
//				 int coarsen,
//				 double searchRadius,
//				 int refining,
//				 bool symmetricY) 
//{
//  WIELD_EXCEPTION_TRY;
//  WIELD_EXCEPTION_CATCH;
//}



}
}


#endif
