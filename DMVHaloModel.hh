/**********************************
 * Maria Martinez 08-11-05
 * Class DMVHaloModel
 * Form factor virtual mother class
 *********************************/

#ifndef __DM__VHaloModel__hh__
#define __DM__VHaloModel__hh__

#include <fstream>
using namespace std;

typedef enum {IS0, FLUX} EnumHaloModels;


class DMVHaloModel
{
  protected:
  EnumHaloModels HaloType;
  double Rho; // Halo density in GeV/cm^3
  double V0;  // V0 velocity in km/s
  double Phi; // Phase of the maximum (in years)
              // Is computed every time V0 is set.
  double YYMax; // VMax/V0. (Vel max of the earth respect to the halo)
  double YYMin; // VMax/V0. (Vel max of the earth respect to the halo)
  double YYMean; // VMean/V0. (mean Vel of the earth respect to the halo)
              // Computed every time V0 is set.

  public:
    // Constructor, copy constructor, destructor
    DMVHaloModel();
    DMVHaloModel(const DMVHaloModel & el);
    virtual ~DMVHaloModel();

    // Return parameters
    double GetRho() {return Rho;}
    double GetV0() {return V0;}
    double GetPhi() {return Phi;}

    // Set parameters
    void SetRho(double rho) {Rho=rho;}

    // Set V0 and compute Phi (phase of the maximum in years)
    // EtaMax and EtaMin
    virtual void SetV0(double v0); 

    // Initialize parameters from file
    virtual int Initialize(char * fileName)=0;

    // Return the Halo model distribution int (f(v)/v^2)
    // Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
    // It must be defined for every daughter class
    virtual double T (double vmin, double * S0, double * Sm, double * phi )=0;

    // Return Chi function
    double Chi (double x, double y, double z);

}; // End of Class DMVHaloModel declaration

  
#endif 
