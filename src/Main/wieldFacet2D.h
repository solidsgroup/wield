#ifndef WIELD_MAIN_FACET2D_H
#define WIELD_MAIN_FACET2D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>
#include <cstdlib>
#include <pthread.h>

#include "Reader.h"

#include "Utils/wieldExceptions.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldCosSeries.h"
#include "Optimization/wieldConvexify2D.h"
#include "SurfaceIntegrate.h"
#include "IO/wieldReaderMacros.h"


using namespace std;

namespace Wield
{
namespace Main
{
void Facet2D(Reader::Reader &reader,
	     int numThreads = 1)
{
  WIELD_EXCEPTION_TRY;
  // srand(time(NULL));
  // for (int i=0;i<25;i++)
  //   ThetaInRange(360.*(double)rand()/(double)RAND_MAX,
  // 		 360.*(double)rand()/(double)RAND_MAX,
  // 		 360.*(double)rand()/(double)RAND_MAX);
  // exit(0);

  
  vector<double> x,y,z,w;

  string dataFile          = reader.Read<string>("Facet2D", "DataFile");
  int maxFacetOrder        = reader.Read<int>("Facet2D", "MaxFacetOrder", 3);

  ifstream in(dataFile.c_str());
  if (!in)
    WIELD_EXCEPTION_NEW("Could not open input file " << dataFile); 
  string line;
  while (getline(in,line))
    {
      std::istringstream iss(line);
      string token;
      for (int i=0; iss >> token; i++)
	{
	  if (i==0) x.push_back(atof(token.c_str()));
	  if (i==1) y.push_back(atof(token.c_str()));
	  if (i==2) z.push_back(atof(token.c_str()));
	  if (i==3) w.push_back(atof(token.c_str()));
	}
    }
  if ( x.size() != y.size() ||
       y.size() != z.size() ||
       z.size() != w.size())
    WIELD_EXCEPTION_NEW("Error reading input file: different x,y,z,w sizes");
  
  double wMin;
  Vector3d lambdaMin;
  Vector3d n1Min, n2Min, n3Min;
  vector<double> r(x.size()), theta(x.size());
  for (int i=0; i<x.size(); i++)
    {
      r[i] = sqrt(x[i]*x[i] + y[i]*y[i]);
      theta[i] = atan2(y[i],x[i])*180./pi; 
      while (theta[i] >= 0.) theta[i] -= 360.;
      while (theta[i] < 0.)  theta[i] += 360.;
      if (fabs(theta[i] - 360.) < 1E-8) theta[i] = 0.;
      if (r[i] < 1E-6) 
	{
	  wMin = w[i];
	  lambdaMin << 1,0,0;
	  n1Min << 0,0,1;
	  n2Min << 0,0,0;
	  n3Min << 0,0,0;
	}
    }

  
  pthread_t threads[numThreads];
  int errorCode;
  Wield::Optimization::ConvexifyData2D<3> *args =
    (Wield::Optimization::ConvexifyData2D<3> *)malloc(numThreads * sizeof(Wield::Optimization::ConvexifyData2D<3>));
  for (int i=0; i<numThreads; i++)
    {
      args[i].index = i;
      args[i].numThreads = numThreads;
      args[i].maxFacetOrder = maxFacetOrder;
      args[i].x = &x;
      args[i].y = &y;
      args[i].z = &z;
      args[i].w = &w;
      args[i].r = &r;
      args[i].theta = &theta;
      args[i].wMin = wMin;
      args[i].lambdaMin = lambdaMin;
      args[i].n1Min = n1Min;
      args[i].n1Min = n2Min;
      args[i].n1Min = n3Min;
      errorCode = pthread_create(&threads[i], NULL, Wield::Optimization::Convexify2D<3>, (void*)(&args[i]));
      if (errorCode)
	WIELD_EXCEPTION_NEW("Error starting thread #" << i << ": errorCode = " << errorCode);
    }

  for (int i=0; i<numThreads; i++)
    {
      errorCode = pthread_join(threads[i],NULL);
      if (errorCode)
	WIELD_EXCEPTION_NEW("Error joining thread #" << i << ": errorCode = " << errorCode);
    }

  wMin = INFINITY;
  Matrix3d nMin;
  for (int i=0; i<numThreads; i++)
    {
      if (args[i].wMin < wMin)
	{
	  wMin = args[i].wMin;
	  lambdaMin = args[i].lambdaMin;
	  nMin.col(0) = args[i].n1Min;
	  nMin.col(1) = args[i].n2Min;
	  nMin.col(2) = args[i].n3Min;
	}
    }
  
  
  cout << WIELD_COLOR_FG_YELLOW << wMin << WIELD_COLOR_RESET << endl;
  cout << WIELD_COLOR_FG_RED << lambdaMin.transpose() << WIELD_COLOR_RESET << endl;
  cout << WIELD_COLOR_FG_BLUE << nMin << WIELD_COLOR_RESET << endl;

  if (reader.Find("Facet2D","OutFile"))
    {
      string outFile = reader.Read<string>("Facet2D", "OutFile");
      ofstream out;
      out.open(outFile.c_str());
      out << wMin << endl;
      out << lambdaMin.transpose() << endl;
      out << nMin << endl;
      out.close();
    }
  WIELD_EXCEPTION_CATCH_FINAL;
}
}
}

#endif