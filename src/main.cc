/// 
/// \mainpage WIELD: (W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries 
/// This is a small research program to compute the energy of a bicrystal interface. 
/// 

///
/// \file main.cpp
/// \brief This is the short description for main.cpp
///
/// This is the long description for main.cpp
/// \f[\int_{\Omega}\nabla\cdot\mathbb{V}dV = \int_{\partial\Omega}\mathbb{V}\cdot\mathbb{n}dA\f]
///


#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>


#include "tclap/CmdLine.h"
#include "Reader.h"

#include "Main/wieldVisualizeOR.h"
#include "Main/wieldGammaSurfaceSphere.h"
#include "Main/wieldGammaInterface1D.h"
#include "Main/wieldGammaOR1D.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/VTK/wieldVTK.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldCosSeries.h"
#include "Optimization/wieldConvexify1D.h"
#include "SurfaceIntegrate.h"
//#include "IO/wieldReaderMacros.h"

using namespace std;

void signalHandler(int signum)
{
  cout << endl;
  cout << WIELD_COLOR_RESET << "Program terminated" << endl;
  exit(signum);
}

int main(int argc, char* argv[])
{
  WIELD_EXCEPTION_TRY;

  signal(SIGINT, signalHandler);

  //
  // COMMAND LINE PARSING
  // 
  TCLAP::CmdLine cmd("(W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries");
  TCLAP::SwitchArg switchDynamicPlot("p", "dynamic-plot", "Show real-time VTK plot of energy", cmd, false);
  TCLAP::SwitchArg switchVisualize("s", "show-crystal", "Show VTK plot of initial OR", cmd, false);
  TCLAP::UnlabeledValueArg<string> argFileName("name", "Path to input file", true, "", "inputfile", cmd);
  cmd.parse(argc, argv);
  bool dynamicPlot = switchDynamicPlot.getValue();
  //bool visualize = switchVisualize.getValue();
  string fileName = argFileName.getValue();

  //
  // INPUT FILE PARSING
  // 

  // Create reader
  Reader::Reader reader(fileName, argc, argv, "$", "#", "...");
  
  if (reader.Find("VisualizeOR"))
    Wield::Main::VisualizeOR(reader, dynamicPlot);
  if (reader.Find("GammaOR1D"))
    Wield::Main::GammaOR1D(reader, dynamicPlot);
  if (reader.Find("GammaInterface1D"))
    Wield::Main::GammaInterface1D(reader, dynamicPlot);
  if (reader.Find("GammaSurfaceSphere"))
    Wield::Main::GammaSurfaceSphere(reader, dynamicPlot); 

  // WARN ABOUT UNUSED VARIABLES
  reader.PrintUnusedVariableWarnings();

  WIELD_EXCEPTION_CATCH_FINAL;
}


