

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
  WIELD_TRY;

  //
  // OPEN INPUT FILE READER
  // 

  string filename;
  if (argc < 2) 
    {WIELD_NEW_EXCEPTION("You must specify a filename!");}
  else filename=argv[1];
  Reader reader(filename, "$", "#", "...");


  //
  // SPECIFICATION OF THE ORIENTATION RELATIONSHIP
  // 

  // Specify orientation of crystal 1
  Matrix3d Omega_1;
  if (reader.Find("X1") && reader.Find("Y1"))
    Omega_1 = createMatrixFromXY(reader.Read<Vector3d>("X1"), reader.Read<Vector3d>("Y1"));
  else if (reader.Find("Y1") && reader.Find("Z1"))
    Omega_1 = createMatrixFromYZ(reader.Read<Vector3d>("Y1"), reader.Read<Vector3d>("Z1"));
  else if (reader.Find("Z1") && reader.Find("X1"))
    Omega_1 = createMatrixFromZX(reader.Read<Vector3d>("Z1"), reader.Read<Vector3d>("X1"));
  else WIELD_NEW_EXCEPTION("Missing two vectors to specify Omega_1");

  // Specify orientation of crystal 2
  Matrix3d Omega_2; 
  if (reader.Find("X2") && reader.Find("Y2"))
    Omega_2 = createMatrixFromXY(reader.Read<Vector3d>("X2"), reader.Read<Vector3d>("Y2"));
  else if (reader.Find("Y2") && reader.Find("Z2"))
    Omega_2 = createMatrixFromYZ(reader.Read<Vector3d>("Y2"), reader.Read<Vector3d>("Z2"));
  else if (reader.Find("Z2") && reader.Find("X2"))
    Omega_2 = createMatrixFromZX(reader.Read<Vector3d>("Z2"), reader.Read<Vector3d>("X2"));
  else WIELD_NEW_EXCEPTION("Missing two vectors to specify Omega_2");


  //
  // VARIATION OF THE ORIENTATION RELATIONSHIP
  //

  // Specify the range of the FREE VARIABLES:
  double theta_min = reader.Read<double>("theta_min");
  double dtheta    = reader.Read<double>("dtheta");
  double theta_max = reader.Read<double>("theta_max");
  double phi_min   = reader.Read<double>("phi_min",0.);
  double dphi      = reader.Read<double>("dphi",0.);
  double phi_max   = reader.Read<double>("phi_max",0.);

  // Specify the rotation of the CRYSTAL 
  double ThetaRotX1 = reader.Read<double>("ThetaRotX1",0.);
  double ThetaRotY1 = reader.Read<double>("ThetaRotY1",0.);
  double ThetaRotZ1 = reader.Read<double>("ThetaRotZ1",0.);
  double ThetaRotX2 = reader.Read<double>("ThetaRotX2",0.);
  double ThetaRotY2 = reader.Read<double>("ThetaRotY2",0.);
  double ThetaRotZ2 = reader.Read<double>("ThetaRotZ2",0.);

  // Specify the rotation of the INTERFACE
  double PhiRotX1 = reader.Read<double>("PhiRotX1",0.);
  double PhiRotY1 = reader.Read<double>("PhiRotY1",0.);
  double PhiRotZ1 = reader.Read<double>("PhiRotZ1",0.);
  double PhiRotX2 = reader.Read<double>("PhiRotX2",0.);
  double PhiRotY2 = reader.Read<double>("PhiRotY2",0.);
  double PhiRotZ2 = reader.Read<double>("PhiRotZ2",0.);


  //
  // ADJUSTABLE PARAMETERS
  //

  double A,B,stdev;
  if (reader.Find("f_constants"))
    {
      string f_constants = reader.Read<string>("f_constants");
      Reader constantsReader(f_constants, "$", "#", "...");
      A = constantsReader.Read<double>("A");
      B = constantsReader.Read<double>("B");
      stdev = constantsReader.Read<double>("stdev");
    }
  else // Otherwise, look in the current file
    {
      A = reader.Read<double>("A");
      B = reader.Read<double>("B");
      stdev = reader.Read<double>("stdev");
    }


  //
  // LATTICE FOURIER COEFFICIENTS FROM FILE
  //

  // Top crystal
  string f1 = reader.Read<string>("C_1");
  Reader crystal1Reader(f1, "$", "#", "...");
  int order1 = crystal1Reader.Read<int>("order");
  CosSeries C1(order1); crystal1Reader.Read<CosSeries>("C", &C1);
  C1.order = order1;
  C1.alpha1 = crystal1Reader.Read<double>("a1");
  C1.alpha2 = crystal1Reader.Read<double>("a2");
  C1.alpha3 = crystal1Reader.Read<double>("a3");

  // Bottom crystal
  string f2 = reader.Read<string>("C_2");
  Reader crystal2Reader(f2, "$", "#", "...");
  int order2 = crystal2Reader.Read<int>("order");
  CosSeries C2(order2); crystal2Reader.Read<CosSeries>("C", &C2);
  C2.order = order2;
  C2.alpha1 = crystal2Reader.Read<double>("a1");
  C2.alpha2 = crystal2Reader.Read<double>("a2");
  C2.alpha3 = crystal2Reader.Read<double>("a3");


  //
  // MISC
  //

  double tolerance = reader.Read<double>("tolerance",0.);


  //
  // OUTPUT FILE STREAM
  //

  string outfile = reader.Read<string>("outfile"); // file to store computation data
  ofstream out(outfile.c_str());        // output stream



  //
  // VTK VISUALIZATION
  //

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


  //
  // ROTATE ORIENTATION RELATIONSHIP AND COMPUTE GRAIN BOUNDARY ENERGY
  //

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

      WIELD_PROGRESS("Computing energy curve", theta-theta_min, theta_max-theta_min)
    }
  cout << endl;
  
  WIELD_CATCH_FINAL;
}


