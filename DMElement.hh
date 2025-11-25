/**********************************
 * Maria Martinez 08-11-05
 * Class DMElement
 * Element, and Form factor
 *********************************/

#ifndef __DM__Element__hh__
#define __DM__Element__hh__

#include "DMVFormFactor.hh"
#include <fstream>
#include <math.h>
#include <TGraph.h>
using namespace std;

#define MAXELEM 10


/************************
 * CLASS ELEMENT
 ************************/
class DMVFormFactor; 

class DMElement
{
  protected:
    double Z; 
    double A;
    double J;
    double Sp;
    double Sn;
    double REF;
    double NAtoms;
    double SpinFactor; // 4/3(J+1)/J(Sp Costheta+Sn Sintheta)^2
    double Theta;

    DMVFormFactor * FFSI;
    DMVFormFactor * FFSD;
 
  // auxiliar
    double MN; // Nuclear mass

  public:
// Constructor, copy constructor, destructor
    DMElement();
    DMElement(const DMElement & el);
    virtual ~DMElement();

    double GetZ() {return Z;}; 
    double GetA() {return A;}; 
    double GetJ() {return J;}; 
    double GetSp() {return Sp;}; 
    double GetSn() {return Sn;}; 
    double GetNAtoms () {return NAtoms;}; 
    double GetMN ()  {return MN;};
    double GetSpinFactor ()  {return SpinFactor;};
    double GetTheta ()  {return Theta;};

    // MARIA 070313. function for ref variable with 
    // energy. If there is not a TGraph with Q=Q(Eee), then 
    // return constant REF
    //double GetREF () {return REF;}; 
    double GetREF (double Eee);

    void SetZ  (double z)  {Z=z;}; 
    void SetA  (double a)  {A=a;}; 
    void SetJ  (double j)  {J=j;}; 
    void SetSp (double sp) {Sp=sp;}; 
    void SetSn (double sn) {Sn=sn;}; 
    void SetREF(double ref){REF = ref;delete gREF;gREF=0;};
    void SetREF(TGraph * g){gREF = g;};
    void SetNAtoms(double na){NAtoms = na;};
    void SetTheta(double th){Theta = th;SetSpinFactor(Theta);FFSD->Initialize(A,Theta);};
    
    // Returns spin independent form factor squared. (Energy in keV)
    double FF2SI (double e)
    { return FFSI->F2(e); }

    // Returns spin dependent form factor squared. (Energy in keV)
    double FF2SD (double e)
    { return FFSD->F2(e); }

    // Read parameters from file
    int Initialize (char * fileName );

    // Returns R factor. mW in GeV
    inline double RFactor (double mW) 
    {
      return  4*mW*MN/(mW+MN)/(mW+MN);
    }
   
    // Returns minimum velocity that produces a recoil of energy energy_ee
    // input : Energy in keV, Mass in GeV
    // output: velocity in km/s
    inline double Vmin (double energy, double mW)
    {
       return ( 300.*sqrt(2*energy/mW/RFactor(mW)) );
    }

    // Set spin factor for given theta (in radians)
    inline void SetSpinFactor (double theta)
    {
      if (J==0) SpinFactor=0;
      else 
      {
        double aux = Sp*cos(theta) + Sn * sin(theta);
        SpinFactor = 4./3.*(J+1)/J*aux*aux;
      }
    }


    // MARIA 070313. TGraph for REF variable with Eee
    TGraph * gREF;
}; // End of Class DMElement declaration

#endif 
