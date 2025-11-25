/**********************************
 * Maria Martinez 08-11-05
 * Class DMFlux
 * Isothermal Halo Model
 *********************************/
#include "DMFlux.hh"
#include "DMPhysConstants.hh"
#include "DMUtil.hh"
#include <iostream>
#include <sstream>
#include <math.h>
#include <string.h>

// Constructor, copy constructor, destructor
DMFlux::DMFlux()
{
}
DMFlux::DMFlux(const DMFlux & other):
DMVHaloModel(other)
{
  VFlux[0] = other.VFlux[0];
  VFlux[1] = other.VFlux[1];
  VFlux[2] = other.VFlux[2];

  VDis = other.VDis;
  VEsc = other.VEsc;
  ZZ = other.ZZ;
  SetV0(other.V0);  
  
}
DMFlux::~DMFlux()
{
}

// Initialize parameters from file
int DMFlux::Initialize(char * fileName)
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
    else if (!strcmp(dummy,"VFLUX"))  srLine >> VFlux[0]  
                                             >> VFlux[1]  
                                             >> VFlux[2] ;
    else if (!strcmp(dummy,"VDIS"))  srLine >> VDis;
    
  }
  // Set V0, Phi, YY...
  SetV0(V0);

  ZZ = VEsc / (SQRT_2_3 * VDis);

  fq.close();

  return 0;
}

// Return the Halo model distribution int (f(v)/v^2)
// Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
double DMFlux::T (double vmin, double * S0, double * Sm, double * phi )
{
  double x = vmin / VDis; 
  *S0 = Chi(x, YYMean, ZZ)/VDis;
  *Sm = ( Chi(x, YYMax, ZZ) - Chi(x, YYMin, ZZ) ) / 2. / VDis;

  // phase
  *phi = Phi;

  return 0;
}

void DMFlux::SetV0(double v0)
{
  V0 = v0;
  int i=0;
  double vFluxToSun[3]; // Flux velocity relative to sun

  vFluxToSun[0] = sunPeculiar_0 - VFlux[0];
  vFluxToSun[1] = sunPeculiar_1 + V0 - VFlux[1];
  vFluxToSun[2] = sunPeculiar_2 - VFlux[2];

  // w1 = |Vearth| e1*vFluxToSun
  double w1 = earthSpeed * (earthE1_0*vFluxToSun[0] + 
                            earthE1_1*vFluxToSun[1] + 
                            earthE1_2*vFluxToSun[2] );
  // w2 = |Vearth| e2*vFluxToSun
  double w2 = earthSpeed * (earthE2_0*vFluxToSun[0] + 
                            earthE2_1*vFluxToSun[1] + 
                            earthE2_2*vFluxToSun[2] );
  // wT2 = VFluxToSun^2 + Vearth^2
  double wT2 = vFluxToSun[0]*vFluxToSun[0] +  
               vFluxToSun[1]*vFluxToSun[1] +  
               vFluxToSun[2]*vFluxToSun[2] +
               earthSpeed2; 

  double delta = sqrt(w1*w1 + w2*w2);

  YYMax = sqrt (wT2 + 2 * delta)/VDis;  
  YYMin = sqrt (wT2 - 2 * delta)/VDis;  
  YYMean = sqrt (wT2)/VDis;  

  // 2Pi(phase-earthT0) = asin (w1/sqrt(w1^2+w2^2)
  double sinMax = w1/delta;
  double cosMax = -w2/delta;
  Phi = asin(sinMax);
  if (cosMax<0) Phi = PI - Phi;
  // Phi/2pi -> year fraction
  Phi = Phi/TWOPI + earthT0; // years
}
