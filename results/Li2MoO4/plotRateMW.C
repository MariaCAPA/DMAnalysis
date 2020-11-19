////////////////////////
// Example plotRateMW.C
// - Initialize a DMRate class with parameters from templates/rate.dat
//          * Detector with three elements Li Mo O
//            whose parameters are readed from  files
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Calculate the rate for 3 different wimp masses (10, 100, 1000 GeV)
//   and superpose them in a plot
void plotRateMW()
{
  gSystem->Load("libDMAnalysis");

  // Initalize rate class
  int error;
  DMRate * rate = new DMRate();
  error = rate->Initialize("rateSI.dat");
  if (error<0) return;

/*
  for (int  iel=0; iel<rate->GetNElements(); iel++)
    rate->GetElement(0)->SetREF(cRef[iel]);
*/


  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);

  double MW [4] = {1, 2, 5,10}; // GeV

  TFile * fout = new TFile("rateLi2Mo4.root","recreate");

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TH1F * haux;
  TH1F * hrate;
  TCanvas * c = new TCanvas(); 
  c->SetLogy();
  for (int i=0; i<4; i++)
  {
    hrate = plothl.GetSIRate(MW[i], 1, 1000); // NBins between 0 and 100 keV, by default 100
    hrate->SetTitle(Form("SI rate #sigma = 1 pb M_{W} = %d GeV",(int)MW[i]));
    hrate->SetName(Form("si_1pb_mw%dGeV",(int)MW[i]));
    hrate->SetLineColor(i+1);
    hrate->SetLineWidth(3);
    hrate->Write();

    if (i==0) 
    {
      haux = (TH1F*)hrate->DrawClone("c");
    }
    else 
    {
      hrate->DrawClone("csame");
    }
  }
  // change axis here
  haux->GetXaxis()->SetRangeUser(0,30);
  c->BuildLegend();

  c->SaveAs("plotRateMW_SI.jpg");

  ////////////////////////// SD p
  error = rate->Initialize("rateSD.dat");
  if (error<0) return;
  c = new TCanvas(); 
  c->SetLogy();
  for (int i=0; i<4; i++)
  {
    hrate = plothl.GetSDpRate(MW[i], 1, 1000); // NBins between 0 and 100 keV, by default 100
    hrate->SetTitle(Form("SDp rate #sigma = 1 pb M_{W} = %d GeV",(int)MW[i]));
    hrate->SetName(Form("sdp_1pb_mw%dGeV",(int)MW[i]));
    hrate->SetLineColor(i+1);
    hrate->SetLineWidth(3);
    hrate->Write();

    if (i==0) 
    {
      haux = (TH1F*)hrate->DrawClone("c");
    }
    else 
    {
      hrate->DrawClone("csame");
    }
  }
  // change axis here
  haux->GetXaxis()->SetRangeUser(0,30);
  c->BuildLegend();

  c->SaveAs("plotRateMW_SDp.jpg");

  ////////////////////////// SD n
  c = new TCanvas(); 
  c->SetLogy();
  for (int i=0; i<4; i++)
  {
    hrate = plothl.GetSDnRate(MW[i], 1, 1000); // NBins between 0 and 100 keV, by default 100
    hrate->SetTitle(Form("SDn rate #sigma = 1 pb M_{W} = %d GeV",(int)MW[i]));
    hrate->SetName(Form("sdn_1pb_mw%dGeV",(int)MW[i]));
    hrate->SetLineColor(i+1);
    hrate->SetLineWidth(3);
    hrate->Write();

    if (i==0) 
    {
      haux = (TH1F*)hrate->DrawClone("c");
    }
    else 
    {
      hrate->DrawClone("csame");
    }
  }
  // change axis here
  haux->GetXaxis()->SetRangeUser(0,30);
  c->BuildLegend();

  c->SaveAs("plotRateMW_SDn.jpg");
  //fout->Close();

}
