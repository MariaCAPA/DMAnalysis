{
  
  //gSystem.Load("/media/sf_D/Users/Maria/DMAnalysis/lib/DMAnalysis.so");
  gSystem.Load("DMAnalysis.so");
  gSystem.Load("libProofPlayer.so");
  gSystem.Load("/usr/lib/libgsl.so");


  gROOT->ProcessLine(".L compSen.C");
  gStyle->SetOptStat(0);
  //gStyle->SetFillColor(0);

  // GRID ON
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);

   gStyle->SetOptTitle(0);

  // Hist line width
  gStyle->SetHistLineWidth(2);


   //////////////////////////////////////////
  //////////////////////////////////////////
  //////////////////////////////////////////

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
  gStyle->SetTitleOffset(1.0,"y");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.12);

  // MIO
  gStyle->SetLabelOffset(0.01,"xy");


}
