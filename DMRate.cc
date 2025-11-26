/**********************************
 * Maria Martinez 08/11/05
 * Class DMRate
 * Rate for a compound Target
 *********************************/
#include "DMUtil.hh"
#include "DMRate.hh"
#include "DMElement.hh"
#include "DMVHaloModel.hh"
#include "DMHaloIsothermal.hh"
#include "DMHaloLGE.hh"
#include "DMFlux.hh"
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include "TMath.h"

// Conctructor
DMRate::DMRate ():
NElements(0),Elements(0),NHaloModels(0),HaloModels(0)
{
  Resolution=0;
  ResolutionK=0;
  ResolutionA=0;
  ResolutionB=0;
}


// Copy constructor
DMRate::DMRate(const DMRate &other):
NElements(other.NElements), Mol(other.Mol), NHaloModels(other.NHaloModels), SigSI(other.SigSI), SigSD(other.SigSD),
Theta(other.Theta), MW(other.MW), MWnucleon2(other.MWnucleon2), Resolution(other.Resolution), ResolutionK(other.ResolutionK) , ResolutionA(other.ResolutionA), ResolutionB(other.ResolutionB)
{
  int i=0;
  // Halo models
  if (other.HaloModels)
  {
    HaloModels = new DMVHaloModel * [NHaloModels];
    for (i=0; i<NHaloModels;i++)
    {
      if (DMHaloIsothermal * pt = dynamic_cast<DMHaloIsothermal*>(other.HaloModels[i]))
        HaloModels[i] = new DMHaloIsothermal(*pt);
      else if (DMHaloLGE * pt = dynamic_cast<DMHaloLGE*>(other.HaloModels[i]))
        HaloModels[i] = new DMHaloLGE(*pt);
      else if (DMFlux * pt = dynamic_cast<DMFlux*>(other.HaloModels[i]))
        HaloModels[i] = new DMFlux(*pt);
      else {std::cout << " Halo model not implemented. Error. " << std::endl; HaloModels[i]=0;}
    }
  }
  else HaloModels = 0; 

  // Elements 
  if (other.Elements)
  {
    Elements = new DMElement * [NElements];
    for (i=0; i<NElements; i++) 
      Elements[i] = new DMElement(*other.Elements[i]);
  } 
  else Elements = 0;

}
 
// Destructor
DMRate::~DMRate()
{
  int i=0;
  if (Elements!=0) 
  {
    for (i=0;i<NElements;i++) delete Elements[i];
    delete [] Elements;
  }

  if (HaloModels!=0) 
  {
    for (i=0;i<NHaloModels;i++) delete HaloModels[i];
    delete [] HaloModels;
  }
}

