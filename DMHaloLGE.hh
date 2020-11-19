/**********************************
 * Maria Martinez 24/05/06
 * Class DMHaloLGE
 * Form factor virtual mother class
 *********************************/

#ifndef __DM__HaloLGE__hh__
#define __DM__HaloLGE__hh__

#include "DMVHaloModel.hh"
#include <fstream>
using namespace std;


class DMHaloLGE : public DMVHaloModel
{
  protected:
    // LGE halo variables
    double P;  // b/a
    double Q;  // c/a
    double Beta;  // anisotropy factor beta = 1 - (sz2+zphi2)/2/sr2
    char Axis; // L -> Long axis, I -> Intermediate axis

    int MaxDim;

    // ARRAYS WITH THE T INTEGRALS READ FROM FILE
    double * Vmin;  
    double * T0;
    double * Tm;
    double * Phiv;
    
  public:
    // Constructor, copy constructor, destructor
    DMHaloLGE();
    DMHaloLGE(const DMHaloLGE & other);
    virtual ~DMHaloLGE();

    // Initialize parameters from file
    int Initialize(char * fileName);

    // Returns the Halo model distribution integral(f(v)/v)
    // Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
    // Input: vmin in km/s
    double T (double vmin, double * S0, double * Sm, double * phi );

}; // End of Class DMHaloLGE declaration

  
#endif 
