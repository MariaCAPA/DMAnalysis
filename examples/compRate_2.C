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
  gStyle->SetTitleOffset(1.1,"y");
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
hXe->SetLineColor(kRed); hXe->SetMarkerColor(kRed);
hXe->SetLineWidth(4);
hAr->SetLineColor(kGreen); hAr->SetMarkerColor(kGreen);
hAr->SetLineWidth(4);
hNaI->SetLineColor(kBlue); hNaI->SetMarkerColor(kBlue);
hNaI->SetLineWidth(4);

TCanvas * c = new TCanvas(); c->SetLogy();
//c->SetLogy();
hXe->Scale(1000.*365);
hAr->Scale(1000.*365);
hNaI->Scale(1000.*365);
hXe->GetYaxis()->SetTitle("Rate (c/keV/ton/year)");
hXe->GetXaxis()->SetTitle("energy (keV_{NR})");
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
  pp->AddText(Form("m_{#chi}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->SetBorderSize(0);
  pp->Draw();

c->SaveAs("compRate.pdf");



}

void compRateNa(double si=1e-10)
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
  gStyle->SetTitleOffset(1.1,"y");
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

DMRate * rNa = new DMRate();
rNa->Initialize("rateNa.dat");

DMRate * rNa2 = new DMRate();
rNa2->Initialize("rateNa.dat");

DMRate * rNa3 = new DMRate();
rNa3->Initialize("rateNa.dat");

rNa->GetElement(0)->SetREF(1);

rNa->SetSigSI(si);
rNa->SetMW(10);

rNa2->GetElement(0)->SetREF(1);

rNa2->SetSigSI(si);
rNa2->SetMW(100);

rNa3->GetElement(0)->SetREF(1);

rNa3->SetSigSI(si);
rNa3->SetMW(1000);

DMRatePlotHandle plNa (rNa);
DMRatePlotHandle plNa2 (rNa2);
DMRatePlotHandle plNa3 (rNa3);

TH1F * hNa = plNa.GetRate(nbins,emin,emax);
TH1F * hNa2 = plNa2.GetRate(nbins,emin,emax);
TH1F * hNa3 = plNa3.GetRate(nbins,emin,emax);

////////////////////////
// PLOT
hNa->SetLineColor(kViolet+1); hNa->SetMarkerColor(kViolet+1);
hNa->SetLineWidth(4);

hNa2->SetLineColor(kOrange+1); hNa2->SetMarkerColor(kOrange+1);
hNa2->SetLineWidth(4);

hNa3->SetLineColor(kGreen+1); hNa3->SetMarkerColor(kGreen+1);
hNa3->SetLineWidth(4);


TCanvas * c = new TCanvas(); c->SetLogy();
//c->SetLogy();
hNa->Scale(1000.*365);
hNa2->Scale(1000.*365);
hNa3->Scale(1000.*365);

hNa->GetYaxis()->SetTitle("Rate (c/keV/ton/year)");
hNa->GetXaxis()->SetTitle("energy (keV_{NR})");
hNa->Draw("lhist");
hNa2->Draw("lhistsame");
hNa3->Draw("lhistsame");

TLegend * leg = new TLegend(0.75,0.50,0.99,0.92);
leg->SetTextSize(0.04);
leg->AddEntry(hNa,"^{23}Na","");
leg->AddEntry(hNa,"m_{#chi} = 10 GeV","l");
leg->AddEntry(hNa2,"m_{#chi} = 100 GeV","l");
leg->AddEntry(hNa3,"m_{#chi} = 1 TeV","l");

leg->Draw();
 leg->SetFillColor(kWhite);
 // leg->SetTextSize(0.04);

 TPaveText * pp = new TPaveText(0.35,0.75,0.65,.89,"NDC");
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->SetBorderSize(0);
  pp->Draw();

c->SaveAs("compRate_Na.pdf");



}


void compRateI(double si=1e-10)
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
  gStyle->SetTitleOffset(1.1,"y");
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

DMRate * rNa = new DMRate();
rNa->Initialize("rateI.dat");

DMRate * rNa2 = new DMRate();
rNa2->Initialize("rateI.dat");

DMRate * rNa3 = new DMRate();
rNa3->Initialize("rateI.dat");

rNa->GetElement(0)->SetREF(1);

rNa->SetSigSI(si);
rNa->SetMW(10);

rNa2->GetElement(0)->SetREF(1);

rNa2->SetSigSI(si);
rNa2->SetMW(100);

rNa3->GetElement(0)->SetREF(1);

rNa3->SetSigSI(si);
rNa3->SetMW(1000);

DMRatePlotHandle plNa (rNa);
DMRatePlotHandle plNa2 (rNa2);
DMRatePlotHandle plNa3 (rNa3);

TH1F * hNa = plNa.GetRate(nbins,emin,emax);
TH1F * hNa2 = plNa2.GetRate(nbins,emin,emax);
TH1F * hNa3 = plNa3.GetRate(nbins,emin,emax);

////////////////////////
// PLOT
hNa->SetLineColor(kViolet+1); hNa->SetMarkerColor(kViolet+1);
hNa->SetLineWidth(4);

hNa2->SetLineColor(kOrange+1); hNa2->SetMarkerColor(kOrange+1);
hNa2->SetLineWidth(4);

hNa3->SetLineColor(kGreen+1); hNa3->SetMarkerColor(kGreen+1);
hNa3->SetLineWidth(4);


TCanvas * c = new TCanvas(); c->SetLogy();
//c->SetLogy();
hNa->Scale(1000.*365);
hNa2->Scale(1000.*365);
hNa3->Scale(1000.*365);

hNa->GetYaxis()->SetTitle("Rate (c/keV/ton/year)");
hNa->GetXaxis()->SetTitle("energy (keV_{NR})");
hNa->GetYaxis()->SetRangeUser(1e-5,100);	
hNa->Draw("lhist");
hNa2->Draw("lhistsame");
hNa3->Draw("lhistsame");

TLegend * leg = new TLegend(0.75,0.50,0.99,0.92);
leg->SetTextSize(0.04);
leg->AddEntry(hNa,"^{127}I","");
leg->AddEntry(hNa,"m_{#chi} = 10 GeV","l");
leg->AddEntry(hNa2,"m_{#chi} = 100 GeV","l");
leg->AddEntry(hNa3,"m_{#chi} = 1 TeV","l");

leg->Draw();
 leg->SetFillColor(kWhite);
 // leg->SetTextSize(0.04);

 TPaveText * pp = new TPaveText(0.35,0.75,0.65,.89,"NDC");
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->SetBorderSize(0);
  pp->Draw();

c->SaveAs("compRate_I.pdf");



}