// Read data from file
int DMRate::Initialize(char * fileName)
{
  int retval=0;
  std::string parsed = DMParseShellVars(fileName);
  fstream fq (parsed.c_str(), ios::in);
  char line [256];
  char dummy[256];
  char typch[256];
  int i=0, typ;

  double nat; // double, to acconut for isotopes
  Mol=0;
  if (!fq.good()) 
  {
    std::cout << "Cannot open file " << parsed.c_str() << std::endl;
    return -1;
  }
  while (!fq.eof())
  {
    fq.getline(line, 240);
    if (fq.eof()) break;
    stringstream srLine(stringstream::in | stringstream::out);
    srLine << line;
    if (line[0]=='#') continue;
    srLine >> dummy;

    if      (!strcmp(dummy,"SIGSI"))  srLine >> SigSI;
    else if (!strcmp(dummy,"SIGSD"))  srLine >> SigSD;
    else if (!strcmp(dummy,"THETA"))  srLine >> Theta;
    else if (!strcmp(dummy,"MW"))  {srLine >> MW; SetMW(MW);}
    // MARIA 180620. new var in cfg file: resolution  -> cte with energy.
    // Internally, put it negative. It means that it is cte
    else if (!strcmp(dummy,"RESOLUTIONK"))  srLine >> ResolutionK;
    else if (!strcmp(dummy,"RESOLUTION")) { srLine >> Resolution;}
    else if (!strcmp(dummy,"RESOLUTIONAB")) { srLine >> ResolutionA >> ResolutionB;}
    else if (!strcmp(dummy,"NELEMENTS"))  
    {
      srLine >> NElements;
      Elements = new DMElement * [NElements];
      for (i=0; i<NElements; i++)
      {
        fq  >> nat >> dummy;
        Elements[i] = new DMElement();
        retval = Elements[i]->Initialize(dummy);
        if (retval<0) return retval;
        Elements[i]->SetNAtoms(nat);
        Mol += nat*Elements[i]->GetA();
      } 
    }
    else if (!strcmp(dummy,"NHALOMODELS"))  
    {
      srLine >> NHaloModels;
      HaloModels = new DMVHaloModel * [NHaloModels];
      for (i=0; i<NHaloModels; i++)
      {
        fq  >> typch >> dummy;
        
        if (!strcmp(typch, "ISO"))
            HaloModels[i] = new DMHaloIsothermal();
        else if (!strcmp(typch, "LGE"))
            HaloModels[i] = new DMHaloLGE();
        else if (!strcmp(typch, "FLUX"))
            HaloModels[i] = new DMFlux();
        else
        {
            std::cout << "WARNING: Halo model " << typch << " not implemented. Using Isothermal sphere " << std::endl;
            HaloModels[i] = new DMHaloIsothermal();
        }
        retval = HaloModels[i]->Initialize(dummy);
        if (retval<0) return retval;
      }
    }
  } // end while
  fq.close();

  // Set spin factor for the elements
  for (i=0; i<NElements; i++) 
  {
    Elements[i]->SetSpinFactor(Theta);
    Elements[i]->SetTheta(Theta);
  }

  // printf resolution model
  if (Resolution>0) std::cout << " cte resolution. Sigma = " << Resolution << " keV " << std::endl;
  else if (ResolutionK>0)  std::cout << " sigma = " << ResolutionK << " * sqrt(ene) (keV) " << std::endl; 
  else if (ResolutionA>0)  std::cout << " sigma = sqrt( " << ResolutionA << " * ene + " << ResolutionB << " ) (keV) " << std::endl; 
  else std::cout << " Resolution not taken into account " << std::endl;
  return 0;
}
void DMRate::SetParams (double mw, double si, double sd, double theta)
{
  SigSI=si;
  SigSD=sd;
  Theta=theta;
  SetMW(mw);
  for (int i=0; i<NElements; i++) 
  {
    Elements[i]->SetSpinFactor(theta);
    Elements[i]->SetTheta(theta);
  }
}

// Compute the Rate for energy energy (in keVee (keV electron equivalent ))
// edep = energy/Quenching
// Returns Mean rate, modulated rate in counts/Kg/keV
// and phase of the maximum (in days)
int DMRate::Rate (double energy_ee, double * S0Tot, double * SMTot, double * PhiTot)
{
  int el, hal;
  double fraction;
  double aux1, aux2;
  double edep;
  double sigff_si=0; double sigff_sd=0;
  *S0Tot = 0; *SMTot = 0; *PhiTot = 0;
  double S0El = 0; double SMEl = 0; double PhiEl = 0;
  double S0, SM, Phi;
  double ref;

  // Loop in elements
  for (el=0;el<NElements;el++)
  {
    S0El = 0; SMEl = 0; PhiEl = 0;

    // energy_ee: Energy in keV electron equivalent. Calculate energy deposited
    ref = Elements[el]->GetREF(energy_ee);
    if (ref<=0) ref=0.001; // Consider a very low value to avoid infinites
    edep = energy_ee/ref;
 
    // spin independent contribution
    if (SigSI!=0) sigff_si = 
      SigSI*Elements[el]->GetA()*Elements[el]->GetA()* Elements[el]->FF2SI(edep);
    // spin dependent contribution
    if (SigSD!=0) sigff_sd = 
      SigSD*Elements[el]->GetSpinFactor()* Elements[el]->FF2SD(edep);

    // halo contribution
    for (hal=0; hal<NHaloModels; hal++)
    {
      HaloModels[hal]->T(Elements[el]->Vmin(edep,MW), &S0, &SM, &Phi);


      // Convet from years to radians
      //Phi *= DAYTORAD;
      Phi *= YEARTORAD;

      // Scale with halo density
      S0 *= HaloModels[hal]->GetRho();
      SM *= HaloModels[hal]->GetRho();

      // Add Sm (vector) and S0 (scalar)
      DMAddVect(&SMEl, &PhiEl, SM, Phi);
      S0El  += S0;
    } 

    // Add element contributions, scaled with fraction 
    fraction = Elements[el]->GetNAtoms()*Elements[el]->GetA();
    S0El *= fraction/ref*(sigff_si + sigff_sd);
    SMEl *= fraction/ref*(sigff_si + sigff_sd);

    DMAddVect(SMTot, PhiTot, SMEl, PhiEl);
    *S0Tot    += S0El;
  }

  // Scale factor independent of the element
  // Units: (keV kg day)^-1
  *S0Tot = (*S0Tot)*234140./MW/MWnucleon2/Mol;
  *SMTot = (*SMTot)*234140./MW/MWnucleon2/Mol;

  // Phase in years
  //(*PhiTot) *= RADTODAY;
  (*PhiTot) *= RADTOYEAR;

  // ADD NAN CONTROL
  if (TMath::IsNaN(*S0Tot)) *S0Tot = 0;
  if (TMath::IsNaN(*SMTot)) *SMTot = 0;
  if (TMath::IsNaN(*PhiTot)) *PhiTot = 0;

  return 0;
}

