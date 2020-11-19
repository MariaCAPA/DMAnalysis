/**********************************
 * Maria Martinez 05/10/15
 * Class DMExclusionBin
 * Class to perform exclusion. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 * Do exclusion bin by bin
 *********************************/

#include "DMExclusionBin.hh"
#include "DMRate.hh"
#include "DMUtil.hh"
#include <sstream>
#include <string.h>
using namespace std;

// Conctructor
DMExclusionBin::DMExclusionBin ():DMExclusion()
{
}
 
// Destructor
DMExclusionBin::~DMExclusionBin()
{
}


// Returns maximum allowed nucleon cross section spin independent and spin dependent
// in picobarns for the given Wimp mass, the experimental 
// spectrum and the theoretical spectrum to the given CL.
int DMExclusionBin::GetMaxCrossSection(double mW, double cl, double * ssi, double * ssd)
{
  // Loop in energy bins, calculate crossection and return the minimum
  int i=0;
  *ssi = 9999999999.;
  *ssd = 9999999999.;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);

  TheoSpc = new double [Nbins];
  double * modSpc = new double [Nbins];
  double * phi = new double [Nbins];

  double maxExRate;

  // Spin Independent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(1.); 
  TheoRate->SetSigSD(0.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, TheoSpc, modSpc, phi);

  // Loop in bins. Get the lowest of the sigmaSI values, bin by bin
  for (i=ini; i<end; i++) 
  {
    // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.
    double nCounts = ExpSpc[i]*Ebin*Exposure;

    // CONSIDER THE CL
    DMGetMaxCountsCL(nCounts, cl, &maxExRate);

    double theoTotalRate = TheoSpc[i]*Ebin*Exposure;

    // Get spin independent nucleon cross section
    double ssiAux = maxExRate / theoTotalRate; // In picobarns
 
    if (ssiAux<(*ssi)) *ssi = ssiAux;
  }

  // Spin Dependent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(0.); 
  TheoRate->SetSigSD(1.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, TheoSpc, modSpc, phi);

  for (i=ini; i<end; i++) 
  {
    // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.
    double nCounts = ExpSpc[i]*Ebin*Exposure;

    // CONSIDER THE CL
    DMGetMaxCountsCL(nCounts, cl, &maxExRate);

    double theoTotalRate = TheoSpc[i]*Ebin*Exposure;

    // Get spin independent nucleon cross section
    double ssdAux = maxExRate / theoTotalRate; // In picobarns
 
    if (ssdAux<(*ssd)) *ssd = ssdAux;

  }

  delete [] TheoSpc;
  TheoSpc = 0;
  delete [] modSpc;
  delete [] phi;

  return 0;
}

