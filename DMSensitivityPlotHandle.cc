/**********************************
 * Maria Martinez 12/03/12
 * Class DMSensitivityPlotHandle
 * Plot manager for a DMSensitivity class
 *********************************/

#include "DMSensitivityPlotHandle.hh"
#include "DMUtil.hh"

#include <TTree.h>
#include <TNtupleD.h>
#include <TGraph.h>
#include <TAxis.h>

#include <iostream>
#include <sstream>
#include <string>

// Conctructor
DMSensitivityPlotHandle::DMSensitivityPlotHandle (): fSensitivity(0)
{
}

DMSensitivityPlotHandle::DMSensitivityPlotHandle (DMVSensitivity * sensitivity)
{
  fSensitivity = sensitivity;
}
 
// Destructor
DMSensitivityPlotHandle::~DMSensitivityPlotHandle()
{
  fSensitivity = 0;
}
TGraph * DMSensitivityPlotHandle::GetSDpSensitivity(double iniM, double endM)
{
  TGraph * g = GetSensitivity(iniM, endM, 0, 1, 0);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SDp} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SDp} (cm^{2})");
  return g;
}
TGraph * DMSensitivityPlotHandle::GetSDnSensitivity(double iniM, double endM)
{
  TGraph * g = GetSensitivity(iniM, endM, 0, 1, 1.57079632679489656);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SDn} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SDn} (cm^{2})");
  return g;
}
TGraph * DMSensitivityPlotHandle::GetSDSensitivity(double iniM, double endM, double theta)
{
  TGraph * g = GetSensitivity(iniM, endM, 0, 1, theta);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SD} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SD} (cm^{2})");
  return g;
}
TGraph * DMSensitivityPlotHandle::GetSISensitivity(double iniM, double endM)
{
  TGraph * g = GetSensitivity(iniM, endM, 1, 0, 0);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SI} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SI} (cm^{2})");
  return g;
}



TGraph * DMSensitivityPlotHandle::GetSensitivity(double iniM, double endM, int ssi, int ssd, double theta)
{
  static int nGraphs=0;

  if (!fSensitivity) 
  {
    std::cout << "Sensitivity not initialized in DMSensitivityPlotHandle. Use set method" << std::endl;
    return 0; 
  }

  // MARIA 120312
  // BY NOW, MW between 1 and 1000 always
  TGraph * g = new TGraph ();

  int i=0, j=0;
  double mw, base, exp;
  double incr;
  double ind = 0;
  double maxExp = 3; 
  if (endM>1000) maxExp=4;
  for (exp=0; exp<maxExp; exp++)
  {
    incr=0.1;
    for (base=1; base<10; base+=incr)
    {
      if (base>2) incr=1;
      if (exp==0) mw = base;
      else if (exp==1) mw = base*10;
      else if (exp==2) mw = base*100;
      else if (exp==3) mw = base*1000;
      double sigma = fSensitivity->GetMaxCrossSection(mw, fSensitivity->GetDelta2(), ssi, ssd,theta);
      g->SetPoint(ind++, fScaleX*mw, fScaleY*sigma);
    }
  }


  g->GetXaxis()->SetTitle(Form("Wimp mass (%s)",massUnit.c_str()));
  g->GetYaxis()->SetTitle("#sigma_{SI} (pb)");
  g->GetYaxis()->SetLimits(1e-15, 1);
  g->GetYaxis()->SetRangeUser(1e-12, 1);
  
  g->SetFillColor(kWhite);
  return g;

}


// Get a TTree with all the calculated vars. 
TTree * DMSensitivityPlotHandle::GetAllVars(double iniM, double endM)
{
  static int nTrees=0;

  if (!fSensitivity) 
  {
    std::cout << "Sensitivity not initialized in DMSensitivityPlotHandle. Use set method" << std::endl;
    return 0; 
  }

  // MARIA 120312
  // BY NOW, MW between 1 and 1000 always
  TNtupleD * tree = new TNtupleD(Form("tree_%d",nTrees++),"","MW:SI:SD");

  int i=0, j=0;
  double ssi, ssd, mw, base, exp;
  double incr;
  for (exp=0; exp<3; exp++)
  {
    incr=0.1;
    for (base=1; base<10; base+=incr)
    {
      if (base>2) incr=1;
      if (exp==0) mw = base;
      else if (exp==1) mw = base*10;
      else if (exp==2) mw = base*100;
      fSensitivity->GetMaxCrossSection(mw, fSensitivity->GetDelta2(), &ssi, &ssd);
      tree->Fill(fScaleX*mw, fScaleY*ssi, fScaleY*ssd);
    }
  }


  return tree;

}

int DMSensitivityPlotHandle::Dump(char * fileName,double iniM, double endM)
{
  TTree * tree = GetAllVars(iniM, endM);

  int retval = DMVPlotHandle::Dump(fileName, tree);

  return retval;

}
