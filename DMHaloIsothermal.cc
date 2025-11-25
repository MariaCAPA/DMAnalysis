/**********************************
 * Maria Martinez 08-11-05
 * Class DMHaloIsothermal
 * Isothermal Halo Model
 *********************************/
#include "DMHaloIsothermal.hh"
#include "DMUtil.hh"
#include <iostream>
#include <sstream>
#include <string.h>


// Constructor, copy constructor, destructor
DMHaloIsothermal::DMHaloIsothermal()
{
}
DMHaloIsothermal::DMHaloIsothermal(const DMHaloIsothermal & other):
DMVHaloModel(other)
{
  VEsc = other.VEsc;
  ZZ = other.ZZ;  
}
DMHaloIsothermal::~DMHaloIsothermal()
{
}

// Initialize parameters from file
int DMHaloIsothermal::Initialize(char * fileName)
{
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
    else if (!strcmp(dummy,"VESC"))  srLine >> VEsc;
  }
  // Set V0, Phi, YY...
  SetV0(V0);

  ZZ = VEsc / V0;

  fq.close();


  return 0;
}

// Return the Halo model distribution int (f(v)/v^2)
// Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
double DMHaloIsothermal::T (double vmin, double * S0, double * Sm, double * phi )
{
  double x = vmin / V0; 
  *S0 = Chi(x, YYMean, ZZ)/V0;
  *Sm = ( Chi(x, YYMax, ZZ) - Chi(x, YYMin, ZZ) ) / 2. / V0;

  // phase
  *phi = Phi;

  return 0;
}
