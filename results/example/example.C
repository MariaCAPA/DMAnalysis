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
void example(int minInt=20) // min interval -> 2 keV
{
  //gSystem->Load("libDMAnalysis");

   gStyle->SetPadRightMargin(0.16);
  int error;
  DMExclusion * exclusion = new DMExclusion();

  // MARIA NOTE:
  // FF Helm does not work for A<=6 !!
  // for SI 7Li content does not matter, -> start from a more general molecure 
  // without isotopic content
  error = exclusion->Initialize("exampleExclusion.dat");
  if (error<0) return;



  // to test

  TGraph *gaux;

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
  double sL=5e-45;
  double sH=1e-32;
  double sLSI=5e-50;
  double sHSI=5e-37;


  TCanvas * c;
  //c = new TCanvas("c","",820,500);
  c = new TCanvas("cSI","",820*1.5,500*1.5);
  TH1F * frame = gPad->DrawFrame(mL, sLSI, mH, sHSI);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  //img =  TImage::Open("SI_lowMass_0.3_50_m14_m1.png");
  //img =  TImage::Open("exclusionSI_europeanParticleUpdate_noAxis_2em4TeV_100TeV_1m50cm2_1m37cm2.JPG");
  //img->SetConstRatio(kFALSE);
  //img->Draw();
  frame->GetYaxis()->SetTitle("#sigma_{SI} (cm^{2})");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");

  double pb2cm=1e-36;
  TGaxis *axis = new TGaxis(mH,sLSI,mH,sHSI,sLSI/pb2cm,sHSI/pb2cm,50510,"+LG");
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

/*
  TFile * f = new TFile ("QFTamara.root","READ");
  if (!f) {std::cout << " CANNOT READ QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  TGraph * gQNa=(TGraph*)f->Get("gNa");
  if (!gQNa) {std::cout << " CANNOT FIND gNa IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQI=(TGraph*)f->Get("gI");
  if (!gQI) {std::cout << " CANNOT FIND gI IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  DMRate * theRate = exclusion->GetTheoRate();
  theRate->GetElement(0)->SetREF(gQNa);
  theRate->GetElement(1)->SetREF(gQI);
*/

  std::vector<double> th = {5,2,1};
  std::vector<double> bkg = {1e-6, 1e-7, 1e-8, 0};
  std::vector<double> win = {6,8,10,20};
  std::vector<double> exp = {0.1,1,10};
  //std::vector<double> bkg = {1e-7};
  //int n=exp.size();
  int n=bkg.size();
  //int n=th.size();
  //int n=win.size();
  for (int i=0; i<n; i++)
  {

    exclusion->SetLinearBkg(bkg[i]); // in cpd/kg/keV
    exclusion->SetWindow(th[0],win[3]);
    exclusion->SetExposure(1000*exp[1]*365); // in kgxd
    TGraph * gSI;
    //gSI = plothl.GetSIExclusion(1,1e3,minInt); // this is in GeV
    gSI = plothl.GetSIExclusion(1,1e3,0); // this is in GeV
    gSI->SetLineColor(i+1);
    //gSI->SetLineWidth(6);
    gSI->SetName(Form("bkg %0.1e th %0.1f window %0.1f exp ton %0.1f",bkg[i],th[0],win[0],exp[1]));
    gSI->Draw("l");
  }
  // effect of minInt
/*
  gSI = plothl.GetSIExclusion(0.1,1e4,minInt);
  gSI->SetLineColor(kGreen);
  gSI->SetLineWidth(6);
  gSI->SetLineStyle(7);
  gSI->Draw("same");
*/

  gPad->BuildLegend();
  gPad->Update();


/*
  ////////////////////////////
  // SDp
  ////////////////////////////
  //c = new TCanvas("c","",820,500);
  c = new TCanvas("cSDp","",820*1.5,500*1.5);
  frame = gPad->DrawFrame(mL, sL, mH, sH);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  //img =  TImage::Open("SI_lowMass_0.3_50_m14_m1.png");
  //img =  TImage::Open("exclusionSI_europeanParticleUpdate_noAxis_2em4TeV_100TeV_1m50cm2_1m37cm2.JPG");
  //img->SetConstRatio(kFALSE);
  //img->Draw();
  frame->GetYaxis()->SetTitle("#sigma_{SDp} (cm^{2})");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");

  TGraph * gSDp;
  // 1.
  gSDp = plothl.GetSDpExclusion(0.1,1e4,0); // this is in GeV
  gSDp->SetLineColor(kBlue);
  gSDp->SetLineWidth(6);
  gSDp->Draw("l");
  gSDp->SetName("COSINE200");
  // ANAIS+
  mass = 10; 
  time = 365; // days
  th=0.1;
  exclusion->SetLinearBkg(0.5); // in cpd/kg/keV
  exclusion->SetExposure(time*mass); // in kgxd
  exclusion->SetThreshold(th); // in keV
  gSDp = plothl.GetSDpExclusion(0.1,1e4,0);
  gSDp->SetLineColor(kGreen);
  gSDp->SetLineWidth(6);
  gSDp->SetLineStyle(7);
  gSDp->SetName("ANAIS+");
  gSDp->Draw("same");

  axis->Draw();
  gPad->BuildLegend();
  gPad->Update();
  c->SaveAs("ANAISPLUSSDp.png");

  ////////////////////////////
  // SDn
  ////////////////////////////
  //c = new TCanvas("c","",820,500);
  c = new TCanvas("cSDn","",820*1.5,500*1.5);
  frame = gPad->DrawFrame(mL, sL, mH, sH);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  //img =  TImage::Open("SI_lowMass_0.3_50_m14_m1.png");
  //img =  TImage::Open("exclusionSI_europeanParticleUpdate_noAxis_2em4TeV_100TeV_1m50cm2_1m37cm2.JPG");
  //img->SetConstRatio(kFALSE);
  //img->Draw();
  frame->GetYaxis()->SetTitle("#sigma_{SDn} (cm^{2})");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");

  TGraph * gSDn;
  // 1.
  gSDn = plothl.GetSDnExclusion(0.1,1e4,0); // this is in GeV
  gSDn->SetLineColor(kBlue);
  gSDn->SetLineWidth(6);
  gSDn->Draw("l");
  gSDn->SetName("ANAIS+ (10 kgxyr)");
  // effect of minInt
  gSDn = plothl.GetSDnExclusion(0.1,1e4,minInt);
  gSDn->SetLineColor(kGreen);
  gSDn->SetLineWidth(6);
  gSDn->SetLineStyle(7);
  gSDn->Draw("same");

  gPad->BuildLegend();
  gPad->Update();
  c->SaveAs("ANAISPLUSSDn.png");
*/
}
