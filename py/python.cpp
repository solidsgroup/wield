#include <iostream>
// #include <fstream>
// #include <vector>
// #include <fstream>
// #include <stdexcept>
// #include <csignal>
// 
// #include "tclap/CmdLine.h"
// #include "TCLAP/IgnoreArg.h"
// 
// #include "Main/wieldEnergy1D.h"
// #include "Main/wieldEnergy2D.h"
// #include "Main/wieldCSL.h"
// #include "Main/wieldEnergyOffset.h"
// #include "Main/wieldBlenderVoxelData.h"
// #include "Main/wieldVisualizeOR.h"
// #include "Main/wieldEnergySurfaceSphere.h"
// #include "Main/wieldEnergyInterface1D.h"
// #include "Main/wieldEnergyOR1D.h"
// #include "Main/wieldFacet2D.h"
// #include "Utils/wieldExceptions.h"
// #include "Utils/wieldProgress.h"
// 

#include "Reader/Reader.h"
#include "Series/wieldSqrtGaussDirac.h"
#include "Series/wieldGaussDirac.h"
#include "Series/wieldFourierSeries.h"
#include "Integrator/wieldSurface.h"
#include "Integrator/wieldVolume.h"
#include "Optimization/wieldConvexify2D.h"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/eigen.h"

double add(double i, double j) {
    return i + j;
}


double SurfaceGD(Wield::Series::FourierSeries<Wield::Series::GaussDirac> C1,
						 Eigen::Matrix3d R1,
						 Wield::Series::FourierSeries<Wield::Series::GaussDirac> C2,
						 Eigen::Matrix3d R2,
						 double epsilon,
						 double tolerance)
{
	return Wield::Integrator::Surface(C1,R1,C2,R2,epsilon,tolerance);
}

double VolumeSQGD(Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac> C1,
						 Eigen::Matrix3d R1,
						 Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac> C2,
						 Eigen::Matrix3d R2,
						 double epsilon,
						 double tolerance)
{
	return Wield::Integrator::Volume(C1,R1,C2,R2,epsilon,tolerance);
}

std::pair<double,std::vector<Eigen::Vector3d>> Convexify2D(
	std::vector<std::vector<double>> &x,
	std::vector<std::vector<double>> &y,
	std::vector<std::vector<double>> &z,
	std::vector<std::vector<double>> &r,
	std::vector<std::vector<double>> &theta,
	std::vector<std::vector<double>> &w,
	bool threefacet = false
	)
{
	/// Try 2D faceting first

	int sizet = x.size();
	int sizer = x[0].size();

	double wMin = w[0][0];
	Eigen::Vector3d e(0,0,1);
	Eigen::Vector3d n1Min = e, n2Min = e, n3Min = e;
	for (int i1 = 0; i1 < sizet/2; i1++)
	{
		// Positive r: (i,j)
		// Negative r: (i+sizet/2, j)
		//std::cout << "theta = " << theta[i1][0] << std::endl;
		int i2 = i1 + sizet/2;

		if (std::abs(std::fmod(theta[i2][0],180.) - std::fmod(theta[i1][0],180.)) > 1E-8)
			WIELD_EXCEPTION_NEW("Thetas do not match: " << theta[i2][0] << ", " << theta[i1][0]);

		for (int j1 = 1; j1 < sizer; j1++) 
		{
			Eigen::Vector3d n1(x[i1][j1], y[i1][j1], z[i1][j1]);
			for (int j2 = 1; j2 < sizer; j2++)
			{
				Eigen::Vector3d n2(x[i2][j2], y[i2][j2], z[i2][j2]);
				Eigen::Vector2d lambda = Wield::Optimization::ConvexCoefficients(n1,n2,e);
				double wCurr = lambda(0)*w[i1][j1] + lambda(1)*w[i2][j2];
				if (wCurr < wMin)
				{
					wMin = wCurr;
					n1Min = n1;
					n2Min = n2;
				}
			}
		}
		
	}
	if (threefacet)
	{
		for (int t1 = 0; t1 < sizet; t1++)
		{
			if (theta[t1][0] > 180) break;
			std::cout << theta[t1][0] << std::endl;
			for (int t2 = 0; t2 < sizet; t2++)
			{
				if (theta[t2][0] < theta[t1][0]) continue;
				if (theta[t2][0] > theta[t1][0] + 180.) break;
				for (int t3 = 0; t3 < sizet; t3++)
				{
					if (theta[t3][0] < theta[t1][0]+180.) continue;
					if (theta[t3][0] > theta[t2][0]+180.) break;

					for (int j1 = 1; j1 < sizer; j1++)
					{
						Eigen::Vector3d n1(x[t1][j1], y[t1][j1], z[t1][j1]);
						for (int j2 = 1; j2 < sizer; j2++)
						{
							Eigen::Vector3d n2(x[t2][j2], y[t2][j2], z[t2][j2]);
							for (int j3 = 1; j3 < sizer; j3++)
							{
								if (w[t1][j1] > w[0][0] && w[t2][j2] > w[0][0] && w[t3][j3] > w[0][0]) continue;
								Eigen::Vector3d n3(x[t3][j3], y[t3][j3], z[t3][j3]);
								Eigen::Vector3d lambda = Wield::Optimization::ConvexCoefficients(n1,n2,n3,e);
								double wCurr = lambda(0)*w[t1][j1] + lambda(1)*w[t2][j2] + lambda(2)*w[t3][j3];
								if (wCurr < 0) continue;
								if (wCurr < wMin)
								{
									wMin = wCurr;
									n1Min = n1;
									n2Min = n2;
									n3Min = n3;
								}
							}
						}
					}
				}
			}
		}
	}
	std::vector<Eigen::Vector3d> ret;
	ret.push_back(n1Min);
	ret.push_back(n2Min);
	ret.push_back(n3Min);

	std::pair<double,std::vector<Eigen::Vector3d>> pair;
	pair.first = wMin;
	pair.second = ret;
	return pair;
}

