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
#include "Series/wieldGaussDirac.h"
#include "Series/wieldFourierSeries.h"
#include "Integrator/wieldSurface.h"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/eigen.h"

double add(double i, double j) {
    return i + j;
}


double SurfaceGaussDirac(Wield::Series::FourierSeries<Wield::Series::GaussDirac> C1,
						 Eigen::Matrix3d R1,
						 Wield::Series::FourierSeries<Wield::Series::GaussDirac> C2,
						 Eigen::Matrix3d R2,
						 double epsilon,
						 double tolerance)
{
	return Wield::Integrator::Surface(C1,R1,C2,R2,epsilon,tolerance);
}

//PYBIND11_MODULE(wield, m) {
//    m.doc() = "pybind11 example plugin"; // optional module docstring
//
//    m.def("add", &add, "A function that adds two numbers");
//}

//Wield::Integrator::Surface<Wield::Series::GaussDirac>;
//int null()
//{
//	&createMatrixFromAngle;
//	Wield::Integrator::Surface<Wield::Series::GaussDirac>;
//}

PYBIND11_MODULE(wield,m) {

	pybind11::class_<Wield::Series::FourierSeries<Wield::Series::GaussDirac>>(m,"Crystal")
		.def(pybind11::init<
			 const int, const double, const double, const double,
			 const double, std::vector<double>, std::vector<double>,std::vector<double>,
			 int, int >());

	m.def("Surface",&SurfaceGaussDirac,"Surface integrate");
	//m.def("Surface",&add,"Surface integrate");
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
	
}

						 
