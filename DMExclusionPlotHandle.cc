/**********************************
 * Maria Martinez 12/03/12
 * Class DMExclusionPlotHandle
 * Plot manager for a DMExclusion class
 *********************************/

#include "DMExclusionPlotHandle.hh"
#include "DMUtil.hh"

#include <TTree.h>
#include <TNtupleD.h>
#include <TGraph.h>
#include <TAxis.h>

#include <iostream>
#include <sstream>
#include <string>

// Conctructor
DMExclusionPlotHandle::DMExclusionPlotHandle (): fExclusion(0)
{
}

DMExclusionPlotHandle::DMExclusionPlotHandle (DMExclusion * exclusion)
{
  fExclusion = exclusion;
}
 
// Destructor
DMExclusionPlotHandle::~DMExclusionPlotHandle()
{
  fExclusion = 0;
}

TGraph * DMExclusionPlotHandle::GetSDpExclusion(double iniM, double endM, int minInt)
{
  TGraph * g = GetExclusion(iniM, endM, 0, 1, 0, minInt);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SDp} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SDp} (cm^{2})");
  return g;
}
TGraph * DMExclusionPlotHandle::GetSDnExclusion(double iniM, double endM, int minInt)
{
  TGraph * g = GetExclusion(iniM, endM, 0, 1, 1.57079632679489656, minInt);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SDn} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SDn} (cm^{2})");
  return g;
}
TGraph * DMExclusionPlotHandle::GetSDExclusion(double iniM, double endM, double theta, int minInt)
{
  TGraph * g = GetExclusion(iniM, endM, 0, 1, theta, minInt);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SD} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SD} (cm^{2})");
  return g;
}
TGraph * DMExclusionPlotHandle::GetSIExclusion(double iniM, double endM, int minInt)
{
  TGraph * g = GetExclusion(iniM, endM, 1, 0, 0, minInt);
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma_{SI} (pb)");
  else g->GetYaxis()->SetTitle("#sigma_{SI} (cm^{2})");
  return g;
}

TGraph * DMExclusionPlotHandle::GetExclusion(double iniM, double endM, double si, double sd, double theta, int minInt)
{
  static int nGraphs=0;

  if (!fExclusion) 
  {
    std::cout << "Exclusion not initialized in DMExclusionPlotHandle. Use set method" << std::endl;
    return 0; 
  }

  TGraph * g = new TGraph ();

  int i=0, j=0;
  double ss, mw, base, exp;
  double incr;
  double ind = 0;
  int maxExp = 3;
  int iniExp = 0;
  if (endM>1e3) maxExp=4;
  if (iniM<1) iniExp=-1; 
  for (exp=iniExp; exp<maxExp; exp++)
  {
    incr=0.1;
    for (base=1; base<10; base+=incr)
    {
      if (base>2) incr=1;
      if (exp==-1) mw = base*0.1;
      else if (exp==0) mw = base;
      else if (exp==1) mw = base*10;
      else if (exp==2) mw = base*100;
      else if (exp==3) mw = base*1000;
      ss = fExclusion->GetOptMaxCrossSection(mw, fExclusion->GetCL(), si, sd, theta, minInt);
      g->SetPoint(ind++, fScaleX*mw, fScaleY*ss);
    }
  }



  g->GetXaxis()->SetTitle(Form("Wimp mass (%s)",massUnit.c_str()));
  if (fScaleY==1) g->GetYaxis()->SetTitle("#sigma (pb)");
  else g->GetYaxis()->SetTitle("#sigma (cm^{2})");
  //g->GetYaxis()->SetLimits(1e-12, 1e6);
  //g->GetYaxis()->SetRangeUser(1e-12, 1e6);
  g->SetFillColor(kWhite);
  return g;

}

// Get a TTree with all the calculated vars. 
TTree * DMExclusionPlotHandle::GetAllVars(double iniM, double endM)
{
  static int nTrees=0;

  if (!fExclusion) 
  {
    std::cout << "Exclusion not initialized in DMExclusionPlotHandle. Use set method" << std::endl;
    return 0; 
  }

  TNtupleD * tree = new TNtupleD(Form("tree_%d",nTrees++),"","MW:SI:SD");

  int i=0, j=0;
  double ssi, ssd, mw, base, exp;
  double incr;
  int maxExp = 3;
  int iniExp = 0;
  if (endM>1e3) maxExp=4;
  if (iniM<1) iniExp=-1; 
  for (exp=iniExp; exp<maxExp; exp++)
  {
    incr=0.1;
    for (base=1; base<10; base+=incr)
    {
      if (base>2) incr=1;
      if (exp==-1) mw = base*0.1;
      if (exp==0) mw = base;
      else if (exp==1) mw = base*10;
      else if (exp==2) mw = base*100;
      else if (exp==3) mw = base*1000;
      fExclusion->GetMaxCrossSection(mw, fExclusion->GetCL(), &ssi, &ssd);
      tree->Fill(fScaleX*mw, fScaleY*ssi, fScaleY*ssd);
    }
  }


  return tree;

}

int DMExclusionPlotHandle::Dump(char * fileName,double iniM, double endM)
{
  TTree * tree = GetAllVars(iniM, endM);

  int retval = DMVPlotHandle::Dump(fileName, tree);

  return retval;

}
