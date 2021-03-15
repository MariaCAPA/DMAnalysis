/**********************************
 * Maria Martinez 19/05/06
 * Class DMVSensitivity
 * Class to perform exclusion. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 *********************************/

#ifndef __DM__VSensitivity__hh__
#define __DM__VSensitivity__hh__

#include <fstream>

class DMRate;

class DMVSensitivity
{
  protected:
    
  DMRate * TheoRate; // Class to obtain the theoretical spectrum
  double Exposure;   // kg*days of exposition
  double Delta2;   // Delta squared value for the sensitivity computation
  double Eini;  // Initial energy of the experimental spectrum in keVee
  double Eend;  // Final energy of the experimental spectrum in keVee
  double Ebin;  // energy bin of the experimental spectrum  in keVee
  double EWini;  // Energy threshold of the energy window to compute 
                 // the exclusion, in keVee
  double EWend;  // Energy end of the energy window to compute 
                 // the exclusion, in keVee
  int Nbins;     // Number of bins = (Eend - Eini)/Ebin
  int NWbins;     // Number of bins in window= (EWend - EWini)/Ebin
  double * Background; // Array with the background 
                   // in counts/bin/kg/day. Dim Nbins
  double * S0; // Array with the theoretical spectrum S0
                    // in counts/bin/kg/day. Dim Nbins
  double * Sm; // Array with the modulated theoretical spectrum Sm
                    // in counts/bin/kg/day. Dim Nbins

  public:

  // Conctructor
  DMVSensitivity ();
 
  // Destructor
  virtual ~DMVSensitivity();

  // Return parameters
  DMRate * GetTheoRate() {return TheoRate;};
  double GetExposure() {return Exposure;}; 
  double GetDelta2() {return Delta2;};   
  double GetEini() {return Eini;}; 
  double GetEend() {return Eend;};
  double GetEWini() {return EWini;}; 
  double GetEWend() {return EWend;};
  double GetEbin() {return Ebin;};
  int    GetNbins() {return Nbins;};
  int    GetNWbins() {return NWbins;};

  double * GetBackground() {return Background;};
  double * GetS0() {return S0;};
  double * GetSm() {return Sm;};

  // Set parameters
  void SetTheoRate(DMRate * aux) {TheoRate = aux;};
  void SetExposure(double aux)   {Exposure = aux;}; 
  void SetDelta2      (double aux)   {Delta2 = aux;};   
  void SetEWini    (double aux)  {EWini = (aux<Eini ? Eini : aux);NWbins = (EWend-EWini)/Ebin;}; 
  void SetEWend    (double aux)  {EWend = (aux>Eend ? Eend : aux);NWbins = (EWend-EWini)/Ebin;};
  void SetBackground  (double * aux) {Background = aux;};
  void SetS0 (double * aux) {S0 = aux;};
  void SetSm (double * aux) {Sm = aux;};


  // auxiliar, same as SetEWini, SetEWend. For pratical use..
  void SetThreshold (double thresholdkeV)  {SetEWini(thresholdkeV);};
  void SetWindow (double ei, double ef)  {SetEWini(ei); SetEWend(ef);};

  void SetLinearBkg (double bkg_ckgd); // set linear bkg in c/keV/kg/d

  // Initialize class. initialize Rate class from file
  virtual int Initialize(char * file);


  // Set the energy window and an experimental spectrum 
  // equal to a linear background (1count/keV/kg/day by default)
  // Energy in keVee, background in counts/keV/kg/day
  void SetBackground(double ei, double ef, double ebin, double bck=1);

  // Set the energy window and the experimental spectrum 
  // copying it from the array pointed by spc 
  // Energy in keVee, spectrum in counts/bin/kg/day
  void SetBackground(double ei, double ef, double ebin, double * spc);

  // Set the energy window and an background spectrum 
  // from file
  // Energy in keVee, background in counts/bin/kg/day
  void SetBackground(double ei, double ef, double ebin, char * bckFile);


  // Get Maximum experimental number of counts for CL
  double GetMaxBackground(double cl);

  // Returns maximum allowed nucleon cross section SI and SD
  // in picobarns for the given Wimp mass, the experimental 
  // backgrouond and the theoretical spectrum to the given delta2
  virtual int GetMaxCrossSection(double mW, double delta2, double * ssi, double * ssd)=0;
  virtual double GetMaxCrossSection(double mW, double delta2, int ssi, int ssd, double theta)=0;


}; // End of class DMVSensitivity declaration

#endif 
