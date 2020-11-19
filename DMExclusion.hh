/**********************************
 * Maria Martinez 16/11/05
 * Class DMExclusion
 * Class to perform exclusion. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 *********************************/

#ifndef __DM__Exclusion__hh__
#define __DM__Exclusion__hh__

#include <fstream>

class DMRate;

class DMExclusion
{
  protected:
    
  DMRate * TheoRate; // Class to obtain the theoretical spectrum
  double Exposure;   // kg*days of exposition
  double CL;   // Confident level (in %) for the exclusion
  double Eini;  // Initial energy of the experimental spectrum in keVee
  double Eend;  // Final energy of the experimental spectrum in keVee
  double Ebin;  // energy bin of the experimental spectrum  in keVee
  double EWini;  // Energy threshold of the energy window to compute 
                 // the exclusion, in keVee
  double EWend;  // Energy end of the energy window to compute 
                 // the exclusion, in keVee
  int Nbins;     // Number of bins = (Eend - Eini)/Ebin
  int NWbins;     // Number of bins in window= (EWend - EWini)/Ebin
  double * ExpSpc; // Array with the experimental spectrum 
                   // in counts/bin/kg/day. Dim Nbins
  double * TheoSpc; // Array with the theoretical spectrum
                    // in counts/bin/kg/day. Dim Nbins

  public:

  // Conctructor
  DMExclusion ();
 
  // Destructor
  virtual ~DMExclusion();

  // Return parameters
  DMRate * GetTheoRate() {return TheoRate;};
  double GetExposure() {return Exposure;};  // kg*days
  double GetCL() {return CL;};   
  double GetEini() {return Eini;}; 
  double GetEend() {return Eend;};
  double GetEWini() {return EWini;}; 
  double GetEWend() {return EWend;};
  double GetEbin() {return Ebin;};
  int    GetNbins() {return Nbins;};
  int    GetNWbins() {return NWbins;};
  double * GetExpSpc() {return ExpSpc;};
  double * GetTheoSpc() {return TheoSpc;};

  // Set parameters
  void SetTheoRate(DMRate * aux) {TheoRate = aux;};
  void SetExposure(double kgDays)   {Exposure = kgDays;}; 
  void SetCL      (double cl)   {CL = cl;};   
  void SetEWini    (double thresholdkeV)  {EWini = (thresholdkeV<Eini ? Eini : thresholdkeV);NWbins = (EWend-EWini)/Ebin;}; 
  void SetEWend    (double eEnd)  {EWend = (eEnd>Eend ? Eend : eEnd);NWbins = (EWend-EWini)/Ebin;};
  void SetExpSpc  (double * aux) {ExpSpc = aux;};
  void SetTheoSpc (double * aux) {TheoSpc = aux;};

  // auxiliar, same as SetEWini, SetEWend. For pratical use..
  void SetThreshold (double thresholdkeV)  {SetEWini(thresholdkeV);};
  void SetWindow (double ei, double ef)  {SetEWini(ei); SetEWend(ef);};
  void SetLinearBkg (double bkg_ckgd); // set linear bkg in c/keV/kg/d


  // Initialize class. initialize Rate class from file
  int Initialize(char * file);


  // Set the energy window and an experimental spectrum 
  // equal to a linear background (1count/keV/kg/day by default)
  // Energy in keVee, background in counts/keV/kg/day
  void SetExpSpc(double ei, double ef, double ebin, double bck=1);

  // Set the energy window and the experimental spectrum 
  // copying it from the array pointed by spc (count/keV/kg/day by default)
  // Energy in keVee, spectrum in counts/bin/kg/day
  void SetExpSpc(double ei, double ef, double ebin, double * spc);
  
  // Set the energy window and an experimental spectrum 
  // from file
  // Energy in keVee, background in counts/bin/kg/day
  void SetExpSpc(double ei, double ef, double ebin, char * bckFile);


  // Get Maximum experimental number of counts for CL
  double GetMaxExpRate(double cl);

  // Get integrated theoretical rate form TheoSpc
  // in the energy window
  double GetTheoTotalRate();

  // Get experimental and predicted integrals for bins 
  // between i0 and i1, starting from 0 , NWbin bins
  void GetRates(int i0, int i1, double &exp, double &theo);

  // Returns maximum allowed nucleon cross section SI and SD
  // in picobarns for the given Wimp mass, the experimental 
  // spectrum and the theoretical spectrum to the given CL.
  virtual int GetMaxCrossSection(double mW, double cl, double * ssi, double * ssd);

  // minInt -> minimum number of bins to be considered together when 
  // computing the optimum interval 
  // If minInt == 0, the method reduces to the standard one
  double GetOptMaxCrossSectionSI(double mW, double cl, int minInt=0);
  double GetOptMaxCrossSectionSDp(double mW, double cl, int minInt=0);
  double GetOptMaxCrossSectionSDn(double mW, double cl, int minInt=0);
  double GetOptMaxCrossSectionSD(double mW, double cl, double theta, int minInt=0);
  
  // auxiliar
  double GetOptMaxCrossSection(double mW, double cl, double si, double sd, double theta, int minInt=0);


}; // End of class DMExclusion declaration

#endif 
