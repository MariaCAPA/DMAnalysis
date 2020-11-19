/**********************************
 * Maria Martinez 08-11-05
 * Class DMFormFactorHelmSI
 * Form factor virtual mother class
 *********************************/

#ifndef __DM__FormFactorHelmSI__hh__
#define __DM__FormFactorHelmSI__hh__

#include "DMVFormFactor.hh"
#include <fstream>
#include <math.h>
using namespace std;

class DMFormFactorHelmSI : public DMVFormFactor
{
  protected:
    // Form Factor SI variables
    double RParam;
    double BParam;
    double SSquared;
    double MNucleo;

  public:
    // Constructor, copy constructor, destructor
    DMFormFactorHelmSI();
    DMFormFactorHelmSI(const DMFormFactorHelmSI & other);
    virtual ~DMFormFactorHelmSI();

    // Initialize parameters. a: Mass number. b: not used
    int Initialize(double a, double b=0);

    // Return the squared form factor for energy (in keV)
    double F2 (double energy);

    // Returns Bessel function
    inline double SBessel1(double x) {return ((sin(x)-x*cos(x))/x/x);};

}; // End of Class DMFormFactorHelmSI declaration

  
#endif 
