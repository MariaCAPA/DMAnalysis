////////////////////////
// Maria 
// Example plotExclusion.C
// - Initialize a DMExclusion class with parameters from templates/exclusion.dat
//       * Initialize detector & and halo parameters from templates/rate.dat:
//              - Detector with two elements Na, I 
//                 whose parameters are readed from templates/Na.dat, templates/I.dat 
//              - Isothermal halo model. Paramteres read from templates/iso.dat
//       * Initialize exposure, CL, Bkg(lineal), energy window
// - Change some of this parameters (threshold, exposure)
// - Calculate the exclusion (SI & SD) curve for 4 different values of the (lineal) bkg and 
//   superpose them in a plot
#include <vector>
void plotExSICupid(int minInt=10) // min interval -> 1 keV
{
  gSystem->Load("libDMAnalysis");

   gStyle->SetPadRightMargin(0.16);
  int error;
  DMExclusion * exclusion = new DMExclusion();

  // MARIA NOTE:
  // FF Helm does not work for A<=6 !!
  // for SI 7Li content does not matter, -> start from a more general molecure 
  // without isotopic content
  error = exclusion->Initialize("exclusionSICUPID.dat");
  if (error<0) return;


  TGraph *gaux;

  // to test


  DMExclusionPlotHandle  plothl (exclusion);
  plothl.Setcm2Scale();
  plothl.SetTeVScale();

  ////////////////////
  ////////////////////
  // SI

  ////double mL=1;
  //double mH=1000;
  //double sL=1e-13;
  //double sH=1e-2;

  //double mL=0.3;
  //double mH=50;
  //double sL=1e-14;
  //double sH=1e-1;

  double mL=2e-4;
  double mH=100;
  double sL=1e-50;
  double sH=1e-37;


  //c = new TCanvas("c","",820,500);
  c = new TCanvas("c","",820*1.5,500*1.5);
  frame = gPad->DrawFrame(mL, sL, mH, sH);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  //img =  TImage::Open("SI_lowMass_0.3_50_m14_m1.png");
  img =  TImage::Open("exclusionSI_europeanParticleUpdate_noAxis_2em4TeV_100TeV_1m50cm2_1m37cm2.JPG");
  img->SetConstRatio(kFALSE);
  img->Draw();
  frame->GetYaxis()->SetTitle("#sigma_{SI} (cm^{2})");
  frame ->GetXaxis()->SetTitle("m_{W} (TeV)");

  double pb2cm=1e-36;
  TGaxis *axis = new TGaxis(mH,sL,mH,sH,sL/pb2cm,sH/pb2cm,50510,"+LG");
  axis->SetLabelOffset(0.01);
  axis->SetLabelFont(42);
  axis->SetTitle("#sigma_{SI} (pb)");
  axis->SetTitleFont(42);
  axis->SetLabelSize(0.05);
  axis->SetTitleSize(0.07);
  axis->SetTitleOffset(1.1);
  axis->Draw();
 

  double mass = 0.242*1500;
  double time = 1*365;
  double th=5;
  double bkg=0.01;
 

  TGraph * gSI;
  // 1.
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(time*mass); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSI = plothl.GetSIExclusion(0.1,1e4,minInt); // this is in GeV
  gSI->SetLineColor(kBlue);
  gSI->SetLineWidth(6);
  gSI->Draw("l");

  // 2.
/*
  mass = 0.242*1500;
  time = 1*365;
  th=5;
  bkg=0.001;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(time*mass); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSI = plothl.GetSIExclusion(0.1,1e4,minInt); // this is in GeV
  gSI->SetLineColor(kBlue);
  gSI->SetLineWidth(6);
  gSI->SetLineStyle(7);
  gSI->Draw("same");
*/

  // 3.
  mass = 0.242*1500;
  time = 1*365;
  th=1;
  bkg=0.01;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(time*mass); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSI = plothl.GetSIExclusion(0.1,1e4,minInt); // this is in GeV
  gSI->SetLineColor(kRed);
  gSI->SetLineWidth(6);
  gSI->Draw("same");


  // 4.
  mass = 0.242*1500;
  time = 1*365;
  th=1;
  bkg=0.001;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(time*mass); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSI = plothl.GetSIExclusion(0.1,1e4,minInt);
  gSI->SetLineColor(kGreen);
  gSI->SetLineWidth(6);
  //gSI->SetLineStyle(7);
  gSI->Draw("same");

  gPad->Update();
  //c->SaveAs("cupidSI.png");
  c->SaveAs("cupidSI.png");
  //c->SaveAs("cupidSI.pdf");
  c->SaveAs("cupidSI.eps");
}
