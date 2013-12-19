#include "Reader.h"
#include <array>

using namespace std;
int Convexify(Reader &myreader)
{
  string datafile; myreader.Read(datafile, "$datafile");
  Reader datareader(datafile,false);
  vector<array<double, 2> > data;
  datareader.ReadData(data);

  string outfile;    myreader.Read(outfile, "$outfile", datafile);
  ofstream out; out.open(outfile.c_str());
  
  double N = data.size();
  /* double x_min=data[0][0], x_max=data[0][0]; */
  /* for(int i=0;i<n;i++) */
  /*   { */
  /*     if (data[i][0]<x_min) x_min=data[i][0]; */
  /*     if (data[i][0]>x_max) x_max=data[i][0]; */
  /*   } */
  /* myreader.Read(x_min,"$x_min",x_min); */
  /* myreader.Read(x_max,"$x_max",x_max); */

  double min, W, lambda1, lambda2;
  for(int i=0;i<N;i++)
    {
      min = data[i][1];
      Vector2d ni(data[i][0], sqrt(1-data[i][0]*data[i][0]));
      for (int l=0; l<i; l++)
	for (int u=i+1; u<N; u++)
	  {
	    Vector2d nl(data[l][0], sqrt(1-data[l][0]*data[l][0]));
	    Vector2d nu(data[u][0], sqrt(1-data[u][0]*data[u][0]));

	    double det = (nl(0)*nu(1) - nl(1)*nu(0));
	    double detl = (ni(0)*nu(1) - ni(1)*nu(0));
	    double detu = (nl(0)*ni(1) - nl(1)*ni(0));
	    lambda1 = detl/det;
	    lambda2 = detu/det;
	    W = lambda1*data[l][1] + lambda2*data[u][1];

	    /* lambda1=(data[i][0] - data[l][0])/(data[u][0]-data[l][0]); */
	    /* lambda2=(data[u][0] - data[i][0])/(data[u][0]-data[l][0]); */
	    /* W = lambda2*data[l][1] + lambda1*data[u][1]; */

	    if (W<min) min=W;
	  }
      out  << data[i][0] << " " << data[i][1] << " " << min << endl;
      cout << data[i][0] << " " << data[i][1] << " " << min << endl;
  }
  

}