Eigen::Vector2d ConvexCoefficients2(Eigen::Vector3d n1, Eigen::Vector3d n2, Eigen::Vector3d e)
{ return Wield::Optimization::ConvexCoefficients(n1,n2,e); }
Eigen::Vector3d ConvexCoefficients3(Eigen::Vector3d n1, Eigen::Vector3d n2, Eigen::Vector3d n3, Eigen::Vector3d e)
{ return Wield::Optimization::ConvexCoefficients(n1,n2,n3,e); }

PYBIND11_MODULE(wield,m) {

	pybind11::class_<Wield::Series::FourierSeries<Wield::Series::GaussDirac>>(m,"CrystalGD")
		.def(pybind11::init<
			 const int, const double, const double, const double,
			 const double, std::vector<double>, std::vector<double>,std::vector<double>,
			 int, int >());

	pybind11::class_<Wield::Series::FourierSeries<Wield::Series::SqrtGaussDirac>>(m,"CrystalSQGD")
		.def(pybind11::init<
			 const int, const double, const double, const double,
			 const double, std::vector<double>, std::vector<double>,std::vector<double>,
			 int, int >());

	m.def("SurfaceGD",&SurfaceGD,"Surface integrate (energy)");
	m.def("VolumeSQGD",&VolumeSQGD,"Volume integrage (CSL)");

	m.def("createMatrixFromAngle",&createMatrixFromAngle,"Surface integrate");
	m.def("createMatrixFromXAngle",&createMatrixFromXAngle,"Generate rotation matrix about x axis");
	m.def("createMatrixFromYAngle",&createMatrixFromYAngle,"Generate rotation matrix about y axis");
	m.def("createMatrixFromZAngle",&createMatrixFromZAngle,"Generate rotation matrix about z axis");
	m.def("createMatrixFromAngle",&createMatrixFromAngle,"Generate rotation matrix about x, y, or z axis");
	m.def("createMatrixFromXY",&createMatrixFromXY,"Generate rotation matrix from x axis and y axis");
	m.def("createMatrixFromYZ",&createMatrixFromYZ,"Generate rotation matrix from y axis and z axis");
	m.def("createMatrixFromZX",&createMatrixFromZX,"Generate rotation matrix from z axis and x axis");
	m.def("createMatrixFromNormalVector",&createMatrixFromNormalVector,"Generate rotation matrix from normal vector");
	m.def("createMatrixFromBungeEulerAngles",&createMatrixFromBungeEulerAngles,"Generate rotation matrix from Bunge Euler Angles");
	m.def("createMatrixFromAxisAngle",&createMatrixFromAxisAngle,"Generate rotation matrix from axis-angle pair");
	m.def("Convexify2D",&Convexify2D,"Convexify 2D");
	m.def("ConvexCoefficients2",&ConvexCoefficients2,"Convex coefficents for second order facets");
	m.def("ConvexCoefficients3",&ConvexCoefficients3,"Convex coefficents for third order facets");
}

						 
