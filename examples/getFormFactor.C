////////////////////////
// Example plotRateMW.C
// - Initialize a DMRate class with parameters from templates/rate.dat
//          * Detector with two elements Na, I 
//            whose parameters are readed from templates/Na.dat, templates/I.dat 
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Calculate the rate for 3 different wimp masses (10, 100, 1000 GeV)
//   and superpose them in a plot
void getFormFactor(char * file = "$DMANALYSIS/templates/I.dat")
{
   gSystem->Load("libDMAnalysis");
  double si = 1e-5;
  double sd = 1e-5;

  double maxE=200;
  int error;

  DMElement * el = new DMElement();
  error = el->Initialize(file);
  if (error<0) return;

  TH1F * hffsi = new TH1F("ffsi","",1000,0,maxE);
  TH1F * hffsd = new TH1F("ffsd","",1000,0,maxE);
  ////////////////////////
  TCanvas * c = new TCanvas();
  c->SetLogy();

  for (double ene=0.1; ene<maxE; ene+=0.2)
  {
    hffsi->Fill(ene,el->FF2SI(ene));
  }
  hffsi->Draw("hist");
  c->BuildLegend();

  //c->SaveAs("plotRateMW.jpg");
  c = new TCanvas();
  c->SetLogy();

  for (double ene=0.1; ene<maxE; ene+=0.2)
  {
    hffsd->Fill(ene,el->FF2SD(ene));
  }
  hffsd->Draw("hist");
  c->BuildLegend();

}
