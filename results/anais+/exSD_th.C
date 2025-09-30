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
void exSD_th(int minInt=10) // bines de 0.1 keV 1 keV -> 10 bines
{
   gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

   gStyle->SetOptTitle(0);

  // Hist line width
  gStyle->SetHistLineWidth(2);
  gStyle->SetLineWidth(2);

  ///////////////////////////////////////////
  ///////////////////////////////////////////
  ///////////////////////////////////////////

  gStyle->SetOptTitle(0);
  gStyle->SetCanvasColor(kWhite);     // background is no longer mouse-dropping white
  gStyle->SetPalette(1,0);            // blue to red false color palette. Use 9 for b/w
  gStyle->SetCanvasBorderMode(0);     // turn off canvas borders
  gStyle->SetPadBorderMode(0);
  gStyle->SetPaintTextFormat("5.2f");  // What precision to put numbers if plotted with "TEXT"

  // For publishing:
  gStyle->SetLineWidth(2.);
  gStyle->SetTextSize(1.1);
  gStyle->SetLabelSize(0.06,"xy");
  gStyle->SetLabelOffset(0.0,"x");
  gStyle->SetTitleSize(0.06,"xy");
  gStyle->SetTitleOffset(0.8,"x");
  gStyle->SetTitleOffset(1.4,"y");
  gStyle->SetPadTopMargin(60.00);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.10);
  //gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadLeftMargin(0.18);


  int error;
  DMExclusion * exclusion = new DMExclusion();
  error = exclusion->Initialize("exclusion.dat");
  if (error<0) return;


   // SET BKG, EXPOSURE AND THRESHOLD
  double eth=0.25;
  double bkg = 1;
  exclusion->SetExposure(365); // in kgxday
  exclusion->SetLinearBkg(bkg); // in kgxday
  exclusion->SetWindow(0,10);

  TGraph *gaux;


  /////////////////
  // SD proton -> Theta = 0
  //DMRate  * rate = exclusion->GetTheoRate();
  //rate->GetElement(0)->SetTheta(0);

  TCanvas * c = new TCanvas("c","",650,530);
  //c = new TCanvas("c","",2*650,2*530);
  //TH1F * frame = gPad->DrawFrame(0.3,1e-1,10,1e7);
  TH1F * frame = gPad->DrawFrame(0.2,1e-2,6,1e11);
  frame ->GetYaxis()->SetTitle("#sigma_{SD}^{p} (pb)");
  frame ->GetXaxis()->SetTitle("Wimp mass (GeV)");
  frame ->GetXaxis()->SetNoExponent(1);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  TImage * img =  TImage::Open("cresstIII_Li_2022_noaxis_0.2_6_1em2_1e11.PNG");
  img->SetConstRatio(kFALSE);
  img->Draw();
gPad->Update();

  TGraph * gSDp;

  //exclusion->SetLinearBkg(bkg); // in c/keVee/kg/d
  DMExclusionPlotHandle  plothl (exclusion);
  std::vector <double> threshold;
  threshold.push_back(0.25);
  threshold.push_back(0.15);
  threshold.push_back(0.10);
  threshold.push_back(0.05);
  for (int ii=0; ii<threshold.size(); ii++)
  {
    exclusion->SetThreshold(threshold[ii]); // in keV
    gSDp = plothl.GetSDpExclusion(0.1,10,minInt);
    gSDp->SetLineColor(kViolet);
    gSDp->SetLineWidth(3);
  //gSDp->SetTitle(Form("exposure 1 kg #times 1 y, threshold %0.0f eV, bkg %0.1f cpd/kg/keV",threshold[ii]*1000, bkg));
    gSDp->Draw("same");
  }
  
  //l->AddEntry(gSDp);
  //l->SetFillColor(kWhite);
  //l->SetBorderSize(0);
  //l->Draw();

  gPad->Update();
//gPad->SaveAs("naIDemSDp.png");


}
