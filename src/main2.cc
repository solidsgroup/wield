

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


#include "TypeDefinitions.h"
#include "MatrixUtilities.h"
#include "Exception.h"
#include "SurfaceIntegrate.h"
#include "wieldVTK.h"

int main(int argc, char* argv[])
{
  WIELD_TRY;

  string filename;
  if (argc < 2) 
    {WIELD_NEW_EXCEPTION("You must specify a filename!");}
  else filename=argv[1];

  Reader reader(filename, "$", "#", "...");
  cout << reader.Read<double>("test") << endl;

  #include "io2.h"


  if (reader.Find("vtk"))
    {
      vector<Actor> actors;
      actors.push_back(drawCrystal(C1, 
				   Omega_1
				   *createMatrixFromXAngle(reader.Read<double>("vtk_rot_x1",0.)) 
				   *createMatrixFromYAngle(reader.Read<double>("vtk_rot_y1",0.))
				   *createMatrixFromZAngle(reader.Read<double>("vtk_rot_z1",0.)),
				   0*C1.alpha1, -2*C1.alpha2, 0*C1.alpha3,
				   2*C1.alpha1,  2*C1.alpha2, 2*C1.alpha3,
				   (int)((double)reader.Read<double>("resolution",50)/C1.alpha1), 
				   0.6,0.));
      actors.push_back(drawCrystal(C2, 
				   Omega_2
				   *createMatrixFromXAngle(reader.Read<double>("vtk_rot_x2",0.)) 
				   *createMatrixFromYAngle(reader.Read<double>("vtk_rot_y2",0.))
				   *createMatrixFromZAngle(reader.Read<double>("vtk_rot_z2",0.)),
				   0*C2.alpha1, -2*C2.alpha2, -2*C2.alpha3,
				   2*C2.alpha1,  2*C2.alpha2, 0*C2.alpha3,
				   (int)((double)reader.Read<double>("resolution",50)/C1.alpha1), 
				   0.6,0.));
      renderCrystals(actors);
      return 0;
    }	

  for (double theta = theta_min; theta <= theta_max; theta += dtheta)
    {
      Matrix3d Rot1 = 
	Omega_1 *
	createMatrixFromXAngle(theta*ThetaRotX1) *
	createMatrixFromYAngle(theta*ThetaRotY1) *
	createMatrixFromZAngle(theta*ThetaRotZ1);
      Matrix3d Rot2 = 
	Omega_2 *
	createMatrixFromXAngle(theta*ThetaRotX2) *
	createMatrixFromYAngle(theta*ThetaRotY2) *
	createMatrixFromZAngle(theta*ThetaRotZ2);
      
      out << theta << " " << 
	A - B*SurfaceIntegrate(C1, Rot1,C2, Rot2,stdev,tolerance) << endl;

    }

  
  WIELD_CATCH_FINAL;
}


