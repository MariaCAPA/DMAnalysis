/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROODMPDF
#define ROODMPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class DMRate;
 
class RooDMPdf : public RooAbsPdf {
public:
  RooDMPdf() {} ; 
  RooDMPdf(const char *name, const char *title,
	      RooAbsReal& _energy,
	      RooAbsReal& _sSI,
	      RooAbsReal& _mW);
  RooDMPdf(const RooDMPdf& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooDMPdf(*this,newname); }
  virtual ~RooDMPdf();

  int initialize(const char * fileRate);
  void setTimeInterval(double tini, double tend) {tIni=tini; tEnd=tend;};

  //virtual Double_t	expectedEvents(const RooArgSet& nset) const;

protected:

  RooRealProxy energy ;
  RooRealProxy  sSI ;
  RooRealProxy  mW ;

  DMRate * fDMRate;
  Double_t tIni; 
  Double_t tEnd; 

  // Return S0 (unmodulated part)
  // If time interval is set (it checks that tEnd > tIni)
  // add the integral over time of the modulated part
  Double_t evaluate() const ;


private:

  ClassDef(RooDMPdf,1) // Your description goes here...
};
 
#endif
