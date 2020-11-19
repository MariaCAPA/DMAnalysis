/**********************************
 * Maria Martinez 08/11/05
 * Class DMRate
 * Rate for a compound Target
 *********************************/

#ifndef __DM__Rate__hh__
#define __DM__Rate__hh__

#include "DMVHaloModel.hh"
#include "DMElement.hh"
#include "DMPhysConstants.hh"
#include <fstream>

//class DMVHaloModel;
//class DMElement;

class DMRate
  {
  protected:
  // Array of pointers to the elements of the target
  DMElement ** Elements;
  
  // Number of elements of the target
  int NElements;

  double Mol; // Molecular mass

  // Array of pointers to the halo models
  DMVHaloModel ** HaloModels;
  // Number of halo models
  int NHaloModels;

  double SigSI; // nucleon spin independent cross section in pbarns
  double SigSD; // nucleon spin dependent cross section in pbarns
  double Theta; // Angle theta Tan(theta)=an/ap. In radians (0 to pi)
  double MW;    // Wimp mass in GeV
  double MWnucleon2; // Reduced mass wimp-nucleon squared. Is set every time 
                    // MW is set

  // Detector resolution
  // if (ResolutinK>0) sigma = ResolutionK*sqrt(Energy)
  // else , sigma = -ResolutionK (cte in all the range)
  double ResolutionK; 
  
  public:

  // Conctructor
  DMRate ();

  // Copy constructor
  DMRate(const DMRate& other);
 
  // Destructor
  virtual ~DMRate();

  // Return parameters
  inline double GetSigSI () {return SigSI;};
  inline double GetSigSD () {return SigSD;};
  inline double GetTheta () {return Theta;};
  inline double GetMW () {return MW;};
  inline double GetMWnucleon2 () {return MWnucleon2;};
  inline double GetResolutionK () {return ResolutionK;}; 
  inline int GetNElements() {return NElements;};
  inline int GetNHaloModels() {return NHaloModels;};
  inline DMVHaloModel * GetHaloModel (int i) {return HaloModels[i];}
  inline DMElement * GetElement (int i) {return Elements[i];}

  // Set parameters
  void SetParams (double mw, double si, double sd, double theta);
  inline void SetSigSI (double aux) {SigSI=aux;};
  inline void SetSigSD (double aux) {SigSD=aux;};
  inline void SetTheta (double aux) {Theta=aux;};
  inline void SetMW (double aux) 
    {MW=aux; MWnucleon2=mNucleon*MW/(mNucleon+MW); MWnucleon2 *= MWnucleon2;};
  inline void SetResolutionK (double aux) {ResolutionK=aux;}; 

  // Read data from file
  int Initialize(char * fileName); 

  // Compute the Rate for energy energy (in keVee (keV electron equivalent ))
  // edep = energy/Quenching
  // Returns Mean rate, modulated rate in counts/Kg/keV
  // and phase of the maximum (in days)
  int Rate (double energy_ee, double * S0Tot, double * SMTot, double * PhiTot);


  // Compute the integrate rate between eMin_ee and eMax_ee and tMin and tMax
  // energy in keVee
  // time in days
  // result is in c/kg 
  double IntegRate(double eMin_ee, double eMax_ee, double tMin, double tMax, double eBin=0.1);

  // integrate the spectrum from e1 to e2.  takes into account the resolution
  int SpectrumResolution (double e1, double e2, double ebin,  double * S0, double * Sm, double * phi);  
	 
}; // End of class DMRate declaration

#endif 
