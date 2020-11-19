/**********************************
 * Maria Martinez 05/10/15
 * Class DMExclusionBin
 * Class to perform exclusion. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 * Exclusion done bin by bin
 *********************************/

#ifndef __DM__ExclusionBin__hh__
#define __DM__ExclusionBin__hh__

#include <fstream>
#include "DMExclusion.hh"

class DMRate;

class DMExclusionBin : public DMExclusion
{
  protected:
    
  public:

  // Conctructor
  DMExclusionBin ();
 
  // Destructor
  virtual ~DMExclusionBin();

  // Returns maximum allowed nucleon cross section SI and SD
  // in picobarns for the given Wimp mass, the experimental 
  // spectrum and the theoretical spectrum to the given CL.
  int GetMaxCrossSection(double mW, double cl, double * ssi, double * ssd);

}; // End of class DMExclusionBin declaration

#endif 
