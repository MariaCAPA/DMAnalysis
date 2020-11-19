/**********************************
 * Maria Martinez 12/03/12
 * Class DMVPlotHandle
 * Virtual mother class for PlotHandle objects
 *********************************/

#ifndef __DM__VPlotHandle__hh__
#define __DM__VPlotHandle__hh__

#include "DMVPlotHandle.hh"
#include <iostream>

class TH1F;
class TTree;

class DMVPlotHandle 
  {

  protected:

  double fScaleY;
  double fScaleX;
  std::string massUnit;
  
  public:

  void SetpbScale(bool val=1)  {if (val) fScaleY=1; else fScaleY=1e-36;}
  void Setcm2Scale(bool val=1) {if (val) fScaleY=1e-36; else fScaleY=1;}

  void SetTeVScale(bool val=1)  {if (val) {massUnit="TeV"; fScaleX=1e-3;}}
  void SetGeVScale(bool val=1)  {if (val) {massUnit = "GeV"; fScaleX=1;}}
  void SetMeVScale(bool val=1)  {if (val) {massUnit = "MeV"; fScaleX=1e3;}}


  // Conctructor
  DMVPlotHandle ();
 
  // Destructor
  virtual ~DMVPlotHandle();

  // AUXILIAR FUNCITONS

  // Dump tree contents in filename fileName
  int Dump(char * fileName, TTree * t);

  
}; // End of class DMVPlotHandle

#endif 
