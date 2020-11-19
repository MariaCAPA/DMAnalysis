////////////////////////
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
void compareWithCresst(int minInt=10) // min interval -> 1 keV
{
  gSystem->Load("libDMAnalysis");

  int error;
  DMExclusion * exclusion = new DMExclusion();
  error = exclusion->Initialize("exclusionCRESST.dat");
  if (error<0) return;





  // SET BKG, EXPOSURE AND THRESHOLD
  exclusion->SetThreshold(0.932); // in keV
  //exclusion->SetThreshold(0.702); // in keV

  //exclusion->SetExposure(7.9e-5); // in kg*day
  exclusion->SetExposure(1.073e-3 );

  TGraph *gaux;
  double  bkg = 2.37e4;

  // to test
  //exclusion->SetLinearBkg(0.); // in c/keVee/kg/d
  //exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d

  /////////////////
  // SD proton -> Theta = 0
  //DMRate  * rate = exclusion->GetTheoRate();
  //rate->GetElement(0)->SetTheta(0);

  c = new TCanvas();
  TH1F * frame = gPad->DrawFrame(0.8,1e-5,20,1e10);
  frame ->GetYaxis()->SetTitle("#sigma_{SD}^{p} (pb)");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  TImage * img =  TImage::Open("cresst_sdp_0.8_20_1em5_1e10.jpg");
  img->SetConstRatio(kFALSE);
  img->Draw();

  ////////////////////
  ////////////////////
  // SD proton
  TGraph * gSDp;

  DMExclusionPlotHandle  plothl (exclusion);
  gSDp = plothl.GetSDpExclusion(0.1,1e3,minInt);
  gSDp->SetLineColor(kCyan);
  gSDp->SetLineWidth(4);
  gSDp->SetTitle(Form("%0.2f c/keV/kg/d",bkg));
  gSDp->Draw("same");
  gPad->Update();


  ////////////////////
  ////////////////////
  // SD neutron

  c = new TCanvas();
  frame = gPad->DrawFrame(0.8,1e-5,20,1e15);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  img =  TImage::Open("cresst_sdn_0.8_20_1em5_1e15.jpg");
  img->SetConstRatio(kFALSE);
  img->Draw();


  TGraph * gSDn;

  DMExclusionPlotHandle  plothl (exclusion);
  gSDn = plothl.GetSDnExclusion(0.1,1e3,minInt);
  gSDn->SetLineColor(kCyan);
  gSDn->SetLineWidth(4);
  gSDn->SetTitle(Form(""));
  frame ->GetYaxis()->SetTitle("#sigma_{SD}^{n} (pb)");
  frame ->GetXaxis()->SetTitle("m_{W} (GeV)");
  gSDn->Draw("same");
gPad->Update();

  

}
