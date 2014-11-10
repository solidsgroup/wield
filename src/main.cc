/// 
/// \mainpage WIELD: (W)eak approximation of (I)nterface (E)nergy for bicrysta(L) boun(D)aries 
/// This is a small research program to compute the energy of a bicrystal interface. 
/// 

///
/// @file main.cpp
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
#include "TCLAP/IgnoreArg.h"
#include "Reader.h"

#include "Main/wieldBlenderVoxelData.h"
#include "Main/wieldVisualizeOR.h"
#include "Main/wieldEnergySurfaceSphere.h"
#include "Main/wieldEnergyInterface1D.h"
#include "Main/wieldEnergyOR1D.h"
#include "Main/wieldFacet2D.h"
#include "Utils/wieldExceptions.h"

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
  TCLAP::ValueArg<int> valueNumThreads("n", "num-threads", "Number of pthreads to use",false,1,"", cmd);
  TCLAP::IgnoreArg testIgnoreArg("D","User defined variables","",cmd);
  TCLAP::UnlabeledValueArg<string> argFileName("name", "Path to input file", false, "", "inputfile", cmd);
  cmd.parse(argc, argv);
  bool dynamicPlot = switchDynamicPlot.getValue();
  int numThreads = valueNumThreads.getValue();
  string fileName = argFileName.getValue();

  //
  // INPUT FILE PARSING
  // 

  // Create reader
  Reader::Reader *rabbit;
  if (fileName == "")
    rabbit = new Reader::Reader(argc,argv,"$","#","...");
  else 
    rabbit = new Reader::Reader(fileName, argc, argv, "$", "#", "...");
  
  if (rabbit->Find("BlenderVoxelData"))
    Wield::Main::BlenderVoxelData(*rabbit);
  if (rabbit->Find("VisualizeOR"))
    Wield::Main::VisualizeOR(*rabbit, dynamicPlot);
  if (rabbit->Find("EnergyOR1D"))
    Wield::Main::EnergyOR1D(*rabbit, dynamicPlot);
  if (rabbit->Find("EnergyInterface1D"))
    Wield::Main::EnergyInterface1D(*rabbit, dynamicPlot);
  if (rabbit->Find("EnergySurfaceSphere"))
    Wield::Main::EnergySurfaceSphere(*rabbit, dynamicPlot, numThreads); 
  if (rabbit->Find("Facet2D"))
    Wield::Main::Facet2D(*rabbit,numThreads); 

  // WARN ABOUT UNUSED VARIABLES
  rabbit->PrintUnusedVariableWarnings();

  WIELD_EXCEPTION_CATCH_FINAL;
}


