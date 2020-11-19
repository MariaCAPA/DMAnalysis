/**********************************
 * Maria Martinez 10/04/15
 * Class DMSensitivityToData
 * Class to perform a sensitivity plot. Contains an 
 * experimental spectrum and a theoritical one (class Rate)
 *********************************/

#include "DMSensitivityToData.hh"
#include "DMRate.hh"
#include "DMUtil.hh"
#include <sstream>
#include <string.h>
using namespace std;

// Conctructor
DMSensitivityToData::DMSensitivityToData ()
{
  TheoRate  = 0;
  Background  = 0;
  S0 = 0;
  Sm = 0;
  Nbins   = 0;
  fEfficiency = 0;
}
 
// Destructor
DMSensitivityToData::~DMSensitivityToData()
{
  if (TheoRate) delete TheoRate;
  if (Background) delete Background;
  if (S0) delete S0;
  if (Sm) delete Sm;
  if (fEfficiency) delete fEfficiency;
}


// Initialize class. initialize Rate class from file
int DMSensitivityToData::Initialize(char * fileName)
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
  char effFile[256];
  int flag=0;
  int flagEff=0;


  // Default Initial values
  double auxbackground = 1;
  double auxEfficiency = 1;
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
    else if (!strcmp(dummy,"LINEFFICIENCY"))  {srLine >> auxEfficiency; }
    else if (!strcmp(dummy,"EFFICIENCY"))  {srLine >> effFile; flagEff=1;}
    else if (!strcmp(dummy,"EINI"))  {srLine >> Eini; EWini = Eini;}
    else if (!strcmp(dummy,"EEND"))  {srLine >> Eend; EWend = Eend;}
    else if (!strcmp(dummy,"EBIN"))  {srLine >> Ebin;}
    else if (!strcmp(dummy,"EWINI"))  {srLine >> EWini;}
    else if (!strcmp(dummy,"EWEND"))  {srLine >> EWend;}

  } // end while
  fq.close();
 
  // Set experimental spectrum
  if (flag==0) SetBackground(Eini, Eend, Ebin, auxbackground);
  else  SetBackground(Eini, Eend, Ebin, bckFile);

  if (flagEff==0) SetEfficiency(auxEfficiency);
  else  SetEfficiency(effFile);

  return 0;

}


// Efficiency of the measured bkg. Bins must be the same as bkg
void DMSensitivityToData::SetEfficiency(double eff)
{
  int i;
  if (fEfficiency!=0) delete fEfficiency;
  fEfficiency = new double [Nbins];
  for (i=0; i<Nbins; i++) fEfficiency[i] = eff;
}

// Efficiency of the measured bkg. Bins must be the same as bkg
void DMSensitivityToData::SetEfficiency(char * effFile)
{
  int i;
  if (fEfficiency!=0) delete fEfficiency;
  fEfficiency = new double [Nbins];
  fstream fq (effFile, ios::in);
  for (i=0; i<Nbins; i++)
  {
    fq >> fEfficiency[i];
    if (fq.eof()) {cout << "Warning: efficiency file too short! " << endl; fEfficiency[i]=0;}
  }
}

// Difference with mother class: Now, bk = bk  + S0
// This makes the function much more simple (sigma is just a multiplicative factor)
// Returns maximum allowed nucleon cross section spin independent and spin dependent
// in picobarns for the given Wimp mass, the experimental 
// spectrum and the theoretical spectrum to the given CL.
int DMSensitivityToData::GetMaxCrossSection(double mW, double cl, double * ssi, double * ssd)
{
  int i=0;
  double sum = 0;
  int ini = (int)((EWini-Eini)/Ebin);
  int end = (int)((EWend-Eini)/Ebin);


  // GET MAXIMUM EXPERIMENTAL COUNTS FOR CL AND EXPOSURE.

  // Spin Independent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM for sigma=1
  S0 = new double [Nbins];
  Sm = new double [Nbins];
  double * phi = new double [Nbins];
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(1.); 
  TheoRate->SetSigSD(0.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, S0, Sm, phi);

  for (i=ini; i<end; i++) sum += Sm[i]*Sm[i]*fEfficiency[i]/Background[i];

  double sig0 = sqrt((2*Delta2-4)/sum/Exposure/Ebin);

  // Get spin independent nucleon cross section
  (*ssi) = sig0; // In picobarns

  // Spin Dependent
  // SET mW in RATE AND COMPUTE THEORETICAL SPECTRUM
  TheoRate->SetMW(mW);
  TheoRate->SetSigSI(0.); 
  TheoRate->SetSigSD(1.); 
  TheoRate->SpectrumResolution(Eini, Eend, Ebin, S0, Sm, phi);

  for (i=ini; i<end; i++) sum += Sm[i]*Sm[i]*fEfficiency[i]/Background[i];

  sig0 = sqrt((2*Delta2-4)/sum/Exposure/Ebin);

  // Get spin independent nucleon cross section
  (*ssd) = sig0; // In picobarns


  delete [] S0;
  S0 = 0;
  delete [] Sm;
  Sm = 0;
  delete [] phi;
  phi=0;

  return 0;
}
