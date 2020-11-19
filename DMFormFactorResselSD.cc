/**********************************
 * Maria Martinez 08-11-05
 * Class DMFormFactorResselSD
 * Form factor spin dependent
 *********************************/
#include <iostream>
#include "DMFormFactorResselSD.hh"
#include "DMPhysConstants.hh"
#include <math.h>

// Constructor, copy constructor, destructor
DMFormFactorResselSD::DMFormFactorResselSD()
{
}
DMFormFactorResselSD::DMFormFactorResselSD(const DMFormFactorResselSD & other):
DMVFormFactor(other),A(other.A), A0(other.A0), A1(other.A1), MN(other.MN)
{

}
DMFormFactorResselSD::~DMFormFactorResselSD()
{
}

// Initialize parameters from file
// TODO: include Z number in initialization to distinguiss among isobars
int DMFormFactorResselSD::Initialize(double a, double theta)
{
  A = a;
  MN=A*mNucleon;
  A0 = cos(theta) +  sin(theta);
  A1 = cos(theta) -  sin(theta);

  return 0;
}

// Return the squared form factor for energy
// TODO: include Z number in initialization to distinguiss among isobars
double DMFormFactorResselSD::F2 (double energy)
{
  double b_factor; 
  double y, y2, y3, y4, y5, y6, y7, y8, S00, S01, S11, S0,exp2y;
 
  if (A==127.) // assume I127 Bonn-A
  {
    // Units: MeV-1
    b_factor=1./86.4718;
    y=MN*b_factor*b_factor/2.*energy;
    y2 =  y*y;    y3 = y2*y;
    y4 = y3*y;    y5 = y4*y;
    y6 = y5*y;    y7 = y6*y;
    y8 = y7*y;
    exp2y = exp(2*y); 

    // CUT VALUE
    if (y>10) return (0);

    S00 = 0.0983393470867778/exp2y - 0.489096*y/exp2y +
          1.140199838536073*y2/exp2y -
          1.47168*y3/exp2y +
          1.171696230336817*y4/exp2y -
          0.564574*y5/exp2y +
          0.1582874329440406*y6/exp2y -
          0.0238874*y7/exp2y +
          0.001542518017266915*y8/exp2y;

    S01 = 0.1199404045469431/exp2y - 0.618424*y/exp2y +
          1.508929990979145*y2/exp2y -
          2.07367*y3/exp2y +
          1.77307126057402*y4/exp2y -
          0.903597*y5/exp2y +
          0.2600198911184635*y6/exp2y -
          0.0387025*y7/exp2y +
          0.002356749893541029*y8/exp2y;

    S11 = 0.03657086832326849/exp2y - 0.194994*y/exp2y +
          0.5048764907242186*y2/exp2y -
          0.747451*y3/exp2y +
          0.7043440972366082*y4/exp2y -
          0.393018*y5/exp2y +
          0.1218808582677593*y6/exp2y -
          0.0191881*y7/exp2y +
          0.001210212919226947*y8/exp2y;

    S0 =  A0*A0*0.0983393470867778+A0*A1*0.1199404045469431+
          A1*A1*0.03657086832326849;

/*
    //  Nijmegen II

    S00 = 0.1166302926028242/exp2y - 0.572149*y/exp2y +
          1.337968179785889*y2/exp2y -
          1.72517*y3/exp2y +
          1.377417056400153*y4/exp2y -
          0.669986*y5/exp2y +
          0.1905217312688953*y6/exp2y -
          0.0291803*y7/exp2y +
          0.001908102710708012*y8/exp2y

    S01 = 0.1620541553846288/exp2y - 0.836288*y/exp2y +
          2.059437741131643*y2/exp2y -
          2.83193*y3/exp2y +
          2.397263106611574*y4/exp2y -
          1.21214*y5/exp2y +
          0.3486119081711927*y6/exp2y -
          0.0521813*y7/exp2y +
          0.003207310100111171*y8/exp2y

    S11 = 0.05628703534871887/exp2y - 0.303825*y/exp2y +
          0.7947833950753289*y2/exp2y -
          1.17027*y3/exp2y +
          1.063734012799804*y4/exp2y -
          0.571342*y5/exp2y +
          0.1721971591569158*y6/exp2y -
          0.0266165*y7/exp2y +
          0.001662382463022109*y8/exp2y

    S0 = A0*A0*0.1166302926028242+A0*A1*0.1620541553846288+
          A1*A1*0.05628703534871887
*/

    return (A0*A0*S00+A1*A1*S11+A0*A1*S01)/S0;
  }

  else if (A==23.) // assume Na23 Bonn-A
  {
    b_factor=1./117.01;
    y=MN*b_factor*b_factor/2.*energy; // y=(qb/2)^2, q2 = 2*energy*MN
    y2 = y*y;   y3 = y2*y;

    if(y>0.1875) return (0.);

    S00=0.0379935 - 0.174341*y + 0.378299*y2 - 0.342962*y3;
    S01=0.0646525 - 0.350289*y + 0.910031*y2 - 0.985833*y3;
    S11=0.0275013 - 0.169641*y + 0.507868*y2 - 0.617985*y3;
    S0=A0*A0*0.0379935+A0*A1*0.0646525+A1*A1*0.0275013;

    return (A0*A0*S00+A1*A1*S11+A0*A1*S01)/S0;
  }

  else if (A==27) // assume Al27
  {
    b_factor=1./114.06; // MeV-1  -> 1.73 fm
    y=MN*b_factor*b_factor/2.*energy; // y=(qb/2)^2, q2 = 2*energy*MN -> y = energy*MN*b^2/2
    y2 = y*y;   y3 = y2*y;
    
    S00 = 0.0930 - 0.4721*y + 1.0600*y2 - 1.0115*y3;
    S11 = 0.0657 - 0.4498*y + 1.3504*y2 - 1.6851*y3;
    S01 = 0.1563 - 0.9360*y + 2.4578*y2 - 2.7262*y3;

    S0=A0*A0*0.0930+A0*A1*0.1563+A1*A1*0.0657; // S0 for q = 0

    return (A0*A0*S00+A1*A1*S11+A0*A1*S01)/S0;
  }

  else if (A==7) // assume Li7
  {
    // approx  FF-> 1
    return (1);
  }  

  else
  {
    //cout << "Nucleus not implemented" << endl;
    return (0);
  }
}
