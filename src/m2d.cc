///
/// \file m2d.cc
/// \brief Currently, you can safely disregard this file
///
/// This file is currently under testing.
///


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

#include "/home/brandon/Research/Reader/Reader.h"

#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "SurfaceIntegrate.h"
#include "Utils/wieldVTK.h"
#include "Utils/wieldProgress.h"


#define GETC {string tst; std::getline(std::cin,tst);}

int main(int argc, char* argv[])
{
  WIELD_EXCEPTION_TRY;

  string xlabel, ylabel;
  vector<double> X, Y;

  // Temporary
  for (double f=0; f<=pi; f+= 0.1)
    {
      X.push_back(f);
      Y.push_back(exp(f));
    }
  // End Temporary

  // 1) Initialization phase

  PlotWindow2D plotWindow = createNewPlotWindow2D();
  plotLine(plotWindow,X,Y);
  GETC;
  plotLine(plotWindow,Y,X);
  GETC;
  
  WIELD_EXCEPTION_CATCH_FINAL;
}


