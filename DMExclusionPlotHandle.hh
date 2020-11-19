/**********************************
 * Maria Martinez 12/03/12
 * Class DMExclusionPlotHandle
 * Plot manager for a DMExclusion class
 *********************************/

#ifndef __DM__ExclusionPlotHandle__hh__
#define __DM__ExclusionPlotHandle__hh__

#include "DMExclusion.hh"
#include "DMVPlotHandle.hh"

class TGraph;
class TTree;

class DMExclusionPlotHandle: public DMVPlotHandle
  {

  protected:
  // Pointer to exclusion class
  DMExclusion * fExclusion;
  
  public:

  // Conctructor
  DMExclusionPlotHandle ();
  DMExclusionPlotHandle (DMExclusion * exclusion);
 
  // Destructor
  virtual ~DMExclusionPlotHandle();

  // Return parameters
  inline DMExclusion * GetExclusionObj () {return fExclusion;};
  inline void SetExclusion (DMExclusion *exclusion) {fExclusion = exclusion;};

  ///////////////////
  // Plot functions

  // Get the Spin independent and spin dependent exclusion curve in a TGraph 
  // Units: MW (GeV) Sigma (pb)
  TGraph * GetSDpExclusion(double iniM, double endM, int minInt=0);
  TGraph * GetSDnExclusion(double iniM, double endM, int minInt=0);
  TGraph * GetSDExclusion(double iniM, double endM, double theta, int minInt=0);
  TGraph * GetSIExclusion(double iniM, double endM, int minInt=0);
  TGraph * GetExclusion(double iniM, double endM, double si, double sd, double theta, int minInt=0);

  // Get a TTree with all the calculated vars. 
  TTree * GetAllVars(double iniM=1, double endM=1e3);

  // Dump vars to file
  int Dump(char * fileName,double iniM=1, double endM=1e3);

}; // End of class DMExclusionPlotHandle

#endif 





