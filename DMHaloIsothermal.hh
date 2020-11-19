/**********************************
 * Maria Martinez 08-11-05
 * Class DMHaloIsothermal
 * Form factor virtual mother class
 *********************************/

#ifndef __DM__HaloIsothermal__hh__
#define __DM__HaloIsothermal__hh__

#include "DMVHaloModel.hh"
#include <fstream>
using namespace std;


class DMHaloIsothermal : public DMVHaloModel
{
  protected:
    // Isothermal halo variables
    double VEsc; // Escape velocity in km/s
    double ZZ;   // ZZ = VESC / V0
    
  public:
    // Constructor, copy constructor, destructor
    DMHaloIsothermal();
    DMHaloIsothermal(const DMHaloIsothermal & other);
    virtual ~DMHaloIsothermal();

    // Initialize parameters from file
    int Initialize(char * fileName);

    // Returns the Halo model distribution integral(f(v)/v)
    // Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
    // Input: vmin in km/s
    double T (double vmin, double * S0, double * Sm, double * phi );

}; // End of Class DMHaloIsothermal declaration

  
#endif 
