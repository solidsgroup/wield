// WIELD: general interface energy computation

#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include "Eigen/Core"
#include "Eigen/Geometry"
#include "SurfaceIntegrate.h"
#include "Trig6Int.h"
#include "DTrig6Int.h"
#include "ElasticEnergy.h"
#include "Energy.h"
#include "Rotations.h"
#include "Crystal.h"
#include "matio.h"
#include "Reader.h"
#include "Convexify.h"
#include "readline/readline.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
  string filename;
  /**/ if (argc < 2) {filename=readline("Please specify filename: ");cout << filename << endl;} // Currently failing--do not use
  else filename=argv[1];
  Reader myreader(filename,argc,argv,true);

  string mode;       myreader.Read(mode, "$mode", (string)"");
  if (mode == "convexify") 
    {Convexify(myreader); exit(0);}

  #include "io.h"

  int order;
  if (order1==order2) order = order1;
  else {cout << "Crystal order must match" << endl; exit(0);}

  Vector6d alpha; alpha << alpha1_1,alpha1_2,alpha1_3,alpha2_1,alpha2_2,alpha2_3;
  Vector6d alpha0 = alpha;

  
  vector<pair<Vector3d, double> > w;

  Energy W(4,C_1,C_2,C,alpha0,stdev,tolerance,distribution,selfenergyfactor);

  Vector3d ex(1,0,0), ey(0,1,0), ez(0,0,1);

  double tol = 0.1;
  for (double theta = theta_min; theta <= theta_max; theta += dtheta)
    {
      Matrix3d R1 =  RotX((ThetaRotX1*theta)*PI/180) * RotY((ThetaRotY1*theta)*PI/180) * RotZ((ThetaRotZ1*theta)*PI/180);
      Matrix3d R2 =  RotX((ThetaRotX2*theta)*PI/180) * RotY((ThetaRotY2*theta)*PI/180) * RotZ((ThetaRotZ2*theta)*PI/180);

      if (testbed) 
	goto testbed;


      if (fabs(phi_min - phi_max) < 1E-10)
	{
	  W.SetR(Omega_1*R1,Omega_2*R2);

	  if (xtype=="degrees")
	    out << theta << " ";
	  else if (xtype == "normal")
	    out << ey.dot(R1*ez) << " ";
	  out << (A + B*W.W(alpha));
	  out << endl;
	}
      else
	for (double phi = phi_min; phi <= phi_max; phi += dphi)
	  {
	    Matrix3d RR1 =  
	      R1 * RotX((PhiRotX1*phi)*PI/180) * RotY((PhiRotY1*phi)*PI/180) * RotZ((PhiRotZ1*phi)*PI/180);
	    Matrix3d RR2 =  
	      R2 * RotX((PhiRotX2*phi)*PI/180) * RotY((PhiRotY2*phi)*PI/180) * RotZ((PhiRotZ2*phi)*PI/180);

	    W.SetR(Omega_1*RR1,Omega_2*RR2);
	    
	    double _w_ = (A + B*W.W(alpha));
	    Vector3d _n_ = RR1*ez; 

	    out  << ex.transpose()*_n_ << " " << ey.transpose()*_n_ << " " << _w_ << endl;
	    cout << ex.transpose()*_n_ << " " << ey.transpose()*_n_ << " " << _w_ << endl;

	    if (relaxation)
	      w.push_back(make_pair(_n_,_w_));
	    cout << endl;
	  }
      continue;

    testbed:

      /*
      {
      	R1 =  RotX((4*theta)*PI/180);
      	R2 =  RotX((4*theta)*PI/180);
      	W.SetR(Omega_1*R1,Omega_2*R2);
      
      	double small = 1E-5;
      	double eps = 0.5;
      	double DW, DW_numeric;
      
      	W.SetEpsilon(eps+small);
      	DW_numeric = W.W(alpha);
      	W.SetEpsilon(eps);
      	DW_numeric -= W.W(alpha);
      	DW_numeric /= small;
      
      	DW = W.W_epsilon(alpha);
      
      	cout << "computed=" << DW << "\t numeric=" << DW_numeric << endl;
      }
      exit(0);
      */

      double eps1=0.5, eps2=1, eps3;
      int k;
      double f1, f2;
      for (k=0;k<15;k++)
	{
	  W.SetR(Omega_1*R1,Omega_2*R2);

	  // W.SetEpsilon((double)k / 10.);
	  // cout << (double)k / 10. << " " << W.W(alpha) + E/((double) k/10.) << endl;
	  // continue;

	  W.SetEpsilon(eps1);
	  f1 = B*W.W_epsilon(alpha) - E;
	  W.SetEpsilon(eps2);
	  f2 = B*W.W_epsilon(alpha) - E;
	  eps3 = eps2 - f2*(eps2-eps1)/(f2-f1);
	  eps1 = eps2;
	  eps2 = eps3;
	  cout << "k=" << k << " " << fabs(eps2-eps1) << "   eps=" << eps3 << " f1=" << f1 << " f2=" << f2 << endl;
	  if (fabs(eps2-eps1)<1E-8) break;
	};
      cout << endl << endl;
      //if (k==15) {cout << "Convergence error" << endl; exit(0);}

      out << theta << " ";
      out << A + B*W.W(alpha) + E*eps2;
      out << endl;
    }

  if (relaxation)
    {
      vector<pair<Vector3d,double> >::iterator p,q,r;
      for (p=w.begin();p!=w.end();p++)
	{
	  for (q=p+1;q!=w.end();q++)
	    {
	      for (r=q+1;r!=w.end();r++)
		{
		  Matrix3d M; 
		  M.col(0) = p->first;
		  M.col(1) = q->first;
		  M.col(2) = r->first;

		  cout << (M.inverse()*ez).transpose() << endl;;

		}
	    }
	}
    }
}
