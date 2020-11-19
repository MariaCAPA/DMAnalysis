/**********************************
 * Maria Martinez 12/03/12
 * Class DMRatePlotHandle
 * Plot manager for a DMRate class
 *********************************/

#include "DMRatePlotHandle.hh"
#include "DMUtil.hh"
#include <TTree.h>
#include <TNtupleD.h>
#include <TH1F.h>

#include <iostream>
#include <sstream>
#include <string>

// Conctructor
DMRatePlotHandle::DMRatePlotHandle (): fRate(0)
{
}

DMRatePlotHandle::DMRatePlotHandle (DMRate * rate)
{
  fRate = rate;
}
 
// Destructor
DMRatePlotHandle::~DMRatePlotHandle()
{
  fRate = 0;
}

// Get the expected rate in a TH1F (nBins, Eini, Eend) 
// Energy in keV
TH1F * DMRatePlotHandle::GetSIRate(double mw, double sigma, int nBins, double Eini, double Eend)
{
  fRate->SetParams(mw,sigma,0,0);
  TH1F * h= GetRate(nBins, Eini, Eend);
  return h;
}

TH1F * DMRatePlotHandle::GetSDpRate(double mw, double sigma, int nBins, double Eini, double Eend)
{
  fRate->SetParams(mw,0, sigma,0);
  TH1F * h= GetRate(nBins, Eini, Eend);
  return h;
}

TH1F * DMRatePlotHandle::GetSDnRate(double mw, double sigma, int nBins, double Eini, double Eend)
{
  fRate->SetParams(mw,0, sigma,1.57079632679489656);
  TH1F * h= GetRate(nBins, Eini, Eend);
  return h;
}


TH1F * DMRatePlotHandle::GetRate(int nBins, double Eini, double Eend)
{
  static int nHist=0;
  int i;

  if (!fRate) 
  {
    std::cout << "Rate not initialized in DMRatePlotHandle. Use set method" << std::endl;
    return 0; 
  }

  TH1F * h = new TH1F (Form("h_%d",nHist++), "", nBins, Eini, Eend);
  double * S0 = new double [nBins];
  double * Sm = new double [nBins];
  double * phi = new double [nBins];
  double ebin = (Eend-Eini)/nBins;
  fRate -> SpectrumResolution (Eini, Eend, ebin, S0, Sm, phi);

  for (i=0; i<nBins; i++) h->SetBinContent(i+1, S0[i]);
  delete [] S0;
  delete [] Sm;
  delete [] phi;

  h->GetXaxis()->SetTitle("Energy (keVee)");
  h->GetYaxis()->SetTitle("c/keVee/kg/day");
  return h;

}
// Get the expected modulated rate in a TH1F (nBins, Eini, Eend) 
// Energy in keV
TH1F * DMRatePlotHandle::GetModulatedRate(int nBins, double Eini, double Eend)
{
  static int nHist=0;
  int i;

  if (!fRate) 
  {
    std::cout << "Rate not initialized in DMRatePlotHandle. Use set method" << std::endl;
    return 0; 
  }

  TH1F * h = new TH1F (Form("hm_%d",nHist++), "", nBins, Eini, Eend);
  double * S0 = new double [nBins];
  double * Sm = new double [nBins];
  double * phi = new double [nBins];
  double ebin = (Eend-Eini)/nBins;
  fRate -> SpectrumResolution (Eini, Eend, ebin, S0, Sm, phi);

  for (i=0; i<nBins; i++) h->SetBinContent(i+1, Sm[i]);
  delete [] S0;
  delete [] Sm;
  delete [] phi;

  h->GetXaxis()->SetTitle("Energy (keVee)");
  h->GetYaxis()->SetTitle("Sm (c/keVee/kg/day)");
  return h;

}

// Get a TTree with all the calculated vars. 
// Energy in keV
TTree * DMRatePlotHandle::GetAllVars(int nBins, double Eini, double Eend)
{
  static int nTrees=0;
  int i,el, ivar;

  if (!fRate) 
  {
    std::cout << "Rate not initialized in DMRatePlotHandle. Use set method" << std::endl;
    return 0; 
  }

  // TODO F2 DE TODOS LOS ELEMENTOS!!!
  std::string vars;
  int nVars = MakeVars(vars);

  // Create tree and auxiliar array to fill it
  TNtupleD * tree = new TNtupleD(Form("tree_%d",nTrees++),"",vars.c_str());
  double * auxVars = new double[nVars];

  // Create auxiliar arrays to get the rate
  double * S0 = new double [nBins];
  double * Sm = new double [nBins];
  double * phi = new double [nBins];

  // Get the rate
  double ebin = (Eend-Eini)/nBins;
  fRate -> SpectrumResolution (Eini, Eend, ebin, S0, Sm, phi);

  // Fill the tree
  double energy = Eini;;
  for (i=0; i<nBins; i++)
  {
    ivar = 0;
    auxVars [ivar++] = energy;
    auxVars [ivar++] = S0[i];
    auxVars [ivar++] = Sm[i];
    auxVars [ivar++] = phi[i];

    // loop in elements
    for (el=0; el<fRate->GetNElements();el++)
    {
      DMElement * ele = fRate->GetElement(el); 

      // Calculate minimum velocity of a Wimp of  mass MW to produce a recoil of energy edep (in keVee)
      //double edep = energy/ele->GetREF();
      //auxVars[ivar++] = ele->Vmin(edep, fRate->GetMW());
  
      // Calculate form factors
      auxVars[ivar++] = ele->FF2SI(energy);
      auxVars[ivar++] = ele->FF2SD(energy);
    } // end loop in elements

    tree->Fill(auxVars);
    energy += ebin;
  }
  delete [] S0;
  delete [] Sm;
  delete [] phi;
  delete [] auxVars;

  return tree;
}

// Get a TTree with all the calculated vars. 
// Energy in keV
int DMRatePlotHandle::Dump(char * fileName, int nBins, double Eini, double Eend)
{
  TTree * tree = GetAllVars(nBins, Eini, Eend);

  int retval = DMVPlotHandle::Dump(fileName, tree);

  return retval;
  
}

int DMRatePlotHandle::MakeVars(std::string & vars)
{
  std::stringstream aux;
  aux << "E:S0:Sm:Phi";
  int i, nVars = 4;
  for (i=0; i<fRate->GetNElements();i++)
  {
    //aux << Form(":Vmin_%d:FF2SI_%d:FF2SD_%d", i+1, i+1, i+1);
    //nVars += 3;
    aux << Form(":FF2SI_%d:FF2SD_%d", i+1, i+1);
    nVars += 2;
  }
  vars = aux.str();
  return nVars;
} 
