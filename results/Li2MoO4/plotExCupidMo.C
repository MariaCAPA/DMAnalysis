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
void plotExCupidMo(int minInt=10) // min interval -> 1 keV
{
  gSystem->Load("libDMAnalysis");

  int error;
  DMExclusion * exclusion = new DMExclusion();
  error = exclusion->Initialize("exclusionCUPID.dat");
  if (error<0) return;


   gStyle->SetPadRightMargin(0.16);




  // SET BKG, EXPOSURE AND THRESHOLD
  exclusion->SetThreshold(5); // in keV
  exclusion->SetExposure(200*365); // in kgxd
  exclusion->SetLinearBkg(0.06); // in c/keVee/kg/d

  TGraph *gaux;

  // to test


  DMExclusionPlotHandle  plothl (exclusion);

  ////////////////////
  ////////////////////
  // SD proton
  c = new TCanvas("c","",650,500);
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

  double mass = 2; // kg 
  double time = 1*365; // 2 years
  int nth=4;
  double th[] = {1,2,5,10};
  double thColors[] = {kRed, kGreen, kBlue, kBlack};
  int nbkg=3;
  double bkg[]= {1,5,10};
  double bkgLines[]= {1,3,7};

  exclusion->SetExposure(mass*time); // in kgxd

  for (int ith=0; ith<nth; ith++)
  {
    for (int ibkg=0; ibkg<nbkg; ibkg++)
    {
      exclusion->SetThreshold(th[ith]); // in keV
      exclusion->SetLinearBkg(bkg[ibkg]); // in c/keVee/kg/d
      //gSDp = plothl.GetSDpExclusion(ith==3 ? 5 : 0.1,1e3,minInt);
      gSDp = plothl.GetSDpExclusion(0.1,1e3,minInt);
      gSDp->SetLineColor(thColors[ith]);
      gSDp->SetLineStyle(bkgLines[ibkg]);
      gSDp->SetLineWidth(3);
      gSDp->SetTitle(Form("exposure %d kg x %d y threshold %d keV bkg %d c/keV/kg/d",2,time/365,th[ith],bkg[ibkg]));
      if (ith==3) 
      { 
        // remove massses below 2 GeV
        double mw,yy;
        do { gSDp->GetPoint(0,mw,yy); if (mw<2) gSDp->RemovePoint(0);} while (mw<2);
      }
      gSDp->Draw("same");
    }
  }

  // 2.


  gPad->Update();

  c->SaveAs("cupidSDpMo.png");
  //c->SaveAs("cupidSDpMo.eps");

  ////////////////////
  ////////////////////
  // SD neutron

  c = new TCanvas("c2","",650,500);
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




  for (int ith=0; ith<nth; ith++)
  {
    for (int ibkg=0; ibkg<nbkg; ibkg++)
    {
      exclusion->SetThreshold(th[ith]); // in keV
      exclusion->SetLinearBkg(bkg[ibkg]); // in c/keVee/kg/d
      //gSDn = plothl.GetSDnExclusion(ith==3 ? 5 : 0.1,1e3,minInt);
      gSDn = plothl.GetSDnExclusion(0.1,1e3,minInt);
      gSDn->SetLineColor(thColors[ith]);
      gSDn->SetLineStyle(bkgLines[ibkg]);
      gSDn->SetLineWidth(3);
      gSDn->SetTitle(Form("exposure %d kg x %d y threshold %d keV bkg %d c/keV/kg/d",2,time/365,th[ith],bkg[ibkg]));
      if (ith==3) 
      { 
        // remove massses below 2 GeV
        double mw,yy;
        do { gSDn->GetPoint(0,mw,yy); if (mw<2) gSDn->RemovePoint(0);} while (mw<2);
      }
      gSDn->Draw("same");
    }
  }

  gPad->Update();

  c->SaveAs("cupidSDnMo.png");
  //c->SaveAs("cupidSDn.eps");

}
