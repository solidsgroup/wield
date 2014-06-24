//
// double vector
// 



Reader reader("in.in", "$", "#", "...");
string outfile = reader.Read<string>("outfile"); // file to store computation data
ofstream out(outfile.c_str());        // output stream

reader.Read<Vector6d>("X1");

Vector3d a(1,0,0), b(0,1,0);
createMatrixFromXY(a,b);


Matrix3d Omega_1; // Specify orientation of crystal 1
if (reader.Find("X1") && reader.Find("Y1"))
  Omega_1 = createMatrixFromXY(reader.Read<Vector3d>("X1"), reader.Read<Vector3d>("Y1"));
 else if (reader.Find("Y1") && reader.Find("Z1"))
   Omega_1 = createMatrixFromYZ(reader.Read<Vector3d>("Y1"), reader.Read<Vector3d>("Z1"));
 else if (reader.Find("Z1") && reader.Find("X1"))
   Omega_1 = createMatrixFromZX(reader.Read<Vector3d>("Z1"), reader.Read<Vector3d>("X1"));
 else WIELD_NEW_EXCEPTION("Missing two vectors to specify Omega_1");

Matrix3d Omega_2; // Specify orientation of crystal 2
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
// Import Lattice Data
//

string f1 = reader.Read<string>("C_1");
Reader crystal1Reader(f1, "$", "#", "...");
int order1 = crystal1Reader.Read<int>("order");
double alpha1_1 = crystal1Reader.Read<double>("a1");
double alpha1_2 = crystal1Reader.Read<double>("a2");
double alpha1_3 = crystal1Reader.Read<double>("a3");
CosSeries C_1(order1); crystal1Reader.Read<CosSeries>("C", &C_1);

string f2 = reader.Read<string>("C_2");
Reader crystal2Reader(f2, "$", "#", "...");
int order2 = crystal1Reader.Read<int>("order");
double alpha2_1 = crystal1Reader.Read<double>("a1");
double alpha2_2 = crystal1Reader.Read<double>("a2");
double alpha2_3 = crystal1Reader.Read<double>("a3");
CosSeries C_2(order1); crystal1Reader.Read<CosSeries>("C", &C_2);






//
// Variable wastelands
//

//Vector6d C = reader.Read<Vector6d>("C", Vector6d(0)); // Stores elastic constants of crystals

//
// SUPER SKETCHY! Use this with caution
// 
// double RotX1_offset = reader.Read<double>("RotX1_offset");
// double RotY1_offset = reader.Read<double>("RotY1_offset");
// double RotZ1_offset = reader.Read<double>("RotZ1_offset");
// Omega_1 = Omega_1*RotZ(RotZ1_offset*PI/180)*RotY(RotY1_offset*PI/180)*RotX(RotX1_offset*PI/180);
// double RotX2_offset = reader.Read<double>("RotX2_offset");
// double RotY2_offset = reader.Read<double>("RotY2_offset");
// double RotZ2_offset = reader.Read<double>("RotZ2_offset");
// Omega_2 = Omega_2*RotZ(RotZ2_offset*PI/180)*RotY(RotY2_offset*PI/180)*RotX(RotX2_offset*PI/180);

