/**********************************
 * Maria Martinez 08-11-05
 * Class DMFormFactorResselSD
 * Form factor virtual mother class
 *********************************/
#ifndef __DM__FormFactorResselSD__hh__
#define __DM__FormFactorResselSD__hh__

#include "DMVFormFactor.hh"
#include <fstream>
//using namespace std;

//class DMVFormFactor;

class DMFormFactorResselSD : public DMVFormFactor
{
  protected:
    // Form Factor SD variables
    double A; // Mass number
    double A0; // cos(theta) + sin(theta) 
    double A1; // cos(theta) - sin(theta)
    double MN; // Nucleus mass

  public:
    // Constructor, copy constructor, destructor
    DMFormFactorResselSD();
    DMFormFactorResselSD(const DMFormFactorResselSD & other);
    virtual ~DMFormFactorResselSD();

    // Initialize parameters.
    int Initialize(double a, double theta);

    // Returns the squared form factor for energy (in keV)
    double F2 (double energy);

}; // End of Class DMFormFactorResselSD declaration
  
#endif 
