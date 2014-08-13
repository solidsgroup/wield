#ifndef WIELD_UTILS_VTK_SPHEREPLOT_H
#define WIELD_UTILS_VTK_SPHEREPLOT_H

#include "Utils/wieldExceptions.h"

#include <cmath>

#ifdef WIELD_USE_VTK
#include <pthread.h>
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
#endif

namespace Wield
{
namespace Utils
{
namespace VTK
{

void *StartWindowInteractor(void *argument)
{
#ifdef WIELD_USE_VTK
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    (vtkRenderWindowInteractor *)argument;
  //renderWindowInteractor->SetStillUpdateRate(15);
  renderWindowInteractor->Start();
#endif
  return NULL;
}

class PlotSphere
{
public:
  PlotSphere(int _ThetaResolution=20, int _PhiResolution=20, double _ThetaMin=0, double _ThetaMax=360, double _PhiMin=0, double _PhiMax=180)
  {
    #ifdef WIELD_USE_VTK
    XInitThreads();

    // Create a Sphere
    sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(_ThetaResolution);
    sphere->SetPhiResolution(_PhiResolution);
    sphere->SetStartTheta(_ThetaMin);
    sphere->SetEndTheta(_ThetaMax);
    sphere->SetStartPhi(_PhiMin);
    sphere->SetEndPhi(_PhiMax);
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
    lookUpTable->SetHueRange(.75,0);
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
 
    pthread_create(&thread, NULL, StartWindowInteractor, (void*)renderWindowInteractor);
#else
    ThetaResolution = _ThetaResolution;
    PhiResolution = _PhiResolution;
    ThetaMin = _ThetaMin;
    ThetaMax = _ThetaMax;
    PhiMin = _PhiMin;
    PhiMax = _PhiMax;
#endif
  }

  ~PlotSphere()
  {
    #ifdef WIELD_USE_VTK
    pthread_join(thread,NULL);
    #endif
  }

  void GetPointLocations(vector<double> &X, vector<double> &Y, vector<double> &Z)
  {
    #ifdef WIELD_USE_VTK
    int numPts = sphere->GetOutput()->GetNumberOfPoints();
    for( int i = 0; i < numPts; ++i )
      {
    	double x[3];
    	sphere->GetOutput()->GetPoint(i,x);
    	X.push_back(x[0]);
    	Y.push_back(x[1]);
    	Z.push_back(x[2]);
      }
    #else
    double dTheta = (ThetaMax - ThetaMin)/(double)ThetaResolution;
    double dPhi = (PhiMax - PhiMin)/(double)PhiResolution;
    for (double theta = ThetaMin; theta < ThetaMax + dTheta; theta += dTheta) 
      for (double phi = PhiMin; phi < PhiMax + dPhi; phi += dPhi) 
	{
	  X.push_back(sin(phi)*cos(theta));
	  Y.push_back(sin(phi)*sin(theta));
	  Z.push_back(cos(phi));
	}
    #endif
  }

  void SetData(const vector<double> values, bool blocking = false)
  {
    #ifdef WIELD_USE_VTK
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
#endif
  }
  
private:
#ifdef WIELD_USE_VTK
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
#else
  int ThetaResolution, PhiResolution;
  double ThetaMin, ThetaMax, PhiMin, PhiMax;
#endif 
};

}
}
}

#endif


