///
/// \file main.cpp
/// \brief This is the short description for main.cpp
///
/// This is the long description for main.cpp
///


#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>

#include "tclap/CmdLine.h"
#include "Reader.h"

#include "Utils/wieldTypes.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Eigen/Core"
#include "Eigen/Geometry"
//#include "Faddeeva/Faddeeva.h"

// namespace FCC
// {
// //   f(x)     = \sum_{ijk} C(i,j,k) exp(2 pi i (x1/alpha1 + x2/alpha2 + x3/alpha3))
// //   c(i,j,k) = \int\int\int f(x) exp(- 2 pi i (x1/alpha1 + x2/alpha2 + x3/alpha3)) dx1 dx2 dx3

// static double alpha1 = 1., alpha2=1., alpha3=1.;
// std::complex<double> C(int l, int m, int n)
// {
//   std::complex<double> I(0,1.);
  
//   // complex<double> ret =
//   //   // face centers
//   //   0.5*(exp(I*pi*(double)l) + exp(-I*pi*(double)l) + 
//   // 	 exp(I*pi*(double)m) + exp(-I*pi*(double)m) + 
//   // 	 exp(I*pi*(double)n) + exp(-I*pi*(double)n)) +
//   //   // corners
//   //   0.125*(exp(I*pi*(double)(+l+m+n)) +
//   // 	   exp(I*pi*(double)(+l+m-n)) +
//   // 	   exp(I*pi*(double)(+l-m+n)) +
//   // 	   exp(I*pi*(double)(+l-m-n)) +
//   // 	   exp(I*pi*(double)(-l+m+n)) +
//   // 	   exp(I*pi*(double)(-l+m-n)) +
//   // 	   exp(I*pi*(double)(-l-m+n)) +
//   // 	   exp(I*pi*(double)(-l-m-n)));

//   std::complex<double> ret =
//     1.  +
//     0.25*(exp(I*pi*(double)(+l+m)) +
// 	  exp(I*pi*(double)(+l-m)) +
// 	  exp(I*pi*(double)(-l+m)) +
// 	  exp(I*pi*(double)(-l-m)) +
// 	  exp(I*pi*(double)(+m+n)) +
// 	  exp(I*pi*(double)(+m-n)) +
// 	  exp(I*pi*(double)(-m+n)) +
// 	  exp(I*pi*(double)(-m-n)) +
// 	  exp(I*pi*(double)(+n+l)) +
// 	  exp(I*pi*(double)(+n-l)) +
// 	  exp(I*pi*(double)(-n+l)) +
// 	  exp(I*pi*(double)(-n-l)));

//   if (fabs(imag(ret)) > 1E-5) std::cout << "Imaginary part detected --> =" << imag(ret) << std::endl;
//   return ret/(alpha1*alpha2*alpha3);
// }
// Eigen::Vector3d Alpha(int l, int m, int n)
// {
//   return Eigen::Vector3d(2.*pi*l/alpha1,2.*pi*m/alpha2,2.*pi*n/alpha3);
// }
// }

// double PhiHat(Eigen::Vector3d k,double kT)
// {
//   //cout << k.transpose() << " --- " << exp(-k.squaredNorm()/(kT)) << endl;
//   //cout << "PhiHat: " << k.squaredNorm() << " --- " << exp(-k.squaredNorm()/(1000.)) << endl;
//   //return exp(-k.squaredNorm()/(kT));
//   return sqrt(pi*kT)*exp(-0.25*kT*k.squaredNorm());
// }

// std::complex<double> VHat(Eigen::Vector3d ka, Eigen::Vector3d kb, double sigma, double epsilon)
// {
//   std::complex<double> I(0,1.);
//   // double sigma = 1.;
//   // double epsilon = 0.1;

//   //return 1.;
//   //return exp(-sqrt((ka(0)+kb(0))*(ka(0)+kb(0)) + (ka(1)+kb(1))*(ka(1)+kb(1)))/epsilon);
//   std::complex<double> v1,v2,v1v2,v3;


//   v1v2 =
//     sigma * sigma * pi *
//     exp( - (pow(ka(0)-kb(0),2) + pow(ka(1)-kb(1),2) * sigma * sigma )/ 16.) *
//     exp( - sqrt(pow(ka(0)+kb(0),2) + pow(ka(1)+kb(1),2))/epsilon );
    
