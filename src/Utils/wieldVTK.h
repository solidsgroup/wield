#ifndef WIELD_UTILS_VTK_H
#define WIELD_UTILS_VTK_H
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#define eigen_assert(A) if (!(A)) throw new std::runtime_error("Eigen threw an exception");
#include "Eigen/Core"
#include "Eigen/Geometry"
#include "Faddeeva/Faddeeva.h"

using namespace std;
using namespace Eigen;

#include "/home/brandon/Research/Reader/Reader.h"
#include "Utils/wieldTypes.h"
#include "Utils/wieldRotations.h"
#include "Utils/wieldProgress.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkMath.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkShrinkFilter.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVoxel.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
#include <vtkStructuredGridOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkLookupTable.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>

typedef vtkSmartPointer<vtkActor> Actor;

double computeDensityFunction(double x, double y, double z, CosSeries C)
{
  WIELD_EXCEPTION_TRY;
  int order = C.order;
  double alpha1 = C.alpha1;
  double alpha2 = C.alpha2;
  double alpha3 = C.alpha3;
  double phi = 0;
  for (int l=0; l<order; l++)
    for (int m=0; m<order; m++)
      for (int n=0; n<order; n++)
	phi += 
	  C(l,m,n) *
	  cos(l*pi*x/alpha1) *
	  cos(m*pi*y/alpha2) *
	  cos(n*pi*z/alpha3);
  return phi;
  WIELD_EXCEPTION_CATCH;
}



Actor drawCrystal(CosSeries C, Matrix3d R,
		    double xmin, double ymin, double zmin,
		    double xmax, double ymax, double zmax,
		    int resolution,
		    double FactorTop=0, double FactorBottom=0)
{
  WIELD_EXCEPTION_TRY;
  if (xmin > xmax) WIELD_EXCEPTION_NEW("xmin > xmax");
  if (ymin > ymax) WIELD_EXCEPTION_NEW("ymin > ymax");
  if (zmin > zmax) WIELD_EXCEPTION_NEW("zmin > zmax");
  double x0=xmin,y0=ymin,z0=zmin;
  double xl=xmax-xmin,yl=ymax-ymin,zl=zmax-zmin;
  int nx = (int)(resolution*xl), ny=(int)(resolution*yl), nz=(int)(resolution*zl);
  double dx = xl/(double)nx, dy = yl/(double)ny, dz = zl/(double)nz;

  // Create a grid
  vtkSmartPointer<vtkStructuredGrid> structuredGrid = 
    vtkSmartPointer<vtkStructuredGrid>::New();
 
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();

  vtkSmartPointer<vtkDoubleArray> phi = 
    vtkSmartPointer<vtkDoubleArray>::New();

  double min=0, max=0, val=0;
  for(unsigned int k = 0; k < nz; k++)
    {
      for(unsigned int j = 0; j < ny; j++)
	for(unsigned int i = 0; i < nx; i++)
	  {
	    Vector3d X; X << x0 + i*dx, y0+j*dy, z0 + k*dz;
	    Vector3d x = R*X;
	  
	    //double x=X[0], y=X[1], z=X[2];

	    points->InsertNextPoint(X[0],X[1],X[2]);
	    if ((i!=0) && (j!=0) && (k!=0) && (i<nx-1) && (j<ny-1) && (k<nz-1))
	      phi->InsertNextValue(0);
	    else 
	      phi->InsertNextValue(computeDensityFunction(x[0],x[1],x[2],C));
	  }
      WIELD_PROGRESS("Calculating phi(box)", k, nz, 1);
    }
  cout << endl;

  double range[2]; phi->GetRange(range);
  vtkSmartPointer<vtkLookupTable> colorLookupTable = 
    vtkSmartPointer<vtkLookupTable>::New();
  colorLookupTable->SetTableRange(range[0] - (range[1]-range[0])*FactorBottom,range[1] + (range[1]-range[0])*FactorTop);
  colorLookupTable->Build();
  vtkSmartPointer<vtkDoubleArray> colors = 
    vtkSmartPointer<vtkDoubleArray>::New();

  for(int i=0; i<nx*ny*nz; i++)
    {
      double color[3];
      colorLookupTable->GetColor(phi->GetTuple1(i), color);
      colors->InsertNextTupleValue(color);
    }

 
  //specify the dimensions of the grid
  structuredGrid->SetDimensions(nx, ny, nz);
  structuredGrid->SetPoints(points);
  structuredGrid->GetPointData()->SetScalars(colors);

  // Create mapper
  vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(structuredGrid->GetProducerPort());

  // Create actor
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  
  return actor;
  WIELD_EXCEPTION_CATCH;
}

void renderCrystals(vector<Actor> actors)
{
  WIELD_EXCEPTION_TRY;
  // Visualize
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  renderWindowInteractor->SetInteractorStyle(style);

  for (int i=0; i<actors.size(); i++)
    renderer->AddActor(actors[actors.size()-i-1]);
  
  vtkSmartPointer<vtkAxesActor> axes =
    vtkSmartPointer<vtkAxesActor>::New();
  vtkSmartPointer<vtkOrientationMarkerWidget> widget = 
    vtkSmartPointer<vtkOrientationMarkerWidget>::New();
  widget->SetOrientationMarker(axes);
  widget->SetInteractor(renderWindowInteractor);
  widget->SetOutlineColor(0,0,0);
  widget->SetEnabled(1);
  widget->InteractiveOn();

  renderer->ResetCamera();
  renderer->SetBackground(1,1,1); // Background color white
  renderWindow->Render();
  renderWindowInteractor->Start();
  WIELD_EXCEPTION_CATCH;
}
		  
void renderCrystal(Actor actor)
{
  vector<Actor> actors;
  actors.push_back(actor);
  renderCrystals(actors);
}
#endif
