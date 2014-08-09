

#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>


#include "Utils/wieldExceptions.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
// #include "SurfaceIntegrate.h"
#include "Utils/VTK/wieldVTK.h"
#include "Utils/wieldProgress.h"
#include "Utils/wieldEigen.h"
#include "Reader.h"

using namespace std;

int main(int argc, char* argv[])
{
  WIELD_EXCEPTION_TRY;
  
  Import Lattice Data
  

  string filename;
  if (argc < 2) 
    {WIELD_EXCEPTION_NEW("You must specify a filename!");}
  else filename=argv[1];

  Reader::Reader crystal1Reader(filename, "$", "#", "...");
  int order1 = crystal1Reader.Read<int>("order");
  CosSeries C1(order1); crystal1Reader.Read<CosSeries>("C", &C1);
  C1.order = order1;
  C1.alpha1 = crystal1Reader.Read<double>("a1");
  C1.alpha2 = crystal1Reader.Read<double>("a2");
  C1.alpha3 = crystal1Reader.Read<double>("a3");

  renderCrystal((drawCrystal(C1, 
  			     Matrix3d::Identity(),
  			     Matrix3d::Identity(),
  			     0, 0, 0,
  			     C1.alpha1, C1.alpha2, C1.alpha3,
  			     (int)((double)crystal1Reader.Read<double>("resolution",50)/C1.alpha1), 
  			     0.6,0.)));
  
  WIELD_EXCEPTION_CATCH_FINAL;
}


