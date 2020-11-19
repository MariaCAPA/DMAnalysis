/**********************************
 * Maria Martinez 08-11-05
 * Class DMFlux
 * Flux DM with velocity Vx Vy Vz in galactic coordinates, 
 *  Vel dispersion Vdis
 *********************************/

#ifndef __DM__Flux__hh__
#define __DM__Flux__hh__

#include "DMVHaloModel.hh"
#include <fstream>
using namespace std;

class DMFlux : public DMVHaloModel
{
  protected:
    // flux variables
    double VFlux [3]; //Flux velocity in Galactic coordinates in km/s
    double VDis; // Flux dispersion velocity in km/s
    double VEsc; // Escape velocity in km/s
    double ZZ;   // ZZ = VESC / V0
    
  public:
    // Constructor, copy constructor, destructor
    DMFlux();
    DMFlux(const DMFlux & other);
    virtual ~DMFlux();

    // Set V0 value (virtual function)
    void SetV0(double v0);

    // Initialize parameters from file
    int Initialize(char * fileName);

    // Returns the velocity distribution integral(f(v)/v)
    // Output: S0-> mean distrib. Sm-> modulated, phi-> phase of the max(days)
    // Input: vmin in km/s
    double T (double vmin, double * S0, double * Sm, double * phi );

}; // End of Class DMFlux declaration

  
#endif 
