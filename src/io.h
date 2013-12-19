string outfile;    myreader.Read(outfile, "$outfile");
ofstream out;      out.open(outfile.c_str());
Vector6d C;        myreader.Read(C,"$C"); 
Matrix3d Omega_1;
try
{
  Vector3d X1;      myreader.Read(X1,"$X1");
  Vector3d Y1;      myreader.Read(Y1,"$Y1");
  Omega_1 = RotXY(X1,Y1);
}
catch (int err1)
{
  try
    {
      Vector3d Y1;      myreader.Read(Y1,"$Y1");
      Vector3d Z1;      myreader.Read(Z1,"$Z1");
      Omega_1 = RotYZ(Y1,Z1);
    }
  catch (int err2)
    {
      try
	{
	  Vector3d Z1;      myreader.Read(Z1,"$Z1");
	  Vector3d X1;      myreader.Read(X1,"$X1");
	  Omega_1 = RotZX(Z1,X1);
	}
      catch (int err3)
	{
	  cout << "Error: at least 2 of (X1, Y1, Z1) must be defined" << endl;
	  exit(0); 
	}
    }
}

Matrix3d Omega_2;
try
{
  Vector3d X2;      myreader.Read(X2,"$X2");
  Vector3d Y2;      myreader.Read(Y2,"$Y2");
  Omega_2 = RotXY(X2,Y2);
}
catch (int err1)
{
  try
    {
      Vector3d Y2;      myreader.Read(Y2,"$Y2");
      Vector3d Z2;      myreader.Read(Z2,"$Z2");
      Omega_2 = RotYZ(Y2,Z2);
    }
  catch (int err2)
    {
      try
	{
	  Vector3d Z2;      myreader.Read(Z2,"$Z2");
	  Vector3d X2;      myreader.Read(X2,"$X2");
	  Omega_2 = RotZX(Z2,X2);
	}
      catch (int err3)
	{
	  cout << "Error: at least 2 of (X2, Y2, Z2) must be defined" << endl;
	  exit(0); 
	}
    }
}

double RotX1_offset;    myreader.Read(RotX1_offset,"$RotX1_offset",0.);
double RotY1_offset;    myreader.Read(RotY1_offset,"$RotY1_offset",0.);
double RotZ1_offset;    myreader.Read(RotZ1_offset,"$RotZ1_offset",0.);
Omega_1 = Omega_1*RotZ(RotZ1_offset*PI/180)*RotY(RotY1_offset*PI/180)*RotX(RotX1_offset*PI/180);
double RotX2_offset;    myreader.Read(RotX2_offset,"$RotX2_offset",0.);
double RotY2_offset;    myreader.Read(RotY2_offset,"$RotY2_offset",0.);
double RotZ2_offset;    myreader.Read(RotZ2_offset,"$RotZ2_offset",0.);
Omega_2 = Omega_2*RotZ(RotZ2_offset*PI/180)*RotY(RotY2_offset*PI/180)*RotX(RotX2_offset*PI/180);

double ThetaRotX1;           myreader.Read(ThetaRotX1,"$ThetaRotX1",0.);
double ThetaRotY1;           myreader.Read(ThetaRotY1,"$ThetaRotY1",0.);
double ThetaRotZ1;           myreader.Read(ThetaRotZ1,"$ThetaRotZ1",0.);
double ThetaRotX2;           myreader.Read(ThetaRotX2,"$ThetaRotX2",0.);
double ThetaRotY2;           myreader.Read(ThetaRotY2,"$ThetaRotY2",0.);
double ThetaRotZ2;           myreader.Read(ThetaRotZ2,"$ThetaRotZ2",0.);

double PhiRotX1;        myreader.Read(PhiRotX1,"$PhiRotX1",0.);
double PhiRotY1;        myreader.Read(PhiRotY1,"$PhiRotY1",0.);
double PhiRotZ1;        myreader.Read(PhiRotZ1,"$PhiRotZ1",0.);
double PhiRotX2;        myreader.Read(PhiRotX2,"$PhiRotX2",0.);
double PhiRotY2;        myreader.Read(PhiRotY2,"$PhiRotY2",0.);
double PhiRotZ2;        myreader.Read(PhiRotZ2,"$PhiRotZ2",0.);

double tolerance; myreader.Read(tolerance,"$tolerance");
double A, B, stdev;
try
{
  string f_constants;
  myreader.Read(f_constants, "$f_constants");
  Reader constantsreader(f_constants,true);
  constantsreader.Read(A,"$A");
  constantsreader.Read(B,"$B");
  constantsreader.Read(stdev,"$stdev");
}
catch(int code)
{
  myreader.Read(A,"$A");
  myreader.Read(B,"$B");
  myreader.Read(stdev,"$stdev");
}

double E;         myreader.Read(E,"$E",0.);

string f1; myreader.Read(f1, "$C_1"); 
string f2; myreader.Read(f2, "$C_2"); 
  
double theta_min; myreader.Read(theta_min, "$theta_min");
double theta_max; myreader.Read(theta_max, "$theta_max");
double dtheta;    myreader.Read(dtheta,    "$dtheta");

double phi_min; myreader.Read(phi_min, "$phi_min", 0.);
double phi_max; myreader.Read(phi_max, "$phi_max", 0.);
double dphi;    myreader.Read(dphi,    "$dphi", 0.);

Reader Crystal1(f1);
int order1;            Crystal1.Read(order1, "$order");
double alpha1_1;       Crystal1.Read(alpha1_1, "$a1");
double alpha1_2;       Crystal1.Read(alpha1_2, "$a2");
double alpha1_3;       Crystal1.Read(alpha1_3, "$a3");
double C_1[4][4][4];   Crystal1.Read(C_1,"$C");

Reader Crystal2(f2);
int order2;            Crystal1.Read(order2, "$order");
double alpha2_1;       Crystal1.Read(alpha2_1, "$a1");
double alpha2_2;       Crystal1.Read(alpha2_2, "$a2");
double alpha2_3;       Crystal1.Read(alpha2_3, "$a3");
double C_2[4][4][4];   Crystal2.Read(C_2,"$C");

string distribution; myreader.Read(distribution, "$distribution", (string)"gaussian");
double selfenergyfactor; myreader.Read(selfenergyfactor, "$selfenergyfactor", 0.);

int relaxation; myreader.Read(relaxation, "$relaxation", 0);
int testbed; myreader.Read(testbed, "$testbed", 0);
string xtype; myreader.Read(xtype, "$xtype", (string)"degrees");
