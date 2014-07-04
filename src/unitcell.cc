

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#define eigen_assert(A) if (!(A)) throw new std::runtime_error("Eigen threw an exception");
#include "Eigen/Core"
#include "Eigen/Geometry"

using namespace std;
using namespace Eigen;

#include "/home/brandon/Research/Reader/Reader.h"


#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldExceptions.h"
#include "SurfaceIntegrate.h"
#include "Utils/wieldVTK.h"
#include "Utils/wieldProgress.h"

int main(int argc, char* argv[])
{
  WIELD_EXCEPTION_TRY;
  //
  // Import Lattice Data
  //

  string filename;
  if (argc < 2) 
    {WIELD_EXCEPTION_NEW("You must specify a filename!");}
  else filename=argv[1];

  Reader crystal1Reader(filename, "$", "#", "...");
  int order1 = crystal1Reader.Read<int>("order");
  CosSeries C1(order1); crystal1Reader.Read<CosSeries>("C", &C1);
  C1.order = order1;
  C1.alpha1 = crystal1Reader.Read<double>("a1");
  C1.alpha2 = crystal1Reader.Read<double>("a2");
  C1.alpha3 = crystal1Reader.Read<double>("a3");

  renderCrystal((drawCrystal(C1, 
			     Matrix3d::Identity(),
			     0, 0, 0,
			     C1.alpha1, C1.alpha2, C1.alpha3,
			     (int)((double)crystal1Reader.Read<double>("resolution",50)/C1.alpha1), 
			     0.6,0.)));
  
  WIELD_EXCEPTION_CATCH_FINAL;
}


