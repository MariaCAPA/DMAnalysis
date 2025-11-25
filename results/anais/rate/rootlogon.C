{
   //gSystem.Load("/media/sf_D/Users/Maria/DMAnalysis/lib/DMAnalysis.so");
  //gSystem->AddDynamicPath("$DMANALYSIS/lib");
  gSystem->Load("libDMAnalysis.so");
  gSystem->Load("libProofPlayer.so");
  gSystem->Load("/usr/lib/libgsl.so");

//  gROOT->ProcessLine(".L compRate.C");

  gStyle->SetOptStat(0);

  // GRID ON
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);

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
  gStyle->SetTitleSize(0.06,"xy");
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPadTopMargin(0.03);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadBottomMargin(0.16);
  //gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadLeftMargin(0.18);

  // MIO
  //gStyle->SetLabelOffset(0.02,"x");
  //gStyle->SetLabelOffset(0.01,"y");

  gStyle->SetNdivisions(507);


}
