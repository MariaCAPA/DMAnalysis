/**********************************
 * Maria Martinez 19/05/06
 * Class DMSensitivityiToData
 * Class to perform sensitivity plot. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 * Calculates the sensitivity following formule 16 of Astrop Phys 14 82001) 339
 * bk is a MEASURED BKG (so bk = bk' + S0)
 *********************************/

#ifndef __DM__SensitivityToData__hh__
#define __DM__SensitivityToData__hh__

#include <fstream>
#include "DMVSensitivity.hh"

class DMRate;

class DMSensitivityToData: public DMVSensitivity
{
  protected:
 
  double * fEfficiency;
    
  public:

  // Conctructor
  DMSensitivityToData ();
 
  // Destructor
  virtual ~DMSensitivityToData();

  int Initialize (char * file);

  // Efficiency of the measured bkg. Bins must be the same as bkg
  void SetEfficiency(double eff);

  // Efficiency of the measured bkg. Bins must be the same as bkg
  void SetEfficiency(char * effFile);


  // Overload mother class function
  // Returns maximum allowed nucleon cross section SI and SD
  // in picobarns for the given Wimp mass, the experimental 
  // backgrouond and the theoretical spectrum to the given delta2
  int GetMaxCrossSection(double mW, double delta2, double * ssi, double * ssd);

}; // End of class DMSensitivityToData declaration

#endif 
