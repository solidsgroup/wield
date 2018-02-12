#ifndef WIELD_MAIN_VISUALIZEOR_H
#define WIELD_MAIN_VISUALIZEOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>


#include "tclap/CmdLine.h"
#include "solidsuccs-reader/Reader.h"
#include "Utils/wieldExceptions.h"
#include "Utils/wieldColor.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/VTK/wieldVTK.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldEigen.h"
#include "Series/wieldCosSeries.h"
#include "Optimization/wieldConvexify1D.h"
#include "IO/wieldReaderMacros.h"


namespace Wield
{
namespace Main
{
void VisualizeOR(Reader::Reader &reader,bool dynamicPlot)
{
  WIELD_EXCEPTION_TRY;

  // READ STANDARD VARIABLES
  WIELD_IO_READ_CRYSTAL(1);
  WIELD_IO_READ_CRYSTAL(2);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("VisualizeOR",1);
  WIELD_IO_READ_CRYSTAL_ORIENTATION("VisualizeOR",2);
  WIELD_IO_READ_PARAMETERS("VisualizeOR");

  double resolution = reader.Read<double>("VisualizeOR",50);

  vector<Wield::Utils::VTK::Actor> actors;
  actors.push_back(Wield::Utils::VTK::drawCrystal(crystal1, 
						  omega1
						  // *
						  // createMatrixFromXAngle(theta_min*ThetaRotX1) *
						  // createMatrixFromYAngle(theta_min*ThetaRotY1) *
						  // createMatrixFromZAngle(theta_min*ThetaRotZ1) *
						  // createMatrixFromXAngle(phi_min*PhiRotX) *
						  // createMatrixFromYAngle(phi_min*PhiRotY) *
						  // createMatrixFromZAngle(phi_min*PhiRotZ)
						  ,
						  Matrix3d::Identity(),
						  0*crystal1.alpha1, -2*crystal1.alpha2, 0*crystal1.alpha3,
						  2*crystal1.alpha1,  2*crystal1.alpha2, 2*crystal1.alpha3,
						  (int)(resolution/crystal1.alpha1), 
						  0.6,0.));
  actors.push_back(Wield::Utils::VTK::drawCrystal(crystal2, 
						  omega2
						  // *
						  // createMatrixFromXAngle(theta_min*ThetaRotX2) *
						  // createMatrixFromYAngle(theta_min*ThetaRotY2) *
						  // createMatrixFromZAngle(theta_min*ThetaRotZ2) *
						  // createMatrixFromXAngle(phi_min*PhiRotX) *
						  // createMatrixFromYAngle(phi_min*PhiRotY) *
						  // createMatrixFromZAngle(phi_min*PhiRotZ)
						  ,
						  Matrix3d::Identity(),
						  0*crystal2.alpha1, -2*crystal2.alpha2, -2*crystal2.alpha3,
						  2*crystal2.alpha1,  2*crystal2.alpha2, 0*crystal2.alpha3,
						  (int)(resolution/crystal1.alpha1), 
						  0.6,0.));
  Wield::Utils::VTK::renderCrystals(actors);


  WIELD_EXCEPTION_CATCH_FINAL;
}
}
}

#endif
