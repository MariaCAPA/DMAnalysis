/**********************************
 * Maria Martinez 16/11/05
 * Class DMExclusion
 * Class to perform exclusion. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 *********************************/

#include "DMExclusion.hh"
#include "DMRate.hh"
#include "DMUtil.hh"
#include <sstream>
#include <string.h>
#include <limits>
using namespace std;

#define verylarge 1e30

// Conctructor
DMExclusion::DMExclusion ()
{
  TheoRate  = 0;
  ExpSpc  = 0;
  TheoSpc = 0;
  Nbins   = 0;
}
 
// Destructor
DMExclusion::~DMExclusion()
{
  if (TheoRate) delete TheoRate;
  if (ExpSpc) delete ExpSpc;
  if (TheoSpc) delete TheoSpc;
}

// Initialize class. initialize Rate class from fileName
int DMExclusion::Initialize(char * fileName)
{
  int retval=0;
  TheoRate = new DMRate();

  std::string parsed = DMParseShellVars(fileName);
  fstream fq (parsed.c_str(), ios::in);

  if (!fq.good())
  {
    std::cout << "Cannot open file " << parsed.c_str() << std::endl;
    return -1;
  }

  char line [256];
  char dummy[256];
  char rateFile[256];
  char bckFile[256];
  int flag=0;


  // Default Initial values
  double auxbackground = 1;
  Eini = EWini = 1;
  Eend = EWend = 10;
  Ebin = 1;

  while (!fq.eof())
  {
    fq.getline(line, 240);
    if (fq.eof()) break;
    //stringstream srLine(line, 256);
    stringstream srLine(stringstream::in | stringstream::out);
    srLine << line;
    if (line[0]=='#') continue;
    srLine >> dummy;

    if      (!strcmp(dummy,"RATEFILE"))  
    {
      srLine >> rateFile; 
      retval = TheoRate -> Initialize(rateFile);
      if (retval<0) return retval;
    }
    else if (!strcmp(dummy,"EXPOSURE"))  srLine >> Exposure;
    else if (!strcmp(dummy,"CL"))  srLine >> CL;
    else if (!strcmp(dummy,"LINBACKGROUND"))  {srLine >> auxbackground; }
    else if (!strcmp(dummy,"BACKGROUND"))  {srLine >> bckFile; flag=1;}
    else if (!strcmp(dummy,"EINI"))  {srLine >> Eini; EWini = Eini;}
    else if (!strcmp(dummy,"EEND"))  {srLine >> Eend; EWend = Eend;}
    else if (!strcmp(dummy,"EBIN"))  {srLine >> Ebin;}
    else if (!strcmp(dummy,"EWINI"))  {srLine >> EWini;}
    else if (!strcmp(dummy,"EWEND"))  {srLine >> EWend;}
  } // end while
  fq.close();
 
  // Set experimental spectrum
  if (flag==0) SetExpSpc(Eini, Eend, Ebin, auxbackground);
  else  SetExpSpc(Eini, Eend, Ebin, bckFile);

  return 0;
}

// Linear bkg, between Eini and Eend
// bkg  in c/keV/kg/d
void DMExclusion::SetLinearBkg(double bkg)
{
   // revision 513, it is not safe. Calculate Nbins
  //int Nbins = 100;
  Nbins = (int)((Eend - Eini) / Ebin ); 
  int i;
  if (ExpSpc!=0) delete ExpSpc;
  ExpSpc = new double [Nbins];
  for (i=0; i<Nbins; i++) ExpSpc[i] = bkg;
}

  
//  the energy window and an experimental spectrum 
// equal to a linear background (1count/keV/kg/day by default)
// Energy in keVee, background in counts/keV/kg/day
void DMExclusion::SetExpSpc(double ei, double ef, double ebin, double bck)
{
  Eini = ei;
  Eend = ef;
  Ebin = ebin;
  Nbins = (int)((Eend - Eini) / Ebin ); 
  int i;
  if (ExpSpc!=0) delete ExpSpc;
  ExpSpc = new double [Nbins];
  for (i=0; i<Nbins; i++) ExpSpc[i] = bck;
}