//   if (fabs(ka(2)+kb(2)) < 1E-8)
//     v3 =
//       0.5 * sigma * sigma * 
//       (1 - sigma * ka(2) * Faddeeva::Dawson(0.5*ka(2)*sigma));
//   else
//     v3 =
//       sigma *
//       (Faddeeva::Dawson(0.5*ka(2)*sigma) + Faddeeva::Dawson(0.5*kb(2)*sigma)) / (ka(2)+kb(2));
//   return v3;

//   //#define WORKS
// #ifdef  WORKS
//   /*************This seems to work************/ 
//   /*******************************************/ 
//   /**/ std::complex<double> v1 =
//   /**/ 0.5*sigma*epsilon*epsilon*
//   /**/     exp(-0.25*epsilon*epsilon*
//   /**/ 	(ka(0)*ka(0)*sigma*sigma +
//   /**/ 	 kb(0)*kb(0)*sigma*sigma +
//   /**/ 	 ka(0)*ka(0)*epsilon*epsilon +
//   /**/ 	 2.*ka(0)*kb(0) +
//   /**/ 	 kb(0)*kb(0)*epsilon*epsilon)
//   /**/ 	/ (2.*epsilon*epsilon + sigma*sigma))
//   /**/     / (2*epsilon*epsilon + sigma*sigma);
//   /**/ std::complex<double> v2 =
//   /**/ 0.5*sigma*epsilon*epsilon*
//   /**/     exp(-0.25*epsilon*epsilon*
//   /**/ 	(ka(1)*ka(1)*sigma*sigma +
//   /**/ 	 kb(1)*kb(1)*sigma*sigma +
//   /**/ 	 ka(1)*ka(1)*epsilon*epsilon +
//   /**/ 	 2.*ka(1)*kb(1) +
//   /**/ 	 kb(1)*kb(1)*epsilon*epsilon)
//   /**/ 	/ (2.*epsilon*epsilon + sigma*sigma))
//   /**/     / (2*epsilon*epsilon + sigma*sigma);
//   /**/   std::complex<double> v3 = 0.;
//   /**/   if (fabs(ka(2)+kb(2)) < 1E-8)
//   /**/     v3 =
//   /**/       0.5 * sigma * sigma * 
//   /**/       (1 - sigma * ka(2) * Faddeeva::Dawson(0.5*ka(2)*sigma));
//   /**/   else
//   /**/     v3 =
//   /**/       sigma *
//   /**/       (Faddeeva::Dawson(0.5*ka(2)*sigma) + Faddeeva::Dawson(0.5*kb(2)*sigma)) / (ka(2)+kb(2));
//   /**/   return v1*v2*v3 / (pi*epsilon*epsilon);
//   /*******************************************/ 
//   /*******************************************/ 
// #endif

// }

// struct Series
// {
//   Series(int _order):
//     order(_order), C((2*order+1)*(2*order+1)*(2*order+1))
//   {}
//   std::complex<double> &operator()(int i,int j, int k)
//   {
//     return C[ (order+i) + (2*order+1)*(order+j) + (2*order+1)*(2*order+1)*(order+k)];
//   }
//   int order;
//   vector<std::complex<double> > C;
// };

