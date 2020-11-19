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
void plotExCupid(int minInt=10) // min interval -> 1 keV
{
  gSystem->Load("libDMAnalysis");

  int error;
  DMExclusion * exclusion = new DMExclusion();
  error = exclusion->Initialize("exclusionCUPID.dat");
  if (error<0) return;


   gStyle->SetPadRightMargin(0.16);




  // SET BKG, EXPOSURE AND THRESHOLD
  exclusion->SetThreshold(5); // in keV
  exclusion->SetExposure(0.242*1500*365); // in kgxd
  exclusion->SetLinearBkg(0.06); // in c/keVee/kg/d

  TGraph *gaux;

  // to test


  DMExclusionPlotHandle  plothl (exclusion);

  ////////////////////
  ////////////////////
  // SD proton
  //c = new TCanvas("c","",650,500);
  c = new TCanvas("c","",650*2,500*2);
  double mL=0.8;
  double mH=20;
  double sL=1e-5;
  double sH=1e10;
  TH1F * frame = gPad->DrawFrame(mL,sL,mH,sH);
  frame ->GetYaxis()->SetTitle("#sigma_{SD}^{p} (pb)");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  //TImage * img =  TImage::Open("cresst_sdp_0.8_20_1em5_1e10.jpg");
  TImage * img =  TImage::Open("cresst_EPJC_2019_79_630_noAxis_08_20_em5_e10.png");
  img->SetConstRatio(kFALSE);
  img->Draw();

  double pb2cm=1e-36;
  TGaxis *axis = new TGaxis(mH,sL,mH,sH,sL*pb2cm,sH*pb2cm,50510,"+LG");
  axis->SetLabelOffset(0.01);
  axis->SetLabelFont(42);
  axis->SetTitle("#sigma_{SD}^{p} (cm^{2})");
  axis->SetTitleFont(42);
  axis->SetLabelSize(0.05);
  axis->SetTitleSize(0.07);
  axis->SetTitleOffset(1.1);
  axis->Draw();


  TGraph * gSDp;

  double mass = 0.242*1500;
  double time = 1*365;
  double th = 5;
  double bkg=0.01;


  // 1.
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDp = plothl.GetSDpExclusion(0.1,1e3,minInt);
  gSDp->SetLineColor(kBlue);
  gSDp->SetLineWidth(6);
  gSDp->Draw("same");

  // 2.
/*
  mass = 0.242*1500;
  time = 1*365;
  th = 5;
  bkg=0.001;

  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDp = plothl.GetSDpExclusion(0.1,1e3,minInt);
  gSDp->SetLineColor(kBlue);
  gSDp->SetLineWidth(4);
  gSDp->SetLineStyle(7);
  gSDp->Draw("same");
*/

  // 3.
  mass = 0.242*1500;
  time = 1*365;
  th = 1;
  bkg=0.01;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDp = plothl.GetSDpExclusion(0.1,1e3,minInt);
  gSDp->SetLineColor(kRed);
  gSDp->SetLineWidth(6);
  gSDp->Draw("same");

  // 4.
  mass = 0.242*1500;
  time = 1*365;
  th = 1;
  bkg=0.001;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDp = plothl.GetSDpExclusion(0.1,1e3,minInt);
  gSDp->SetLineColor(kGreen);
  gSDp->SetLineWidth(6);
  //gSDp->SetLineStyle(7);
  gSDp->Draw("same");


  gPad->Update();

  c->SaveAs("cupidSDp.png");
  c->SaveAs("cupidSDp.eps");

  ////////////////////
  ////////////////////
  // SD neutron

  //c = new TCanvas("c2","",650,500);
  c = new TCanvas("c2","",650*2,500*2);
  frame = gPad->DrawFrame(mL,sL,mH,sH);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  img =  TImage::Open("cresst_sdn_0.8_20_1em5_1e15.jpg");
  img->SetConstRatio(kFALSE);
  img->Draw();
  frame ->GetYaxis()->SetTitle("#sigma_{SD}^{n} (pb)");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");

  axis = new TGaxis(mH,sL,mH,sH,sL*pb2cm,sH*pb2cm,50510,"+LG");
  axis->SetLabelOffset(0.01);
  axis->SetLabelFont(42);
  axis->SetTitle("#sigma_{SD}^{n} (cm^{2})");
  axis->SetTitleFont(42);
  axis->SetLabelSize(0.05);
  axis->SetTitleSize(0.07);
  axis->SetTitleOffset(1.1);
  axis->Draw();


  TGraph * gSDn;
  // 1.
  mass = 0.242*1500;
  time = 1*365;
  th = 5;
  bkg=0.01;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDn = plothl.GetSDnExclusion(0.1,1e3,minInt);
  gSDn->SetLineColor(kBlue);
  gSDn->SetLineWidth(6);
  gSDn->Draw("same");

  // 2.
/*
  mass = 0.242*1500;
  time = 1*365;
  th = 5;
  bkg=0.001;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDn = plothl.GetSDnExclusion(0.1,1e3,minInt);
  gSDn->SetLineColor(kBlue);
  gSDn->SetLineWidth(4);
  gSDn->SetLineStyle(7);
  gSDn->Draw("same");
*/

  // 3.
  mass = 0.242*1500;
  time = 1*365;
  th = 1;
  bkg=0.01;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDn = plothl.GetSDnExclusion(0.1,1e3,minInt);
  gSDn->SetLineColor(kRed);
  gSDn->SetLineWidth(6);
  gSDn->Draw("same");


  // 4.
/*
  mass = 0.242*1500;
  time = 1*365;
  th = 1;
  bkg=0.001;
  exclusion->SetThreshold(th); // in keV
  exclusion->SetExposure(mass*time); // in kgxd
  exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  gSDn->SetLineColor(kGreen);
  gSDn->SetLineWidth(6);
  //gSDn->SetLineStyle(7);
  gSDn->Draw("same");

  gPad->Update();
*/

  c->SaveAs("cupidSDn.png");
  c->SaveAs("cupidSDn.eps");

}