// Set the energy window and an experimental spectrum 
// equal to a linear background (1count/keV/kg/day by default)
// Energy in keVee, background in counts/bin/kg/day
void DMExclusion::SetExpSpc(double ei, double ef, double ebin, double * spc)
{
  Eini = ei;
  Eend = ef;
  Ebin = ebin;
  Nbins = (int)((Eend - Eini) / Ebin) ; 
  int i;
  if (ExpSpc!=0) delete ExpSpc;
  ExpSpc = new double [Nbins];
  for (i=0; i<Nbins; i++) ExpSpc[i] = spc[i]; 
}

// Set the energy window and an experimental background
// from file
// Energy in keVee, background in counts/bin/kg/day
void DMExclusion::SetExpSpc(double ei, double ef, double ebin, char * bckFile)
{
  Eini = ei;
  Eend = ef;
  Ebin = ebin;
  Nbins = (int)((Eend - Eini) / Ebin) ;
  int i;
  if (ExpSpc!=0) delete ExpSpc;
  ExpSpc = new double [Nbins];
  fstream fq (bckFile, ios::in);
  for (i=0; i<Nbins; i++)
  {
    fq >> ExpSpc[i];
    if (fq.eof()) {cout << "Warning: background file too short! " << endl; ExpSpc[i]=0;}
  }
}


// Get Maximum experimental number of counts for CL
double DMExclusion::GetMaxExpRate(double cl)
{
  int i=0;
  double total = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);
  
  // Integral: RECTANGLES
  for (i=ini; i<end; i++) total += ExpSpc[i]*Ebin;
  total *= Exposure; 

  // MARIA: TRAPEZOID RULE
  //for (i=ini+1; i<end; i++) total += ExpSpc[i];
  //total = 2*total + ExpSpc[ini] + ExpSpc[end];
  //total *= (EWend-EWini)/2./(end-ini)*Exposure; 

  // CONSIDER THE CL
  double nmax;
  DMGetMaxCountsCL(total, cl, &nmax);
//DEB
std::cout << " ini " << ini <<  " end " << end << " : " << total << " -> " << nmax << std::endl;

  return nmax;
}

// Get integrated theoretical rate form TheoSpc
// in the energy window
double DMExclusion::GetTheoTotalRate()
{
  int i=0;
  double total = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);
  
  // RECTANGLES
  for (i=ini; i<end; i++) total += TheoSpc[i]*Ebin;
  total *= Exposure; 

  // MARIA :TRAPEZOID RULE
  //for (i=ini+1; i<end; i++) total += TheoSpc[i];
  //total = 2*total + TheoSpc[ini] + TheoSpc[end];
  //total *= (EWend-EWini)/2./(end-ini)*Exposure; 

  return total;
}

void DMExclusion::GetRates(int i0, int i1, double &exp, double &theo)
{
  exp=0; theo=0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);
  int ini_aux = ini+i0;
  int end_aux = ini+i1;
  if (ini_aux >= end) return;
  if (end_aux > end) end_aux=end;
  
  // Integral: RECTANGLES
  for (int i=ini_aux; i<end_aux; i++) 
  {
    exp += ExpSpc[i]*Ebin;
    theo+= TheoSpc[i]*Ebin;
  }
 
  exp *= Exposure; 
  theo *= Exposure; 
}

// Returns maximum allowed nucleon cross section spin independent and spin dependent
// in picobarns for the given Wimp mass, the experimental 
// spectrum and the theoretical spectrum to the given CL.
int DMExclusion::GetMaxCrossSection(double mW, double cl, double * ssi, double * ssd)
{
  // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.
  double maxExRate = GetMaxExpRate(cl); 

  // Spin Independent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoSpc = new double [Nbins];
  double * modSpc = new double [Nbins];
  double * phi = new double [Nbins];
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(1.); 
  TheoRate->SetSigSD(0.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, TheoSpc, modSpc, phi);

  // Get TOTAL RATE OF THEORETICAL SPECTRUM
  double theoTotalRate = GetTheoTotalRate();

  // Get spin independent nucleon cross section
  (*ssi) = maxExRate / theoTotalRate; // In picobarns
  if (*ssi == std::numeric_limits<double>::infinity() ) *ssi=verylarge;

  // Spin Dependent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(0.); 
  TheoRate->SetSigSD(1.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, TheoSpc, modSpc, phi);


  // Get TOTAL RATE OF THEORETICAL SPECTRUM
  theoTotalRate = GetTheoTotalRate();


  (*ssd) = maxExRate / theoTotalRate; // In picobarns
  if (*ssd == std::numeric_limits<double>::infinity() ) *ssd=verylarge;

//DEB
std::cout   << mW << " theta " ;
for (int iel=0; iel<TheoRate->GetNElements(); iel++) std::cout << TheoRate->GetElement(iel)-> GetTheta() << " " ;
std::cout << maxExRate << " " <<  theoTotalRate << " ssd " << (*ssd) << std::endl;


  delete [] TheoSpc;
  TheoSpc = 0;
  delete [] modSpc;
  delete [] phi;

  return 0;
}

