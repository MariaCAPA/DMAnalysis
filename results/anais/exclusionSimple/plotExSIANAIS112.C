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
void plotExSIANAIS112(int minInt=10) // min interval -> 1 keV
{
  gSystem->Load("libDMAnalysis");

   gStyle->SetPadRightMargin(0.16);
  int error;
  DMExclusion * exclusion = new DMExclusion();

  // MARIA NOTE:
  // FF Helm does not work for A<=6 !!
  // for SI 7Li content does not matter, -> start from a more general molecure 
  // without isotopic content
  error = exclusion->Initialize("exclusionSIANAIS112.dat");
  if (error<0) return;


  TGraph *gaux;

  // to test


  DMExclusionPlotHandle  plothl (exclusion);
  plothl.Setcm2Scale();
  //plothl.SetTeVScale();

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

  double mL=1;
  double mH=1000;
  double sL=1e-45;
  double sH=1e-35;


  TCanvas * c;

  //c = new TCanvas("c","",820,500);
  c = new TCanvas("c","",820*1.5,500*1.5);
  TH1F * frame = gPad->DrawFrame(mL, sL, mH, sH);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  //img =  TImage::Open("SI_lowMass_0.3_50_m14_m1.png");
  //img =  TImage::Open("exclusionSI_europeanParticleUpdate_noAxis_2em4TeV_100TeV_1m50cm2_1m37cm2.JPG");
  //img->SetConstRatio(kFALSE);
  //img->Draw();
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
 
  // QUENCHING
  /////////////////////
  // QUENCHING FACTORS
  // Open file with q factors
  TFile * f = new TFile ("QFTamara.root","READ");
  if (!f) {std::cout << " CANNOT READ QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  TGraph * gQNa=(TGraph*)f->Get("gNa");
  if (!gQNa) {std::cout << " CANNOT FIND gNa IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQI=(TGraph*)f->Get("gI");
  if (!gQI) {std::cout << " CANNOT FIND gI IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  DMRate * theRate = exclusion->GetTheoRate();
  theRate->GetElement(0)->SetREF(gQNa);
  theRate->GetElement(1)->SetREF(gQI);



  double mass = 112.5;
  double time = 18263.42; // days
  double th=1;
 

  TGraph * gSI;
  // 1.
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(time*mass); // in kgxd
  gSI = plothl.GetSIExclusion(0.1,1e4,0); // this is in GeV
  gSI->SetLineColor(kBlue);
  gSI->SetLineWidth(6);
  gSI->Draw("l");
  gSI->SetName("QF ANAIS-112");

  // 2. QF DAMA
  theRate->GetElement(0)->SetREF(0.3);
  theRate->GetElement(1)->SetREF(0.09);
  gSI = plothl.GetSIExclusion(0.1,1e4,0); // this is in GeV
  gSI->SetLineColor(kRed);
  gSI->SetLineWidth(6);
  gSI->Draw("lsame");
  gSI->SetName("QF DAMA");

  // effect of minInt
  //gSI = plothl.GetSIExclusion(0.1,1e4,minInt);
  //gSI->SetLineColor(kGreen);
  //gSI->SetLineWidth(6);
  ////gSI->SetLineStyle(7);
  //gSI->Draw("same");

  gPad->BuildLegend();
  gPad->Update();
  c->SaveAs("ANAIS112SI.png");
}