// Gives the Sprectrum from  e1 to e2 in bins of ebin keVee. 
// Takes into account the resolution
// Input: energy initial, final and size of bin (in keVee)
// Output: Unmodulated and modulated rate and phi
//         Arrays of dim (e1-e2)/ebin

double DMRate::GetSigma(double ene)
{
  if (Resolution>0) return Resolution;
  if (ResolutionK>0)  return ResolutionK*sqrt(ene); 
  if (ResolutionA>0) return sqrt(ResolutionA * ene + ResolutionB);
  return 0;

}

int DMRate::SpectrumResolution (double e1, double e2, double ebin, 
                                double * S0, double * Sm, double * phi)
{
  double PRECISION = 0.0001; // Maximum precision
  double minEne = 0.001;
  int ind;
  double ei, edif, en; // loop variables
  double ef, estep, en1, en2, ens; // interval variables
  double S01, SM1, PHI1, NORM1, S02, SM2, PHI2, NORM2; // Integral var.
  double weight; int indArray;


  //////////////// NO RESOLUTION: NO CONVOLUTION
  ind = 0;
  //if (fabs(ResolutionK)<=PRECISION)
  if (Resolution==0 && ResolutionK==0 && ResolutionA==0)
  {
    for (ei=e1; ei < e2; ei+=ebin)
    {
      Rate (ei+ebin/2., &S0[ind], &Sm[ind], &phi[ind]); 
      ind++;
    }
    return 0;
  }

  // Number of bins in the auxiliar array
  int arrayDim = 400;
  int nSig = 5; // Number of +-sigma of the convolution interval

  // Compute auxiliar array with the rates. From e1-nSig*sigma (or 0.1) to e2+nSig*sigma 
  //double auxsig = (ResolutionK<0 ? -nSig*ResolutionK : nSig*ResolutionK*sqrt(e1)); 
  double auxsig = nSig*GetSigma(e1);
  double arrayEi   = (e1-auxsig < minEne ? minEne : e1-auxsig); 
  double arrayEf   = e2;
  //if (ResolutionK<0) arrayEf -= nSig * ResolutionK;
  //else arrayEf += nSig * ResolutionK * sqrt (e2);
  arrayEf += nSig*GetSigma(e2);
  double arrayEbin = ( arrayEf - arrayEi ) / arrayDim; 

  // Auxiliar arrays with the rates (Unmodulated, modulated, phase)
  double*  array_S0  = new double [arrayDim];
  double*  array_SM  = new double [arrayDim];
  double*  array_Phi = new double [arrayDim];

  ei = arrayEi;
  for (ind=0; ind<arrayDim; ind++)
  {
    ei +=  arrayEbin; 
    Rate (ei, &array_S0[ind], &array_SM[ind], &array_Phi[ind]); 

    //array_Phi[ind] *= DAYTORAD;
    array_Phi[ind] *= YEARTORAD;
  }

  // Loop ei in the number of output bins
  ind = 0;
  for (ei=e1; ei < e2; ei+=ebin)
  {
    // PRECISION CONTROL
    if ( fabs(e2-ei)<PRECISION )  break;

    ef = ei + ebin;
    estep = (ef - ei) / 20.;

    // initialize integrating variables
    S01 = 0; 
    SM1 = 0; 
    PHI1 = 0; 
    NORM1 = 0; 
    
    // Loop edif: integral in the bin ei-ef
    for (edif=ei; edif<=ef; edif+= estep)
    {
      //auxsig = (ResolutionK<0 ? -nSig*ResolutionK : nSig*ResolutionK*sqrt(edif)); 
      auxsig = nSig*GetSigma(edif);
      en1 = (edif - auxsig < minEne ? minEne : edif - auxsig);
      en2 = edif + auxsig;
      ens = (en2 - en1)/100.;
      // Initialize integrating variables
      S02   = 0; 
      SM2   = 0; 
      PHI2  = 0; 
      NORM2 = 0; 

      // Control of 0 resolution
      if (auxsig==0) 
      {
        indArray = (int)((edif - arrayEi)/arrayEbin);
        S02 = array_S0[indArray];
        SM2 = array_SM[indArray];
        PHI2 = array_Phi[indArray];
        NORM2 = 1;
        en2 = 0;
      }
      
      // Loop en: Gaussian convolution
      for (en=en1; en<=en2; en+=ens) 
      {
        //auxsig = (ResolutionK<0 ? -ResolutionK : ResolutionK*sqrt(en));
        auxsig = GetSigma(en);
        weight = exp (-(edif-en)*(edif-en)/2./auxsig/auxsig) / auxsig;

        // Look for the index corresponding to en in the rate array
        indArray = (int)((en - arrayEi) / arrayEbin);
        
        // Integrate
        //MARIA: Mas adelante se puede hacer una integracion trapezoidal...
        S02 += weight * array_S0[indArray];
        DMAddVect(&SM2, &PHI2, weight*array_SM[indArray], array_Phi[indArray]);
        NORM2 += weight;

      } // end of en loop
      
      // Integrate
      S01 += S02/NORM2;
      DMAddVect(&SM1, &PHI1, SM2/NORM2, PHI2);
      NORM1++;
      
    } // end of edif loop

    // Fill the output arrays
    S0 [ind] = S01/NORM1;
    Sm [ind] = SM1/NORM1; 

    // Maria 04-01-06 Output in years
    //phi[ind] = PHI1 * RADTODAY;
    phi[ind] = PHI1 * RADTOYEAR;
    ind++;
    

  } // End of ei loop

  delete [] array_S0;
  delete [] array_SM;
  delete [] array_Phi;
  
  return 0;
} 

