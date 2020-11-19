/**********************************
 * Maria Martinez 08-11-05
 * Class DMElement
 * Element, and Form factor
 *********************************/
#include <iostream>
#include <sstream>
#include <string.h>
#include "DMElement.hh"
#include "DMFormFactorHelmSI.hh"
#include "DMFormFactorResselSD.hh"
#include "DMPhysConstants.hh"
#include "DMUtil.hh"
#include "TGraph.h"
using namespace std;

// Constructor, copy constructor, destructor
DMElement::DMElement()
{
  FFSI = 0;
  FFSD = 0;
  A=0;
  Z=0;
  J=0;
  Sp=0;
  Sn=0;
  MN=0;
  NAtoms=0;
  SpinFactor=0;
  Theta=0;
  
  gREF = 0;
}
DMElement::DMElement(const DMElement & other):
Z(other.Z), A(other.A), J(other.J), Sp(other.Sp), Sn(other.Sn),MN(other.MN),
REF(other.REF), NAtoms(other.NAtoms), SpinFactor(other.SpinFactor), Theta(other.Theta)
{
  if (DMFormFactorHelmSI * pt = dynamic_cast<DMFormFactorHelmSI*>(other.FFSI))
    FFSI = new DMFormFactorHelmSI(*pt);
  else {std::cout << " FFSI not implemented. Error. " << std::endl; FFSI=0;}

  if (DMFormFactorResselSD * pt = dynamic_cast<DMFormFactorResselSD*>(other.FFSD))
    FFSD = new DMFormFactorResselSD(*pt);

  else {std::cout << " FFSD not implemented. Error. " << std::endl; FFSD=0;}
  
  if (other.gREF) gREF = new TGraph(*other.gREF);
  else gREF = 0;
}

DMElement::~DMElement()
{
  if (FFSI!=0) delete FFSI;
  if (FFSD!=0) delete FFSD;

  if (gREF) delete gREF;
}

int DMElement::Initialize (char * fileName)
{
  int retval=0;
  std::string parsed = DMParseShellVars(fileName);
  fstream fq (parsed.c_str(), ios::in);

  if (!fq.good())
  {
    std::cout << "Cannot open file " << parsed.c_str() << std::endl;
    return -1;
  }

  char line [256];
  char dummy[256];
  while (!fq.eof()) 
  {
    fq.getline(line, 240);
    if (fq.eof()) break;
    stringstream srLine(stringstream::in | stringstream::out);
    srLine << line;
    if (line[0]=='#') continue;
    srLine >> dummy;

    if      (!strcmp(dummy,"A"))  srLine >> A;
    else if (!strcmp(dummy,"Z"))  srLine >> Z;
    else if (!strcmp(dummy,"J"))  srLine >> J;
    else if (!strcmp(dummy,"Sp")) srLine >> Sp;
    else if (!strcmp(dummy,"Sn")) srLine >> Sn;
    else if (!strcmp(dummy,"Q"))  srLine >> REF;
    else if (!strcmp(dummy,"FFSI"))  
    {
      srLine >> dummy;

      if (!strcmp(dummy, "STD")) FFSI = new DMFormFactorHelmSI();

    }
    else if (!strcmp(dummy,"FFSD"))  
    {
      srLine >> dummy;
      if (!strcmp(dummy, "STD")) FFSD = new DMFormFactorResselSD();
    }
  }

  MN = A*mNucleon;

  fq.close();

  if (FFSI)  retval = FFSI->Initialize(A,Theta);
  if (retval < 0) return retval;
  if (FFSD) retval = FFSD->Initialize(A,Theta);
  if (retval < 0) return retval;

  return 0;
  
}



double DMElement::GetREF (double Eee)
{
  if (gREF) return gREF->Eval(Eee);

  else return REF;
}