// uses pseudo Yillis method to optain an optimum
// with minimum interval size of miInt bins
// Returns maximum allowed nucleon cross section spin independent / spin dependent
// in picobarns for the given Wimp mass, the experimental 
// spectrum and the theoretical spectrum to the given CL.
double DMExclusion::GetOptMaxCrossSectionSI(double mW, double cl, int minInt)
{
  return GetOptMaxCrossSection(mW,cl,1,0,0,minInt);
}
double DMExclusion::GetOptMaxCrossSectionSDp(double mW, double cl, int minInt)
{
  return GetOptMaxCrossSection(mW,cl,0,1,0,minInt);
}
double DMExclusion::GetOptMaxCrossSectionSDn(double mW, double cl, int minInt)
{
  return GetOptMaxCrossSection(mW,cl,0,1,1.57079632679489656,minInt);
}

double DMExclusion::GetOptMaxCrossSectionSD(double mW, double cl, double theta, int minInt)
{
  return GetOptMaxCrossSection(mW,cl,0,1,theta,minInt);
}

  // auxiliar

// sd = 0 -> SI, sd = 1 -> proton sd = 2 -> neutron
double DMExclusion::GetOptMaxCrossSection(double mW, double cl, double si, double sd, double theta, int minInt)
{

  // Spin Independent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoSpc = new double [Nbins];
  double * modSpc = new double [Nbins];
  double * phi = new double [Nbins];
  TheoRate->SetMW(mW);

  TheoRate->SetSigSI(si); 
  TheoRate->SetSigSD(sd); 
  for (int iel=0; iel<TheoRate->GetNElements(); iel++)
    TheoRate->GetElement(iel)->SetTheta(theta);

  TheoRate->SpectrumResolution(Eini, Eend, Ebin, TheoSpc, modSpc, phi);

  double crossSection;
  double nmax;
  if (minInt==0)
  {
    // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.
    double maxExRate = GetMaxExpRate(cl); 
  
    // Get TOTAL RATE OF THEORETICAL SPECTRUM
    double theoTotalRate = GetTheoTotalRate();
  
    // Get spin independent nucleon cross section
    crossSection = maxExRate / theoTotalRate; // In picobarns

std::cout << " mw  " << mW <<  " -> " << "exp counts " << maxExRate << " expected " << theoTotalRate << " sigma -> " << crossSection << std::endl;
  }

  else 
  {
    // look for optiman interval with at least minInt bins, from 0 to Wbins
    double exp,theo,optExp, optTheo, merit=verylarge;
    int bestI, bestE;
    for (int is=0; is<NWbins-minInt; is++) // start of the interval
    {
      for (int ie=is+minInt; ie<NWbins; ie++)
        {
          GetRates(is,ie, exp, theo);

          DMGetMaxCountsCL(exp, cl, &nmax);
          if ( (nmax/theo) < merit)
          {
            optExp=exp; optTheo=theo; 
            merit=nmax/theo;
            bestI=is; bestE=ie;
          }
        }
     }

    // NOW CONSIDER THE CL
    double nmax;
    DMGetMaxCountsCL(optExp, cl, &nmax);
    crossSection = nmax / optTheo; // In picobarns
std::cout << " mw  " << mW <<  " best interval " << EWini+bestI*Ebin << " : " << EWini+bestE*Ebin << " index: " << bestI << "-" << bestE << " -> " << "exp counts " << optExp << " afrer CL -> " << nmax << " expected " << optTheo << std::endl;
  }

  if (crossSection == std::numeric_limits<double>::infinity() ) crossSection=verylarge;
  
  return crossSection;
}
