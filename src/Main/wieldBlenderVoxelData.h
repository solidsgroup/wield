#ifndef WIELD_MAIN_BLENDERVOXELDATA_H
#define WIELD_MAIN_BLENDERVOXELDATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <csignal>


#include "tclap/CmdLine.h"
#include "Reader.h"

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
void BlenderVoxelData(Reader::Reader &reader)
{
  WIELD_EXCEPTION_TRY;

  // READ STANDARD VARIABLES
  WIELD_IO_READ_CRYSTAL();
  // WIELD_IO_READ_CRYSTAL(2);
  // WIELD_IO_READ_CRYSTAL_ORIENTATION("VisualizeOR",1);
  // WIELD_IO_READ_CRYSTAL_ORIENTATION("VisualizeOR",2);
  // WIELD_IO_READ_PARAMETERS("VisualizeOR");

  FILE *f = fopen("voxels.bvox","wb");

  int nx=100,ny=100,nz=100,nframes=1;
  //float xmin=-1,xmax=1,ymin=-1,ymax=1,zmin=-1,zmax=1;
  float xmin=0,xmax=crystal.alpha1,ymin=0,ymax=crystal.alpha2,zmin=0,zmax=crystal.alpha3;
  float dx = (xmax-xmin)/(float)(nx-1);    
  float dy = (ymax-ymin)/(float)(ny-1);    
  float dz = (zmax-zmin)/(float)(nz-1);    

  fwrite(&nx,sizeof(int),1,f);
  fwrite(&ny,sizeof(int),1,f);
  fwrite(&nz,sizeof(int),1,f);
  fwrite(&nframes,sizeof(int),1,f);

  for (int k=0; k<nz; k++)
    for (int j=0; j<ny; j++)
      for (int i=0; i<nx; i++)
	{
	  float x = xmin + dx*(float)i;
	  float y = ymin + dy*(float)j;
	  float z = zmin + dz*(float)k;

	  //float val = exp(-((x*x) + (y*y) + (z*z))/0.25);
	  float val = crystal.EvaluateAt(x,y,z);
	  fwrite(&val,sizeof(float),1,f);
      	  WIELD_PROGRESS("Generating file", k, nz, 1);
	}
  cout << endl;

  fclose(f);
  // double resolution = reader.Read<double>("VisualizeOR",50);

  // vector<Wield::Utils::VTK::Actor> actors;
  // actors.push_back(Wield::Utils::VTK::drawCrystal(crystal1, 
  // 						  omega1
  // 						  // *
  // 						  // createMatrixFromXAngle(theta_min*ThetaRotX1) *
  // 						  // createMatrixFromYAngle(theta_min*ThetaRotY1) *
  // 						  // createMatrixFromZAngle(theta_min*ThetaRotZ1) *
  // 						  // createMatrixFromXAngle(phi_min*PhiRotX) *
  // 						  // createMatrixFromYAngle(phi_min*PhiRotY) *
  // 						  // createMatrixFromZAngle(phi_min*PhiRotZ)
  // 						  ,
  // 						  Matrix3d::Identity(),
  // 						  0*crystal1.alpha1, -2*crystal1.alpha2, 0*crystal1.alpha3,
  // 						  2*crystal1.alpha1,  2*crystal1.alpha2, 2*crystal1.alpha3,
  // 						  (int)(resolution/crystal1.alpha1), 
  // 						  0.6,0.));
  // Wield::Utils::VTK::renderCrystals(actors);


  WIELD_EXCEPTION_CATCH_FINAL;
}
}
}

#endif