// energy in keVee
// time in days
// result is in c/kg 
double DMRate::IntegRate(double eMin_ee, double eMax_ee, double tMin, double tMax, double eBin)
{
  double ee;
  double S0, Sm, Phi;
  double retval=0;
  double Phi_d; // phi in days 

  // Integrate with trapezoid rule 

  // integ[e1,eN]f(x)dx = ebin/2 *(f(e1) + f(eN) + 2*Sum[e2,eN-1](f(i)) ) 

  Rate(eMin_ee, &S0, &Sm, &Phi);
  Phi_d = Phi*365; // Phi is in years
  retval += 0.5*(S0*(tMax-tMin) + Sm*(sin(DAYTORAD*(tMax-Phi_d)) - sin(DAYTORAD*(tMin-Phi_d)))/DAYTORAD); 

  Rate(eMax_ee, &S0, &Sm, &Phi);
  Phi_d = Phi*365; // Phi is in years
  retval += 0.5*(S0*(tMax-tMin) + Sm*(sin(DAYTORAD*(tMax-Phi_d)) - sin(DAYTORAD*(tMin-Phi_d)))/DAYTORAD); 

  for (ee=eMin_ee+eBin; ee<eMax_ee; ee+=eBin)
   {
     Rate(ee, &S0, &Sm, &Phi);

     Phi_d = Phi*365; // Phi is in years


     // For every energy bin, integrate the modulated part
     // Integral of Sm * cos(DAYTORAD*(time - Phi_d)) ;

     retval += S0*(tMax-tMin) + Sm*(sin(DAYTORAD*(tMax-Phi_d)) - sin(DAYTORAD*(tMin-Phi_d)))/DAYTORAD; 

   }

   retval *= eBin;

   return retval;
}

