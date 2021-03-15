/**********************************
 * Maria Martinez 19/05/06
 * Class DMSensitivity
 * Class to perform sensitivity plot. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 * Calculates the sensitivity following formule 16 of Astrop Phys 14 82001) 339
 * bk is an estimated bkg (MC or an hypothetical one)! It is not the measured one 
 *********************************/

#ifndef __DM__Sensitivity__hh__
#define __DM__Sensitivity__hh__

#include <fstream>
#include "DMVSensitivity.hh"

class DMRate;

class DMSensitivity: public DMVSensitivity
{
  public:

  // Conctructor
  DMSensitivity ();
 
  // Destructor
  virtual ~DMSensitivity();

  // Returns maximum allowed nucleon cross section SI and SD
  // in picobarns for the given Wimp mass, the experimental 
  // backgrouond and the theoretical spectrum to the given delta2
  virtual int GetMaxCrossSection(double mW, double delta2, double * ssi, double * ssd);
  virtual double GetMaxCrossSection(double mW, double delta2, int ssi, int ssd, double theta);

  private:
  // For the sigma calculus
  double F(double sig);
  double FPrima(double sig);

}; // End of class DMSensitivity declaration

#endif 
