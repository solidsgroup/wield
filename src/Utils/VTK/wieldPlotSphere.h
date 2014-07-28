#ifndef WIELD_UTILS_VTK_SPHEREPLOT_H
#define WIELD_UTILS_VTK_SPHEREPLOT_H

#include "Utils/wieldExceptions.h"

#include <pthread.h>
#include <cmath>
#include <X11/Xlib.h>

#include <vtkPolyDataMapper.h>
#include <vtkQuadricLODActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkLookupTable.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkMutexLock.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkScalarBarActor.h>

namespace wield
{
namespace utils
{
namespace vtk
{

void *StartWindowInteractor(void *argument)
{
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    (vtkRenderWindowInteractor *)argument;
  //renderWindowInteractor->SetStillUpdateRate(15);
  renderWindowInteractor->Start();
  return NULL;
}

class PlotSphere
{
public:
  PlotSphere(int ThetaResolution=20, int PhiResolution=20, double ThetaMin=0, double ThetaMax=360, double PhiMin=0, double PhiMax=180)
  {
    XInitThreads();

    // Create a Sphere
    sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(ThetaResolution);
    sphere->SetPhiResolution(PhiResolution);
    sphere->SetStartTheta(ThetaMin);
    sphere->SetEndTheta(ThetaMax);
    sphere->SetStartPhi(PhiMin);
    sphere->SetEndPhi(PhiMax);
    sphere->SetRadius(1.);
    sphere->SetCenter(0,0,0);
    sphere->Update();

    poly = vtkSmartPointer<vtkPolyData>::New();
    poly->DeepCopy(sphere->GetOutput());

    int numPoints = sphere->GetOutput()->GetNumberOfPoints();
    scalars = vtkSmartPointer<vtkFloatArray>::New();
    scalars->SetNumberOfValues(numPoints);
    for( int i = 0; i < numPoints; ++i )
      scalars->SetValue(i,0./0.);


    // Lookup table
    lookUpTable = vtkSmartPointer<vtkLookupTable>::New();
    lookUpTable->SetSaturationRange(1,1);
    lookUpTable->SetValueRange(1,1);
    lookUpTable->SetNanColor(0,0,0,0);
    lookUpTable->Build();

    // Colorbar actor
    vtkSmartPointer<vtkScalarBarActor> scalarBar;
    scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBar->SetLookupTable(lookUpTable);

    // Mapper
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());
    mapper->SetInput(poly);
    mapper->ScalarVisibilityOn();
    mapper->SetScalarModeToUsePointData();
    mapper->SetColorModeToMapScalars();
    mapper->SetLookupTable(lookUpTable);

    // Sphere actor
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetInterpolationToFlat();
 
    // A renderer and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
 
    // An interactor
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
      vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetDesiredUpdateRate(1e20);
    renderer->AddActor(actor);
    renderer->AddActor2D(scalarBar);

    // Add axis orientation marker
    axes = vtkSmartPointer<vtkAxesActor>::New();
    widget =  vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    widget->SetOrientationMarker(axes);
    widget->SetInteractor(renderWindowInteractor);
    widget->SetOutlineColor(0,0,0);
    widget->SetEnabled(1);
    widget->InteractiveOn();

    renderer->ResetCamera();
    renderWindow->Render();
 
    int errorCode = pthread_create(&thread, NULL, StartWindowInteractor, (void*)renderWindowInteractor);
  }

  ~PlotSphere()
  {
    pthread_join(thread,NULL);
  }

  void GetPointLocations(vector<double> &X, vector<double> &Y, vector<double> &Z)
  {
    int numPts = sphere->GetOutput()->GetNumberOfPoints();
    for( int i = 0; i < numPts; ++i )
      {
    	double x[3];
    	sphere->GetOutput()->GetPoint(i,x);
    	X.push_back(x[0]);
    	Y.push_back(x[1]);
    	Z.push_back(x[2]);
      }
  }

  void SetScalarValues(const vector<double> values, bool blocking = false)
  {
    vtkSmartPointer<vtkMutexLock> mutexLock
      = vtkSmartPointer<vtkMutexLock>::New();
    //mutexLock->Lock();

    int numPts = sphere->GetOutput()->GetNumberOfPoints();
    if (values.size() > numPts)
      WIELD_EXCEPTION_NEW("Error: too many values to fit on the sphere");
    
    double min = *min_element(values.begin(), values.end());
    double max = *max_element(values.begin(), values.end());
    double maxMinusMin = max-min;
    if (fabs(max-min) < 1E-8) maxMinusMin = 1;

    for( int i = 0; i < values.size(); ++i )
      {
    	scalars->SetValue(i,values[i]);
    	//scalars->SetValue(i,(values[i]-min)/maxMinusMin);
    	//cout << (values[i%values.size()]-min)/maxMinusMin << endl;
      }
    //scalars->SetValue(values.size()-1, (values[values.size()-1]-min)/(maxMinusMin));
    //scalars->SetValue(values.size()-1, values[values.size()-1]);
    lookUpTable->SetTableRange(min,max);
    lookUpTable->Modified();
    mapper->SetScalarRange(min,max);
    mapper->Modified();
    poly->GetPointData()->SetScalars(scalars);
    poly->GetPointData()->Modified();  // THIS CALL IS SUPER IMPORTANT! 
    poly->GetPointData()->Update();
    actor->Modified();

    // renderWindow->Render();
    if (blocking)
      pthread_join(thread,NULL);

    // if (blocking)
    //   renderWindowInteractor->Start();
    // else
    //   renderWindowInteractor->Render();
  }
  
private:
  pthread_t thread;
  vtkSmartPointer<vtkSphereSource> sphere;
  vtkSmartPointer<vtkPolyData> poly;
  vtkSmartPointer<vtkFloatArray> scalars;
  vtkSmartPointer<vtkLookupTable> lookUpTable;
  vtkSmartPointer<vtkPolyDataMapper> mapper;
  vtkSmartPointer<vtkActor> actor;
  vtkSmartPointer<vtkAxesActor> axes;
  vtkSmartPointer<vtkOrientationMarkerWidget> widget;
  vtkSmartPointer<vtkRenderer> renderer;
  vtkSmartPointer<vtkRenderWindow> renderWindow;
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
};

}
}
}

#endif


