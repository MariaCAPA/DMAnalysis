/**********************************
 * Maria Martinez 08-11-05
 * Class DMFormFactorHelmSI
 * Form factor SI 
 *********************************/
#include "DMFormFactorHelmSI.hh"
#include "DMPhysConstants.hh"
#include <math.h>
#include <iostream>


// Constructor, copy constructor, destructor
DMFormFactorHelmSI::DMFormFactorHelmSI()
{
}
DMFormFactorHelmSI::DMFormFactorHelmSI(const DMFormFactorHelmSI & other):
DMVFormFactor(other), RParam(other.RParam), BParam(other.BParam), SSquared(other.SSquared), MNucleo(other.MNucleo)
{
}
DMFormFactorHelmSI::~DMFormFactorHelmSI()
{
}

// Initialize parameters from file. a: Mass number. b: not used
int DMFormFactorHelmSI::Initialize(double a, double b)
{
  if (a<=6) std::cout << " ******** WARNING!! Helm FF aprox not valid for A<=6 !!!" << std::endl;
  MNucleo  = a*mNucleon;
  SSquared = 1; // femto squared
  RParam   = 1.2*pow(a,_1_3); // femto
  BParam   = sqrt (RParam*RParam - 5 * SSquared); // in femto

  return 0;
}

// Return the squared form factor for energy (in keV)
double DMFormFactorHelmSI::F2 (double energy)
{
   if (energy==0) return 1;
   // Transferred momentum squared in MeV^2
   double q2 = 2*MNucleo*energy; 

   // h_c in MeV * femto
   double aux = BParam*sqrt(q2)/h_c; // adimensional

   double aux2 = 3*SBessel1(aux)/aux*exp(-SSquared*q2/h_c/h_c/2.); // MARIA 022822, factor 2 missing
   return (aux2*aux2);
}
