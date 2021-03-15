/**********************************
 * Maria Martinez 12/03/12
 * Class DMSensitivityPlotHandle
 * Plot manager for a DMSensitivity class
 *********************************/

#ifndef __DM__SensitivityPlotHandle__hh__
#define __DM__SensitivityPlotHandle__hh__

#include "DMVSensitivity.hh"
#include "DMVPlotHandle.hh"

class TGraph;
class TTree;

class DMSensitivityPlotHandle: public DMVPlotHandle
  {

  protected:
  // Pointer to sensitivity class
  DMVSensitivity * fSensitivity;
  
  public:

  // Conctructor
  DMSensitivityPlotHandle ();
  DMSensitivityPlotHandle (DMVSensitivity * sensitivity);
 
  // Destructor
  virtual ~DMSensitivityPlotHandle();

  // Return parameters
  inline DMVSensitivity * GetSensitivityObj () {return fSensitivity;};
  inline void SetSensitivity (DMVSensitivity *sensitivity) {fSensitivity = sensitivity;};

  ///////////////////
  // Plot functions

  // Get the Spin independent and spin dependent sensitivity curve in a TGraph 
  // Units: MW (GeV) Sigma (pb)
  TGraph * GetSensitivity(double iniM = 1, double endM=1e3, int ssi=1, int ssd=0, double theta=0);
  TGraph * GetSISensitivity(double iniM = 1, double endM=1e3);
  TGraph * GetSDSensitivity(double iniM = 1, double endM=1e3, double theta=0);
  TGraph * GetSDpSensitivity(double iniM = 1, double endM=1e3);
  TGraph * GetSDnSensitivity(double iniM = 1, double endM=1e3);

  // Get a TTree with all the calculated vars. 
  TTree * GetAllVars(double iniM=1, double endM=1e3);

  // Dump vars to file
  int Dump(char * fileName,double iniM=1, double endM=1e3);

}; // End of class DMSensitivityPlotHandle

#endif 
