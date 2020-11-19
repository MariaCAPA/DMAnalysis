/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROODMINTEG
#define ROODMINTEG

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooRealVar.h"
#include "RooAbsCategory.h"

 
class DMRate;
class RooDMInteg : public RooAbsReal {
public:
  RooDMInteg() {} ; 
  RooDMInteg(const char *name, const char *title,
          RooAbsReal& _sSI,
          RooAbsReal& _mW,
          RooAbsReal& _exposure);

  RooDMInteg(const RooDMInteg& other, const char* name=0) ;

//  RooDMInteg& operator=(const RooDMInteg& other);


  virtual TObject* clone(const char* newname) const { return new RooDMInteg(*this,newname); }

  inline virtual ~RooDMInteg() { }

  int initialize(const char * fileRate, Double_t eIni, Double_t eEnd);

protected:

  RooRealProxy exposure ;
  RooRealProxy sSI ;
  RooRealProxy mW ;


  DMRate * fDMRate;
  Double_t eneIni;
  Double_t eneEnd;
  
  Double_t evaluate() const ;



private:

  ClassDef(RooDMInteg,1) // Your description goes here...
};
 
#endif
