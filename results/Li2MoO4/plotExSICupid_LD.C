////////////////////////
// Maria 
// Example plotExclusion.C
// - Initialize a DMExclusion class with parameters from a file exclusion.dat
//       * Initialize detector & and halo parameters from a file rate.dat
//              - Isothermal halo model. Paramteres read from templates/iso.dat
//       * Initialize exposure, CL, Bkg(lineal), energy window
// - Change some of this parameters (threshold, exposure)
// - Calculate the exclusion (SI & SD) curve for 4 different values of bkg and threshold
//   superpose them in a plot
#include <vector>
void plotExSICupid_LD(int minInt=10) // min interval -> 1 keV
{
  gSystem->Load("libDMAnalysis");

   gStyle->SetPadRightMargin(0.16);
  int error;
  DMExclusion * exclusionGe = new DMExclusion();
  DMExclusion * exclusionSi = new DMExclusion();

  error = exclusionGe->Initialize("exclusionSICUPID_Ge.dat");
  if (error<0) return;

  error = exclusionSi->Initialize("exclusionSICUPID_Si.dat");
  if (error<0) return;


  TGraph *gaux;

  // to test


  DMExclusionPlotHandle  plothlGe (exclusionGe);
  plothlGe.Setcm2Scale();
  plothlGe.SetTeVScale();

  DMExclusionPlotHandle  plothlSi (exclusionSi);
  plothlSi.Setcm2Scale();
  plothlSi.SetTeVScale();

  ////////////////////
  ////////////////////
  // SI

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
 

  double mass = 2.83;
  double time = 1*365;
  double th=0.1;
  double bkg=0.01;
 

  // 1.
  TGraph * gSIGe;
  exclusionGe->SetThreshold(th); // in keV
  exclusionGe->SetExposure(time*mass); // in kgxd
  exclusionGe->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSIGe = plothlGe.GetSIExclusion(0.1,1e4,minInt); // this is in GeV
  gSIGe->SetLineColor(kBlue);
  gSIGe->SetLineWidth(6);
  gSIGe->Draw("l");

  // 2.
  mass = 1.24; // Si total mass
  time = 1*365;
  th=0.1;
  bkg=0.01;
  TGraph * gSISi;
  exclusionSi->SetThreshold(th); // in keV
  exclusionSi->SetExposure(time*mass); // in kgxd
  exclusionSi->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSISi = plothlSi.GetSIExclusion(0.1,1e4,minInt); // this is in GeV
  gSISi->SetLineColor(kRed);
  gSISi->SetLineWidth(6);
  gSISi->Draw("same");

  gPad->Update();
  c->SaveAs("cupidSI_LD.png");
  //c->SaveAs("cupidSI_LD.pdf");
}
