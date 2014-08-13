#ifndef WIELD_MAIN_FACET2D_H
#define WIELD_MAIN_FACET2D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>
#include <cstdlib>

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
void Facet2D(Reader::Reader &reader)
{
  WIELD_EXCEPTION_TRY;
  
  vector<double> x,y,z,w;

  //int maxFacetOrder        = reader.Read<int>("Facet2D", "MaxFacetOrder");
  string dataFile          = reader.Read<string>("Facet2D", "DataFile");
  //Vector3d interfaceNormal = reader.Read<Vector3d>("Facet2D", "InterfaceNormal");

  ifstream in(dataFile.c_str());
  if (!in)
    WIELD_EXCEPTION_NEW("Could not open input file " << dataFile); 
  string line;
  while (getline(in,line))
    {
      istringstream iss(line);
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
  

  //Wield::Optimization::Convexify2D(interfaceNormal, x,y,z,w);
  Wield::Optimization::Convexify2D<3>(x,y,z,w);



  WIELD_EXCEPTION_CATCH_FINAL;
}
}
}

#endif
