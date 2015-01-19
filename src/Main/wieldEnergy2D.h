#ifndef WIELD_MAIN_ENERGY2D_H
#define WIELD_MAIN_ENERGY2D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <fstream>
#include <stdexcept>
#include <pthread.h>

#include "Reader.h"

#include "Utils/wieldExceptions.h"
#include "Series/wieldFourierSeries.h"
#include "Utils/VTK/wieldVTK.h"
#include "Integrator/wieldSurface.h"

using namespace std;

namespace Wield
{
namespace Main
{
typedef struct {
  int index,numThreads;
  double epsilon, tolerance;
  Matrix3d rot1, rot2;
  Wield::Series::FourierSeries *C1, *C2;
  vector<double> *X, *Y, *Z, *W;
} Energy2D_t;

void *Energy2D(void *args);
void Energy2D(Reader::Reader &reader, int numThreads=1)
{
  WIELD_EXCEPTION_TRY;
  
  Wield::Series::FourierSeries
    C1(reader.Read<int>("Order1"),
       reader.Read<double>("AlphaX1"),
       reader.Read<double>("AlphaY1"),
       reader.Read<double>("AlphaZ1"),
       reader.Read<double>("Sigma1"),
       reader.Read<vector<double> >("X1"),
       reader.Read<vector<double> >("Y1"),
       reader.Read<vector<double> >("Z1"));

  Wield::Utils::VTK::renderCrystal
    (Wield::Utils::VTK::drawCrystal
     (C1,Matrix3d::Identity(),Matrix3d::Identity(),
      -C1.alphaX,-C1.alphaY,-C1.alphaZ,
      +C1.alphaX,+C1.alphaY,+C1.alphaZ,
      reader.Read<double>("Resolution",100.)));
      
				   
				   

  Wield::Series::FourierSeries
    C2(reader.Read<int>("Order2"),
       reader.Read<double>("AlphaX2"),
       reader.Read<double>("AlphaY2"),
       reader.Read<double>("AlphaZ2"),
       reader.Read<double>("Sigma2"),
       reader.Read<vector<double> >("X2"),
       reader.Read<vector<double> >("Y2"),
       reader.Read<vector<double> >("Z2"));

  Matrix3d
    rot1 =
    createMatrixFromZAngle(reader.Read<double>("RotZ1",0.))*
    createMatrixFromYAngle(reader.Read<double>("RotY1",0.))*
    createMatrixFromXAngle(reader.Read<double>("RotX1",0.)),
    rot2 = 
    createMatrixFromZAngle(reader.Read<double>("RotZ2",0.))*
    createMatrixFromYAngle(reader.Read<double>("RotY2",0.))*
    createMatrixFromXAngle(reader.Read<double>("RotX2",0.));

  double thetaMin = reader.Read<double>("ThetaMin",0.);
  double thetaMax = reader.Read<double>("ThetaMax",360.);
  double dTheta   = reader.Read<double>("DTheta",1.);
  double rMin = reader.Read<double>("RMin",0.);
  double rMax = reader.Read<double>("RMax",1.);
  double dR   = reader.Read<double>("DR",.05);
  vector<double> X,Y,Z;
  for (double theta = thetaMin; theta <= thetaMax; theta += dTheta) 
    for (double r = rMin; r <= rMax; r += dR) 
      {
	X.push_back(r*cos(theta*pi/180.));
	Y.push_back(r*sin(theta*pi/180.));
	Z.push_back(sqrt(1.-(r*r)));
      }
  vector<double> W(X.size());
  
  vector<Energy2D_t> data(numThreads);
  vector<pthread_t> threads(numThreads);
  for (int i=0; i<numThreads; i++)
    {
      data[i].index     = i;
      data[i].numThreads= numThreads;
      data[i].epsilon   = reader.Read<double>("Epsilon",1.);
      data[i].tolerance = reader.Read<double>("Tolerance",1.);
      data[i].rot1      = rot1;
      data[i].rot2      = rot2;
      data[i].C1        = &C1;
      data[i].C2        = &C2;
      data[i].X         = &X;
      data[i].Y         = &Y;
      data[i].Z         = &Z;
      data[i].W         = &W;
      int errorCode = pthread_create(&threads[i], NULL, Energy2D, (void*)(&data[i]));
      if (errorCode)
	WIELD_EXCEPTION_NEW("Error starting thread #" << i << ": errorCode = " << errorCode);
    }

  for (int i=0; i<numThreads; i++)
    {
      int errorCode = pthread_join(threads[i],NULL);
      if (errorCode)
	WIELD_EXCEPTION_NEW("Error starting thread #" << i << ": errorCode = " << errorCode);
    }

  ofstream out(reader.Read<string>("OutFile").c_str());
  for (int i=0; i<X.size(); i++)
    out << X[i] << " " << Y[i] << " " << Z[i] << " " << W[i] << endl;
  out.close();
  
  WIELD_EXCEPTION_CATCH;
}
void *Energy2D(void *args)
{
  int index                        = ((Energy2D_t*)args)->index;
  int numThreads                   = ((Energy2D_t*)args)->numThreads;
  double epsilon                   = ((Energy2D_t*)args)->epsilon;
  double tolerance                 = ((Energy2D_t*)args)->tolerance;
  Wield::Series::FourierSeries &C1 = *(((Energy2D_t*)args)->C1);
  Wield::Series::FourierSeries &C2 = *(((Energy2D_t*)args)->C2);
  Matrix3d rot1                    = ((Energy2D_t*)args)->rot1;
  Matrix3d rot2                    = ((Energy2D_t*)args)->rot2;
  vector<double> &X                = *(((Energy2D_t*)args)->X);
  vector<double> &Y                = *(((Energy2D_t*)args)->Y);
  vector<double> &Z                = *(((Energy2D_t*)args)->Z);
  vector<double> &W                = *(((Energy2D_t*)args)->W);

  for (int i=0; i<X.size(); i++)
    {
      if (i%numThreads != index) continue;
      Eigen::Vector3d n(X[i],Y[i],Z[i]);
      Matrix3d N = 
	createMatrixFromNormalVector(n);
      W[i] = - Wield::Integrator::Surface(C1,N.transpose()*rot1,
					  C2,N.transpose()*rot2,
					  epsilon, tolerance);
      if (index==0) WIELD_PROGRESS("Energy surface",i,X.size(),1);
    }
  if (index==0) cout << endl;
  return 0;
}


}
}

#endif
