/**********************************
 * Maria Martinez 12/03/12
 * Class DMRatePlotHandle
 * Plot manager for a DMRate class
 *********************************/

#ifndef __DM__RatePlotHandle__hh__
#define __DM__RatePlotHandle__hh__

#include "DMRate.hh"
#include "DMVPlotHandle.hh"

class TH1F;
class TTree;

class DMRatePlotHandle : public DMVPlotHandle
  {

  protected:
  // Pointer to rate class
  DMRate * fRate;
  
  public:

  // Conctructor
  DMRatePlotHandle ();
  DMRatePlotHandle (DMRate * rate);
 
  // Destructor
  virtual ~DMRatePlotHandle();

  // Return parameters
  inline DMRate * GetRateObj () {return fRate;};
  inline void SetRate (DMRate *rate) {fRate = rate;};

  ///////////////////
  // Plot functions

  // Get the expected rate in a TH1F (nBins, Eini, Eend) 
  // Energy in keV
  TH1F * GetRate(int nBins=100, double Eini=0, double Eend=100);
  TH1F * GetSIRate(double mw, double sigma, int nBins=100, double Eini=0, double Eend=100);
  TH1F * GetSDpRate(double mw, double sigma, int nBins=100, double Eini=0, double Eend=100);
  TH1F * GetSDnRate(double mw, double sigma, int nBins=100, double Eini=0, double Eend=100);

  // Get the expected modulated rate in a TH1F (nBins, Eini, Eend) 
  // Energy in keV
  TH1F * GetModulatedRate(int nBins=100, double Eini=0, double Eend=100);

  // Get a TTree with all the calculated vars. 
  // Energy in keV
  TTree * GetAllVars(int nBins=100, double Eini=0, double Eend=100);

  // Dump calculated vars to file
  // Energy in keV
  int Dump(char* fileName, int nBins=100, double Eini=0, double Eend=100);

  // AUXILIAR FUNCITONS
  int MakeVars(std::string & vars);
  
}; // End of class DMRatePlotHandle

#endif 
