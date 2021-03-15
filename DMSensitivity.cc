/**********************************
 * Maria Martinez 16/11/05
 * Class DMSensitivity
 * Class to perform a sensitivity plot. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 *********************************/

#include "DMSensitivity.hh"
#include "DMRate.hh"
#include "DMUtil.hh"
#include <sstream>
#include <string.h>
using namespace std;

// Conctructor
DMSensitivity::DMSensitivity ()
{
  TheoRate  = 0;
  Background  = 0;
  S0 = 0;
  Sm = 0;
  Nbins   = 0;
}
 
// Destructor
DMSensitivity::~DMSensitivity()
{
  if (TheoRate) delete TheoRate;
  if (Background) delete Background;
  if (S0) delete S0;
  if (Sm) delete Sm;
}
// Returns maximum allowed nucleon cross section for si (when si==1) or
// sd (when sd==1) and given theta
// in picobarns for the given Wimp mass, the experimental 
// spectrum and the theoretical spectrum to the given CL.
double DMSensitivity::GetMaxCrossSection(double mW, double delta2, int ssi, int ssd, double theta)
{
  Delta2=delta2;
  // CHECK
  if (! ((ssi==1 && ssd==0) || (ssi==0 && ssd==1)))
  { 
    std::cout << " use for ssi=1 and ssd = 0 or viceversa!" << std::endl;
    return 0;
  }
  int i=0;
  double sum = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);


  // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.

  // Spin Independent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM for sigma=1
  S0 = new double [Nbins];
  Sm = new double [Nbins];
  double * phi = new double [Nbins];
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(ssi); 
  TheoRate->SetSigSD(ssd); 
  for (int iel=0; iel<TheoRate->GetNElements(); iel++)
    TheoRate->GetElement(iel)->SetTheta(theta);

  TheoRate->SpectrumResolution(Eini, Eend, Ebin, S0, Sm, phi);

  // sigma initial guess (approx sigmaS0k<<bk)
  // sum_k Sm^2/bk
  for (i=ini; i<end; i++) sum += Sm[i]*Sm[i]/Background[i];


  double sig0 = sqrt((2*Delta2-4)/sum/Exposure/Ebin);

  // Newton's method.  iterations sign+1 = sign - f(sign)/fprima(sign)
  int nit =5; 
  for(i=0; i<nit; i++)
  {
    // DEB 
    //cout << sig0 << " "  << F(sig0) << " " << FPrima(sig0) << endl;
    sig0 = sig0 - F(sig0)/FPrima(sig0);
  }

//std::cout << " mw " << mW << " Sm in counts approx: " << Exposure*(EWend-EWini)*(*ssi)*fabs(Sm[0]) << " bkg at " << EWini  << " keV " << Background[i] << std::endl;


  delete [] S0;
  S0 = 0;
  delete [] Sm;
  Sm = 0;
  delete [] phi;
  phi=0;

  return sig0;
}

// Returns maximum allowed nucleon cross section spin independent and spin dependent
// in picobarns for the given Wimp mass, the experimental 
// spectrum and the theoretical spectrum to the given CL.
int DMSensitivity::GetMaxCrossSection(double mW, double delta2, double * ssi, double * ssd)
{
  Delta2=delta2;
  int i=0;
  double sum = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);


  // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.

  // Spin Independent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM for sigma=1
  S0 = new double [Nbins];
  Sm = new double [Nbins];
  double * phi = new double [Nbins];
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(1.); 
  TheoRate->SetSigSD(0.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, S0, Sm, phi);

  // sigma initial guess (approx sigmaS0k<<bk)
  // sum_k Sm^2/bk
  for (i=ini; i<end; i++) sum += Sm[i]*Sm[i]/Background[i];


  double sig0 = sqrt((2*Delta2-4)/sum/Exposure/Ebin);

  // Newton's method.  iterations sign+1 = sign - f(sign)/fprima(sign)
  int nit =5; 
  for(i=0; i<nit; i++)
  {
    // DEB 
    //cout << sig0 << " "  << F(sig0) << " " << FPrima(sig0) << endl;
    sig0 = sig0 - F(sig0)/FPrima(sig0);
  }

  // Get spin independent nucleon cross section
  (*ssi) = sig0; // In picobarns

//std::cout << " mw " << mW << " Sm in counts approx: " << Exposure*(EWend-EWini)*(*ssi)*fabs(Sm[0]) << " bkg at " << EWini  << " keV " << Background[i] << std::endl;

  // Spin Dependent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(0.); 
  TheoRate->SetSigSD(1.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, S0, Sm, phi);

  // sigma initial guess (approx sigmaS0k<<bk)
  // sum_k Sm^2/bk
  sum=0;
  for (i=ini; i<end; i++) sum += Sm[i]*Sm[i]/Background[i];

  sig0 = sqrt((2*Delta2-4)/sum/Exposure/Ebin);

  // Newton's method.  iterations sign+1 = sign - f(sign)/fprima(sign)
   nit = 5;
  for(i=0; i<nit; i++)
  {
    sig0 = sig0 - F(sig0)/FPrima(sig0);
  }

  // Get spin independent nucleon cross section
  (*ssd) = sig0; // In picobarns


  delete [] S0;
  S0 = 0;
  delete [] Sm;
  Sm = 0;
  delete [] phi;
  phi=0;

  return 0;
}

double DMSensitivity::F(double sig)
{
  int i=0;
  double sum = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);
  for (i=ini; i<end; i++) sum+=Sm[i]*Sm[i]/(Background[i]+S0[i]*sig);
  return Delta2 - 2 - sum*sig*sig/2.*Exposure*Ebin;
}
double DMSensitivity::FPrima(double sig)
{
  int i=0;
  double sum1 = 0;
  double sum2 = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);
  for (i=ini; i<end; i++)
  {
    sum1+=Sm[i]*Sm[i]/(Background[i]+S0[i]*sig);
    sum2+=S0[i]*Sm[i]*Sm[i]/(Background[i]+S0[i]*sig)/(Background[i]+S0[i]*sig);
  }
  return -Exposure*Ebin/2.*(2.*sum1* sig - sum2*sig*sig);
}