int main(int argc,     
	 char* argv[]) 
{
  // WIELD_EXCEPTION_TRY;

  // //
  // // COMMAND LINE PARSING
  // // 
  // // TCLAP::CmdLine cmd("test");
  // // TCLAP::UnlabeledValueArg<string> argFileName("name", "Path to input file", false, "", "inputfile", cmd);
  // // cmd.parse(argc, argv);
  // // string fileName = argFileName.getValue();
  // Reader::Reader rabbit(argc, argv);
  // int order = rabbit.Read<int>("order",3);
  // double kT = rabbit.Read<double>("kT", 1.);
  // double sigma = rabbit.Read<double>("sigma",1.);
  // double epsilon = rabbit.Read<double>("epsilon",1.);
  // ostringstream filename; filename << "out_order="<<order<<"_kT="<<kT<<"_sigma="<<sigma<<"_epsilon="<<epsilon<<".dat";
  // ofstream out(filename.str().c_str());

  // Series C(order);
  // //vector<std::complex<double> > C((2*order+1)*(2*order+1)*(2*order+1));
  // for (int i=-order; i<=order; i++)
  //   for (int j=-order; j<=order; j++)
  //     for (int k=-order; k<=order; k++)
  // 	{
  // 	  C(i,j,k) = FCC::C(i,j,k) * PhiHat(FCC::Alpha(i,j,k),kT);
  // 	  //cout << "(" << i << " " << j << " " << k << ") " << C(i,j,k) << endl;
  // 	}
  

  // // BLENDER
  // if (rabbit.Find("blender")) {
  //   FILE *f = fopen("voxels.bvox","wb");

  //   int nx=25,ny=25,nz=25,nframes=1;
  //   //float xmin=-1,xmax=1,ymin=-1,ymax=1,zmin=-1,zmax=1;
  //   float xmin=-FCC::alpha1/2.,xmax=FCC::alpha1/2.,ymin=-FCC::alpha1/2.,ymax=FCC::alpha2/2.,zmin=-FCC::alpha1/2.,zmax=FCC::alpha3/2.;
  //   float dx = (xmax-xmin)/(float)(nx-1);    
  //   float dy = (ymax-ymin)/(float)(ny-1);    
  //   float dz = (zmax-zmin)/(float)(nz-1);    

  //   fwrite(&nx,sizeof(int),1,f);
  //   fwrite(&ny,sizeof(int),1,f);
  //   fwrite(&nz,sizeof(int),1,f);
  //   fwrite(&nframes,sizeof(int),1,f);

  //   for (int k=0; k<nz; k++)
  //     for (int j=0; j<ny; j++)
  // 	for (int i=0; i<nx; i++)
  // 	  {
  // 	    float x = xmin + dx*(float)i;
  // 	    float y = ymin + dy*(float)j;
  // 	    float z = zmin + dz*(float)k;

  // 	    //float val = exp(-((x*x) + (y*y) + (z*z))/0.25);
  // 	    std::complex<double> val = 0.;
  // 	    for (int l=-order;l<=order;l++)
  // 	      for (int m=-order;m<=order;m++)
  // 	    	for (int n=-order;n<=order;n++)
  // 	    	  val += C(l,m,n)*exp(std::complex<double>(0.,FCC::Alpha(l,m,n).dot(Eigen::Vector3d(x,y,z))));
  // 	    //val = 2*x;// exp(std::complex<double>(0,2*pi*x/FCC::alpha1));
  // 	    float v = real(val);
  // 	    //cout << v << endl;
  // 	    fwrite(&v,sizeof(float),1,f);
  // 	    WIELD_PROGRESS("Generating file", k, nz, 1);
  // 	  }
  //   //cout << endl;
  //   exit(0);
  // }





  
  // for (double theta=0.;theta<=180.;theta+=0.5)
  //   {
  //     std::complex<double> w(0.,0.);
  //     //Eigen::Matrix3d R = createMatrixFromZX(Vector3d(0,0,1),Vector3d(1,0,0));
  //     Eigen::Matrix3d R = createMatrixFromZX(Eigen::Vector3d(1,-1,0),Eigen::Vector3d(1,1,0));
  //     //Matrix3d R = createMatrixFromZX(Vector3d(1,0,-1),Vector3d(1,1,1));
  //     //Matrix3d R = createMatrixFromZX(Vector3d(1,-1,0),Vector3d(1,1,2));
  //     Eigen::Matrix3d omega1 = createMatrixFromXAngle(+theta/2.)*R;
  //     Eigen::Matrix3d omega2 = createMatrixFromXAngle(-theta/2.)*R;
  //     for (int i=-order; i<=order; i++)
  // 	for (int j=-order; j<=order; j++)
  // 	  for (int k=-order; k<=order; k++)
  // 	    //if (i==0 && j==0 && k==0) continue; else
  // 	      for (int l=-order; l<=order; l++)
  // 		for (int m=-order; m<=order; m++)
  // 		  for (int n=-order; n<=order; n++)
  // 		    //if (l==0 && m==0 && n==0) continue; else
  // 		      {
  // 			std::complex<double> v = VHat(omega1*FCC::Alpha(i,j,k),omega2*FCC::Alpha(l,m,n),sigma,epsilon);
  // 			std::complex<double> dw =
  // 			  C(i,j,k) *
  // 			  v *
  // 			  C(l,m,n);
  // 			w += dw;
  // 		      }
  //     out << theta << " " << w.real() << std::endl;
  //     std::cout << theta << " " << w.real() << std::endl;
  //   }
  // out.close();



  // WIELD_EXCEPTION_CATCH_FINAL;
}


