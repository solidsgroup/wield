

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#define eigen_assert(A) if (!(A)) throw new std::runtime_error("Eigen threw an exception");
#include "Eigen/Core"
#include "Eigen/Geometry"
// #include "SurfaceIntegrate.h"
// #include "Trig6Int.h"
// //#include "DTrig6Int.h"
// #include "ElasticEnergy.h"
// #include "Energy.h"
// #include "Rotations.h"
// #include "Crystal.h"
// #include "matio.h"
// #include "Reader.h"
// #include "Convexify.h"
// #include "readline/readline.h"

using namespace std;
using namespace Eigen;

#include "/home/brandon/Research/Reader/Reader.h"


#include "TypeDefinitions.h"
#include "MatrixUtilities.h"
#include "Exception.h"
#include "Energy.h"

int main(int argc, char* argv[])
{
  WIELD_TRY;

  #include "io2.h"
  
  
  for (double theta = theta_min; theta <= theta_max; theta += dtheta)
    {
      


    }

  
  WIELD_CATCH;
}


