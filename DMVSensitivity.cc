/**********************************
 * Maria Martinez 16/11/05
 * Class DMVSensitivity
 * Class to perform a sensitivity plot. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 *********************************/

#include "DMVSensitivity.hh"
#include "DMRate.hh"
#include "DMUtil.hh"
#include <sstream>
#include <string.h>
using namespace std;

// Conctructor
DMVSensitivity::DMVSensitivity ()
{
  TheoRate  = 0;
  Background  = 0;
  S0 = 0;
  Sm = 0;
  Nbins   = 0;
}
 
// Destructor
DMVSensitivity::~DMVSensitivity()
{
  if (TheoRate) delete TheoRate;
  if (Background) delete Background;
  if (S0) delete S0;
  if (Sm) delete Sm;
}

// Initialize class. initialize Rate class from file
int DMVSensitivity::Initialize(char * fileName)
{
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

    if      (!strcmp(dummy,"RATEFILE"))  {srLine >> rateFile; TheoRate -> Initialize(rateFile);}
    else if (!strcmp(dummy,"EXPOSURE"))  srLine >> Exposure;
    else if (!strcmp(dummy,"DELTA2"))  srLine >> Delta2;
    else if (!strcmp(dummy,"LINBACKGROUND"))  {srLine >> auxbackground; }
    else if (!strcmp(dummy,"BACKGROUND"))  {srLine >> bckFile; flag=1;}
    else if (!strcmp(dummy,"EINI"))  {srLine >> Eini; EWini = Eini;}
    else if (!strcmp(dummy,"EEND"))  {srLine >> Eend; EWend = Eend;}
    else if (!strcmp(dummy,"EBIN"))  {srLine >> Ebin;}
    else if (!strcmp(dummy,"EWINI"))  {srLine >> EWini;}
    else if (!strcmp(dummy,"EWEND"))  {srLine >> EWend;}

  } // end while
  fq.close();
  SetWindow(EWini,EWend);
 
  // Set experimental spectrum
  if (flag==0) SetBackground(Eini, Eend, Ebin, auxbackground);
  else  SetBackground(Eini, Eend, Ebin, bckFile);

  return 0;

}

// Linear bkg, between Eini and Eend
// bkg  in c/keV/kg/d
void DMVSensitivity::SetLinearBkg(double bkg)
{
   // revision 513, it is not safe. Calculate Nbins
  //int Nbins = 100;
  Nbins = (int)((Eend - Eini) / Ebin );
  int i;
  if (Background!=0) delete Background;
  Background = new double [Nbins];
  for (i=0; i<Nbins; i++) Background[i] = bkg;
}




//  the energy window and an experimental spectrum 
// equal to a linear background (1count/keV/kg/day by default)
// Energy in keVee, background in counts/keV/kg/day
void DMVSensitivity::SetBackground(double ei, double ef, double ebin, double bck)
{
  Eini = ei;
  Eend = ef;
  Ebin = ebin;
  Nbins = (int)((Eend - Eini) / Ebin ); 
  int i;
  if (Background!=0) delete Background;
  Background = new double [Nbins];
  for (i=0; i<Nbins; i++) Background[i] = bck;
}

// Set the energy window and an experimental spectrum 
// equal to a linear background (1count/keV/kg/day by default)
// Energy in keVee, background in counts/bin/kg/day
void DMVSensitivity::SetBackground(double ei, double ef, double ebin, double * spc)
{
  Eini = ei;
  Eend = ef;
  Ebin = ebin;
  Nbins = (int)((Eend - Eini) / Ebin) ; 
  int i;
  if (Background!=0) delete Background;
  Background = new double [Nbins];
  for (i=0; i<Nbins; i++) Background[i] = spc[i]; 
}

// Set the energy window and an experimental background
// from file
// Energy in keVee, background in counts/bin/kg/day
void DMVSensitivity::SetBackground(double ei, double ef, double ebin, char * bckFile)
{
  Eini = ei;
  Eend = ef;
  Ebin = ebin;
  Nbins = (int)((Eend - Eini) / Ebin) ;
  int i;
  if (Background!=0) delete Background;
  Background = new double [Nbins];
  fstream fq (bckFile, ios::in);
  for (i=0; i<Nbins; i++)
  {
    fq >> Background[i];
    if (fq.eof()) {cout << "Warning: background file too short! " << endl; Background[i]=0;}
  }
}

// Get Maximum experimental number of counts for CL
double DMVSensitivity::GetMaxBackground(double cl)
{
  int i=0;
  double total = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);
  
  // Integral: RECTANGLES
  for (i=ini; i<end; i++) total += Background[i]*Ebin;
  total *= Exposure; 

  // MARIA: TRAPEZOID RULE
  //for (i=ini+1; i<end; i++) total += Background[i];
  //total = 2*total + Background[ini] + Background[end];
  //total *= (EWend-EWini)/2./(end-ini)*Exposure; 

  // CONSIDER THE CL
  double nmax;
  DMGetMaxCountsCL(total, cl, &nmax);

  return nmax;
}
