/**********************************
 * Maria Martinez 24-05-06
 * Class DMHaloLGE
 * LGE Halo Model
 *********************************/
#include "DMHaloLGE.hh"
#include "DMUtil.hh"
#include <sstream>
#include <iostream>
#include <math.h>
#include <string.h>



// Constructor, copy constructor, destructor
DMHaloLGE::DMHaloLGE()
{
  Vmin=0; T0=0; Tm=0; Phiv=0;
}
DMHaloLGE::DMHaloLGE(const DMHaloLGE & other):
DMVHaloModel(other)
{
  P = other.P;
  Q = other.Q;
  Beta = other.Beta;
  Axis = other.Axis;
  MaxDim = other.MaxDim;
  Vmin = new double [MaxDim];
  T0 = new double [MaxDim];
  Tm = new double [MaxDim];
  Phiv = new double [MaxDim];
  memcpy(Vmin, other.Vmin, MaxDim*sizeof(double));
  memcpy(T0, other.T0, MaxDim*sizeof(double));
  memcpy(Tm, other.Tm, MaxDim*sizeof(double));
  memcpy(Phiv, other.Phiv, MaxDim*sizeof(double));


}
DMHaloLGE::~DMHaloLGE()
{
  if (Vmin!=0)  delete [] Vmin;
  if (T0!=0)  delete [] T0;
  if (Tm!=0)  delete [] Tm;
  if (Phiv!=0)  delete [] Phiv;
}

// Initialize parameters from file
int DMHaloLGE::Initialize(char * fileName)
{
  int i = 0;
  std::string parsed = DMParseShellVars(fileName);
  fstream fq (parsed.c_str(), ios::in);

  if (!fq.good())
  {
    std::cout << "Cannot open file " << parsed.c_str() << std::endl;
    return -1;
  }

  char line [256];
  char dummy[256];
  while (!fq.eof())
  {
    fq.getline(line, 240);
    if (fq.eof()) break;
    stringstream srLine(stringstream::in | stringstream::out);
    srLine << line;
    if (line[0]=='#') continue;
    srLine >> dummy;

    if      (!strcmp(dummy,"RHO"))  srLine >> Rho;
    else if (!strcmp(dummy,"V0"))  srLine >> V0;
    else if (!strcmp(dummy,"P"))  srLine >> P;
    else if (!strcmp(dummy,"Q"))  srLine >> Q;
    else if (!strcmp(dummy,"BETA"))  srLine >> Beta;
    else if (!strcmp(dummy,"AXIS"))  srLine >> Axis;
  }
  // Set V0, Phi, YY...
  SetV0(V0);
  fq.close();

  // Create data file name
  char FileName [256];
  sprintf(FileName, "%s/LGE%c_%3.0f_%3.2f_%3.2f_%3.2f.dat",DataDir, Axis,V0,P,Q,Beta);

  fstream fdat (FileName, ios::in);

  // Create arrays
  MaxDim = 10000;
  Vmin = new double [MaxDim];
  T0 = new double [MaxDim];
  Tm = new double [MaxDim];
  Phiv = new double [MaxDim];
  
  // If file doesnt exist, warning and fill arrays with 0
  if (!fdat) 
  {
    cout << "WARNING!!! File " << FileName << " DOESNT EXIST" << endl;
    bzero (Vmin,MaxDim*sizeof(double));
    bzero (T0,MaxDim*sizeof(double));
    bzero (Tm,MaxDim*sizeof(double));
    bzero (Phiv,MaxDim*sizeof(double));
  }
  else 
  {
    while (!fdat.eof())
    {
      fdat >> Vmin[i] >> T0[i] >> Tm[i] >> Phiv[i];
      if (fdat.eof()) break;
      i++;
      if (i==MaxDim) break;
    }
    MaxDim=i;
  }

  return 0;
  
}

// Return the Halo model distribution int (f(v)/v^2)
// Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
double DMHaloLGE::T (double vmin, double * S0, double * Sm, double * phi )
{
  // GET DATA FROM ARRAYS
  if (vmin>MaxDim || vmin<1 ) { *S0=0; *Sm=0; *phi=Phi; return(0);}

  int index = (int)floor(vmin);
  double frac = vmin - index;

  * S0 = T0[index-1] + frac * (T0[index]-T0[index-1]); 
  * Sm = Tm[index-1] + frac * (Tm[index]-Tm[index-1]); 
  * phi = Phiv[index-1] + frac * (Phiv[index]-Phiv[index-1]); 
}
