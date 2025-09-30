void compRate(double si=1e-10, double mass=100)
{
   gSystem->Load("libDMAnalysis");


  double pbTocm=1e-36;
   gStyle->SetOptStat(0);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

  gStyle->SetOptTitle(0);

  gStyle->SetTextSize(1.1);
  gStyle->SetLabelSize(0.07,"xy");
  gStyle->SetTitleSize(0.07,"xy");
  gStyle->SetTitleOffset(1.0,"x");
  gStyle->SetTitleOffset(1.0,"y");
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.18);

  // MIO
  gStyle->SetLabelOffset(0.01,"xy");

  gStyle->SetNdivisions(510);



//double si=1e-4;
//double mass = 10;
// RATE BINNING
double emin=0;
double emax=100;
int nbins = 200;


int i;

DMRate * rXe = new DMRate();
DMRate * rAr = new DMRate();
DMRate * rNaI = new DMRate();

rXe->Initialize("rateXe.dat");
rAr->Initialize("rateAr.dat");
rNaI->Initialize("rateNaI.dat");

// no quenching -> plot nuclear recoil
rXe->GetElement(0)->SetREF(1);
rAr->GetElement(0)->SetREF(1);
rNaI->GetElement(0)->SetREF(1);
rNaI->GetElement(1)->SetREF(1);

rXe->SetSigSI(si);
rXe->SetMW(mass);
rAr->SetSigSI(si);
rAr->SetMW(mass);
rNaI->SetSigSI(si);
rNaI->SetMW(mass);

DMRatePlotHandle plXe (rXe);
DMRatePlotHandle plAr (rAr);
DMRatePlotHandle plNaI (rNaI);

TH1F * hXe = plXe.GetRate(nbins,emin,emax);
TH1F * hXem = plXe.GetModulatedRate(nbins,emin,emax);
TH1F * hAr = plAr.GetRate(nbins,emin,emax);
TH1F * hArm = plAr.GetModulatedRate(nbins,emin,emax);
TH1F * hNaI = plNaI.GetRate(nbins,emin,emax);
TH1F * hNaIm = plNaI.GetModulatedRate(nbins,emin,emax);

TH1F * hNaISummer = (TH1F*)hNaI->Clone("hNaISummer");
TH1F * hNaIWinter = (TH1F*)hNaI->Clone("hNaIWinter");
hNaISummer->Add(hNaIm);
hNaIWinter->Add(hNaIm,-1);

////////////////////////
// PLOT
hXe->SetLineColor(kRed);
hXe->SetLineWidth(4);
hAr->SetLineColor(kGreen);
hAr->SetLineWidth(4);
hNaI->SetLineColor(kBlue);
hNaI->SetLineWidth(4);

TCanvas * c = new TCanvas();
//c->SetLogy();
hXe->Scale(1000.*365);
hAr->Scale(1000.*365);
hNaI->Scale(1000.*365);
hXe->GetYaxis()->SetTitle("c / keV / ton / yr");
hXe->GetXaxis()->SetTitle("keV_{NR}");
hXe->Draw("lhist");
hAr->Draw("lhistsame");
hNaI->Draw("lhistsame");

TLegend * leg = new TLegend(0.75,0.50,0.9,0.9);
leg->AddEntry(hXe,"Xe ");
leg->AddEntry(hAr,"Ar ");
leg->AddEntry(hNaI,"NaI ");

leg->Draw();
 leg->SetFillColor(kWhite);
 // leg->SetTextSize(0.04);

 TPaveText * pp = new TPaveText(0.25,0.75,0.55,.89,"NDC");
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e cm^{2}",si*pbTocm));
  pp->SetFillColor(kWhite);
  pp->SetBorderSize(0);
  pp->Draw();

c->SaveAs("compRate.png");
////////////////////////
// PLOT modulated rate
hNaISummer->SetLineColor(kBlue);
hNaISummer->SetLineWidth(3);
hNaIWinter->SetLineColor(kBlue);
hNaIWinter->SetLineWidth(3);
hNaIWinter->SetLineStyle(7);

c = new TCanvas();

hNaISummer->Draw("lhist");
hNaIWinter->Draw("lhistsame");

leg = new TLegend(0.75,0.50,0.9,0.9);
leg->AddEntry(hNaISummer,"Summer ");
leg->AddEntry(hNaIWinter,"Winter ");
leg->Draw();
 leg->SetFillColor(kWhite);

c = new TCanvas();
hNaIm->Draw("l");

}
