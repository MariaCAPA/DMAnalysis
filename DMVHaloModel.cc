/**********************************
 * Maria Martinez 08-11-05
 * Class DMVHaloModel
 * Halo Model virtual mother class
 *********************************/
#include <iostream>
#include "DMVHaloModel.hh"
#include "DMPhysConstants.hh"
#include <gsl/gsl_sf.h>
#include <gsl/gsl_math.h>

using namespace std;


// Constructor, copy constructor, destructor
DMVHaloModel::DMVHaloModel():
V0(0),Rho(0),Phi(0),YYMin(0),YYMax(0),YYMean(0)
{
}
DMVHaloModel::DMVHaloModel(const DMVHaloModel & other)
{
  Rho=other.Rho;
  SetV0(other.V0);
}
DMVHaloModel::~DMVHaloModel()
{
}

// Set V0 value and compute Phi (phase of the maximum)
// EtaMax = VMax/V0, EtaMin = VMin/V0

void DMVHaloModel::SetV0(double v0)
{
  V0 = v0;
  int i=0;
  double vSun [3] ;
  vSun[0] = sunPeculiar_0;
  vSun[1] = sunPeculiar_1 + V0;
  vSun[2] = sunPeculiar_2;

  // w1 = |Vearth| e1*Vsun
  double w1 = earthSpeed * (earthE1_0*vSun[0] + 
                            earthE1_1*vSun[1] + 
                            earthE1_2*vSun[2] );
  // w2 = |Vearth| e2*Vsun
  double w2 = earthSpeed * (earthE2_0*vSun[0] + 
                            earthE2_1*vSun[1] + 
                            earthE2_2*vSun[2] );
  // wT2 = VSun^2 + Vearth^2
  double wT2 = vSun[0]*vSun[0] +  
               vSun[1]*vSun[1] +  
               vSun[2]*vSun[2] +
               earthSpeed2; 

  double delta = sqrt(w1*w1 + w2*w2);

  YYMax = sqrt (wT2 + 2 * delta)/V0;  
  YYMin = sqrt (wT2 - 2 * delta)/V0;  
  YYMean = sqrt (wT2)/V0;  

  // 2Pi(phase-earthT0) = asin (w1/sqrt(w1^2+w2^2)
  double sinMax = w1/delta;
  double cosMax = -w2/delta;
  Phi = asin(sinMax);
  if (cosMax<0) Phi = PI - Phi;

  // Phi/2pi -> year fraction
  Phi = Phi/TWOPI + earthT0; // years
}

// Return Chi function
double DMVHaloModel::Chi (double x, double y, double z)
{
  double expz2 = exp(-z*z);
  double cte = 1./(gsl_sf_erf(z) - 2./SQRTPI*z*expz2);
  double aux = 0.;
  
  if (x>=0. && x<= z-y) 
    aux = gsl_sf_erf(x+y) - gsl_sf_erf(x-y) - 4./SQRTPI*y*expz2;
  else if (x>z-y && x<= z+y) 
    aux = gsl_sf_erf(z) - gsl_sf_erf(x-y) - 2./SQRTPI*(z+y-x)*expz2;

  return cte*aux/2./y;
}
