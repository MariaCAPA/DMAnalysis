/**********************************
 * Maria Martinez 08-11-05
 * Class DMVFormFactor
 * Form factor virtual mother class
 *********************************/

#ifndef __DM__VFormFactor__hh__
#define __DM__VFormFactor__hh__

using namespace std;

class DMVFormFactor
{
  protected:

  public:
    // Constructor, copy constructor, destructor
    DMVFormFactor();
    DMVFormFactor(const DMVFormFactor & other);
    virtual ~DMVFormFactor();

    // Initialize parameters 
    virtual int Initialize(double a, double b)=0;
    //virtual int Initialize(double a);

    // Return the squared form factor for energy
    // It must be defined for every daughter class
    // energy in keV
    virtual double F2 (double energy)=0;
    //virtual double F2 (double energy);

}; // End of Class DMVFormFactor declaration

  
#endif 
