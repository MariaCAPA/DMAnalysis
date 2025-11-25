TGraph * grshadeNaC;
TGraph * grshadeNaI;
TGraph * grshadetotCm;
compRateSumCollarDAMA(double si=2e-4, double mass=10)
{

//double si=1e-4;
//double mass = 10;
// RATE BINNING
double emin=0;
double emax=10;
int nbins = 200;

double ANa=23;
double AI=127;
double Atot=ANa+AI;

int i;

  //////////////////////
  // QUENCHING FACTORS
  // Open file with q factors
  TFile * f = new TFile ("$DMANALYSIS/templates/quenchingNaIee.root","read");
  if (!f) {std::cout << " CANNOT READ QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  TGraph * gQNaC=(TGraph*)f->Get("gQNaCollaree");
  if (!gQNaC) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQNaCl=(TGraph*)f->Get("gQNaCollaree_l");
  if (!gQNaCl) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQNaCh=(TGraph*)f->Get("gQNaCollaree_h");
  if (!gQNaCh) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQIC=(TGraph*)f->Get("gQICollaree");
  if (!gQIC) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQICl=(TGraph*)f->Get("gQICollaree_l");
  if (!gQIC) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQICh=(TGraph*)f->Get("gQICollaree_h");
  if (!gQICh) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

   // TRETYAK
  TGraph * gQNaT=(TGraph*)f->Get("gQNaTretyakee");
  if (!gQNaT) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQIT=(TGraph*)f->Get("gQITretyakee");
  if (!gQIT) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}



// COLLAR
DMRate * rtotC = new DMRate();
DMRate * rtotCl = new DMRate();
DMRate * rtotCh = new DMRate();
DMRate * rNaC = new DMRate();
DMRate * rNaCl = new DMRate();
DMRate * rNaCh = new DMRate();
DMRate * rIC = new DMRate();
DMRate * rICl = new DMRate();
DMRate * rICh = new DMRate();

rNaC->Initialize("rateNa.dat");
rNaCl->Initialize("rateNa.dat");
rNaCh->Initialize("rateNa.dat");
rIC->Initialize("rateI.dat");
rICl->Initialize("rateI.dat");
rICh->Initialize("rateI.dat");
rtotC->Initialize("rate.dat");
rtotCl->Initialize("rate.dat");
rtotCh->Initialize("rate.dat");
// init REFS variable with E
rNaC->GetElement(0)->SetREF(gQNaC);
rNaCl->GetElement(0)->SetREF(gQNaCl);
rNaCh->GetElement(0)->SetREF(gQNaCh);

rIC->GetElement(0)->SetREF(gQIC);
rICl->GetElement(0)->SetREF(gQICl);
rICh->GetElement(0)->SetREF(gQICh);

rtotC->GetElement(0)->SetREF(gQNaC);
rtotCl->GetElement(0)->SetREF(gQNaCl);
rtotCh->GetElement(0)->SetREF(gQNaCh);
rtotC->GetElement(1)->SetREF(gQIC);
rtotCl->GetElement(1)->SetREF(gQICl);
rtotCh->GetElement(1)->SetREF(gQICh);

rtotC->SetSigSI(si);
rtotCl->SetSigSI(si);
rtotCh->SetSigSI(si);
rNaC->SetSigSI(si);
rNaCl->SetSigSI(si);
rNaCh->SetSigSI(si);
rIC->SetSigSI(si);
rICl->SetSigSI(si);
rICh->SetSigSI(si);

rtotC->SetMW(mass);
rtotCl->SetMW(mass);
rtotCh->SetMW(mass);
rNaC->SetMW(mass);
rNaCl->SetMW(mass);
rNaCh->SetMW(mass);
rIC->SetMW(mass);
rICl->SetMW(mass);
rICh->SetMW(mass);

DMRatePlotHandle plNaC (rNaC);
DMRatePlotHandle plNaCl (rNaCl);
DMRatePlotHandle plNaCh (rNaCh);

DMRatePlotHandle plIC (rIC);
DMRatePlotHandle plICl (rICl);
DMRatePlotHandle plICh (rICh);

DMRatePlotHandle pltotC (rtotC);
DMRatePlotHandle pltotCl (rtotCl);
DMRatePlotHandle pltotCh (rtotCh);

TH1F * hNaC = plNaC.GetRate(nbins,emin,emax);
TH1F * hNaCm = plNaC.GetModulatedRate(nbins,emin,emax);

TH1F * hNaCl = plNaCl.GetRate(nbins,emin,emax);
TH1F * hNaClm = plNaCl.GetModulatedRate(nbins,emin,emax);
TH1F * hNaCh = plNaCh.GetRate(nbins,emin,emax);
TH1F * hNaChm = plNaCh.GetModulatedRate(nbins,emin,emax);

TH1F * hIC = plIC.GetRate(nbins,emin,emax);
TH1F * hICm = plIC.GetModulatedRate(nbins,emin,emax);

TH1F * hICl = plICl.GetRate(nbins,emin,emax);
TH1F * hIClm = plICl.GetModulatedRate(nbins,emin,emax);

TH1F * hICh = plICh.GetRate(nbins,emin,emax);
TH1F * hIChm = plICh.GetModulatedRate(nbins,emin,emax);

TH1F * htotC = pltotC.GetRate(nbins,emin,emax);
TH1F * htotCm = pltotC.GetModulatedRate(nbins,emin,emax);

TH1F * htotCl = pltotCl.GetRate(nbins,emin,emax);
TH1F * htotClm = pltotCl.GetModulatedRate(nbins,emin,emax);

TH1F * htotCh = pltotCh.GetRate(nbins,emin,emax);
TH1F * htotChm = pltotCh.GetModulatedRate(nbins,emin,emax);

hIC->Scale(AI/Atot);
hICl->Scale(AI/Atot);
hICh->Scale(AI/Atot);
hNaC->Scale(ANa/Atot);
hNaCl->Scale(ANa/Atot);
hNaCh->Scale(ANa/Atot);
hICm->Scale(AI/Atot);
hIClm->Scale(AI/Atot);
hIChm->Scale(AI/Atot);
hNaCm->Scale(ANa/Atot);
hNaClm->Scale(ANa/Atot);
hNaChm->Scale(ANa/Atot);

// DAMA
DMRate * rTotS = new DMRate();
rTotS->Initialize("rate.dat");
rTotS->GetElement(0)->SetREF(0.3);
rTotS->GetElement(1)->SetREF(0.1);
rTotS->SetSigSI(si);
rTotS->SetMW(mass);
DMRatePlotHandle pltotS (rTotS);

TH1F * htotS  = pltotS.GetRate(nbins,emin,emax);
TH1F * htotSm = pltotS.GetModulatedRate(nbins,emin,emax);

// Na
DMRate * rNaS = new DMRate();
rNaS->Initialize("rateNa.dat");
rNaS->GetElement(0)->SetREF(0.3);
rNaS->SetMW(mass);
rNaS->SetSigSI(si);
DMRatePlotHandle plNaS (rNaS);
TH1F * hNaS = plNaS.GetRate(nbins,emin,emax);
TH1F * hNaSm = plNaS.GetModulatedRate(nbins,emin,emax);
hNaS->Scale(ANa/Atot);
hNaSm->Scale(ANa/Atot);
// I
DMRate * rIS = new DMRate();
rIS->Initialize("rateI.dat");
rIS->GetElement(0)->SetREF(0.09);
rIS->SetMW(mass);
rIS->SetSigSI(si);
DMRatePlotHandle plIS (rIS);
TH1F * hIS = plIS.GetRate(nbins,emin,emax);
TH1F * hISm = plIS.GetModulatedRate(nbins,emin,emax);
hIS->Scale(AI/Atot);
hISm->Scale(AI/Atot);

////////////////////////
// PLOT
hNaC->SetLineColor(kRed);
hNaCl->SetLineColor(kRed);
hNaCh->SetLineColor(kRed);

hIC->SetLineColor(kRed);
hICl->SetLineColor(kRed);
hICh->SetLineColor(kRed);

htotC->SetLineColor(kRed);
htotCl->SetLineColor(kRed);
htotCh->SetLineColor(kRed);


hNaS->SetLineColor(kBlue);
hIS->SetLineColor(kBlue);

htotC->SetLineWidth(3);
hNaC->SetLineWidth(3);
hIC->SetLineWidth(3);
hNaS->SetLineWidth(3);
hIS->SetLineWidth(3);

hNaCl->SetLineWidth(1);
hNaCh->SetLineWidth(1);

hICl->SetLineWidth(1);
hICh->SetLineWidth(1);

htotCl->SetLineWidth(1);
htotCh->SetLineWidth(1);

hIC->SetLineStyle(9);
hICl->SetLineStyle(9);
hICh->SetLineStyle(9);
hIS->SetLineStyle(9);

//////////////////////
// RATE
TCanvas * c = new TCanvas();
c->SetLogy();

htotC->Draw("l");
htotCl->Draw("lsame");
htotCh->Draw("lsame");
htotS->Draw("lsame");
htotC->GetXaxis()->SetRangeUser(0,6);
htotC->GetYaxis()->SetRangeUser(1e-7,10000);

/*
hIC->Draw("l");
hICl->Draw("lsame");
hICh->Draw("lsame");
hNaC->Draw("lsame");
hNaCl->Draw("lsame");
hNaCh->Draw("lsame");
hNaS->Draw("lsame");
hIS->Draw("lsame");
hIC->GetXaxis()->SetRangeUser(0,6);
hIC->GetYaxis()->SetRangeUser(1e-7,100);
*/

// Shade for errors
int nAux = 3;
double aux[3];
int i;
int nn=hNaCh->GetNbinsX();
grshadeNaC = new TGraph(2*nn);
for (i=0;i<nn;i++)
{
  aux[0]= hNaC->GetBinContent(i+1);
  aux[1]= hNaCl->GetBinContent(i+1);
  aux[2]= hNaCh->GetBinContent(i+1);
  //grshadeNaC->SetPoint(i,hNaCh->GetBinCenter(i+1), hNaCh->GetBinContent(i+1));
  grshadeNaC->SetPoint(i,hNaCh->GetBinCenter(i+1), TMath::MaxElement(nAux,aux));
  aux[0]= hNaC->GetBinContent(nn-i);
  aux[1]= hNaCl->GetBinContent(nn-i);
  aux[2]= hNaCh->GetBinContent(nn-i);
  //grshadeNaC->SetPoint(nn+i,hNaCl->GetBinCenter(nn-i), hNaCl->GetBinContent(nn-i));
  grshadeNaC->SetPoint(nn+i,hNaCl->GetBinCenter(nn-i),TMath::MinElement(nAux,aux));
}
nn=hICh->GetNbinsX();
grshadeIC = new TGraph(2*nn);
for (i=0;i<nn;i++)
{
  aux[0]= hIC->GetBinContent(i+1);
  aux[1]= hICl->GetBinContent(i+1);
  aux[2]= hICh->GetBinContent(i+1);
  //grshadeIC->SetPoint(i,hICh->GetBinCenter(i+1), hICh->GetBinContent(i+1));
  grshadeIC->SetPoint(i,hICh->GetBinCenter(i+1), TMath::MaxElement(nAux,aux));
  aux[0]= hIC->GetBinContent(nn-i);
  aux[1]= hICl->GetBinContent(nn-i);
  aux[2]= hICh->GetBinContent(nn-i);
  //grshadeIC->SetPoint(nn+i,hICl->GetBinCenter(nn-i), hICl->GetBinContent(nn-i));
  grshadeIC->SetPoint(nn+i,hICl->GetBinCenter(nn-i),TMath::MinElement(nAux,aux));
}

nn=htotCh->GetNbinsX();
grshadetotC = new TGraph(2*nn);
for (i=0;i<nn;i++)
{
  aux[0]= htotC->GetBinContent(i+1);
  aux[1]= htotCl->GetBinContent(i+1);
  aux[2]= htotCh->GetBinContent(i+1);
  grshadetotC->SetPoint(i,htotCh->GetBinCenter(i+1), TMath::MaxElement(nAux,aux));
  aux[0]= htotC->GetBinContent(nn-i);
  aux[1]= htotCl->GetBinContent(nn-i);
  aux[2]= htotCh->GetBinContent(nn-i);
  grshadetotC->SetPoint(nn+i,htotCl->GetBinCenter(nn-i),TMath::MinElement(nAux,aux));
}
// DRAW ONLY TOTAL
grshadetotC->SetFillStyle(3013);
grshadetotC->SetFillColor(kRed);
grshadetotC->Draw("f");

grshadeNaC->SetFillStyle(3013);
grshadeNaC->SetFillColor(kRed);
grshadeIC->SetFillStyle(3013);
grshadeIC->SetFillColor(kRed);
//grshadeNaC->Draw("f");
//grshadeIC->Draw("f");


TLegend * leg = new TLegend(0.55,0.7,0.9,0.9);
//leg->AddEntry(hNaS,"Na Q=0.3");
TH1F * haux = (TH1F*)hNaC->Clone();
haux->SetFillStyle(3013);
haux->SetFillColor(kRed);
//leg->AddEntry(hNaC,"Na [Collar]");
//leg->AddEntry(haux,"Na [Collar]");
//leg->AddEntry(hIS,"I Q=0.1");
TH1F * haux2 = (TH1F*)hIC->Clone();
haux2->SetFillStyle(3013);
haux2->SetFillColor(kRed);
//leg->AddEntry(hIC,"I [Collar]");
//leg->AddEntry(haux2,"I [Collar]");
TH1F * hauxC = (TH1F*)htotC->Clone();
hauxC->SetFillStyle(3013);
hauxC->SetFillColor(kRed);
leg->AddEntry(hauxC,"NaI [Collar]");
leg->AddEntry(htotS,"NaI [Q_{Na}=0.3, Q_{I}=0.09]");
leg->Draw();
 leg->SetFillColor(kWhite);
  leg->SetTextSize(0.04);


TPaveText * pp = new TPaveText(0.7,0.55,0.90,.7,"NDC");
  pp->SetBorderSize(0);
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->Draw();

c->SaveAs(Form("rateCollarDama_mW%d.png",(int)mass));
////////////////////////
// PLOT modulated rate
hNaCm->SetLineColor(kRed);
hNaClm->SetLineColor(kRed);
hNaChm->SetLineColor(kRed);

hICm->SetLineColor(kRed);
hIClm->SetLineColor(kRed);
hIChm->SetLineColor(kRed);

htotCm->SetLineColor(kRed);
htotClm->SetLineColor(kRed);
htotChm->SetLineColor(kRed);


hNaSm->SetLineColor(kBlue);
hISm->SetLineColor(kBlue);

htotCm->SetLineWidth(3);
hNaCm->SetLineWidth(3);
hICm->SetLineWidth(3);
hNaSm->SetLineWidth(3);
hISm->SetLineWidth(3);

hNaClm->SetLineWidth(1);
hNaChm->SetLineWidth(1);

hIClm->SetLineWidth(1);
hIChm->SetLineWidth(1);

htotClm->SetLineWidth(1);
htotChm->SetLineWidth(1);

hICm->SetLineStyle(9);
hIClm->SetLineStyle(9);
hIChm->SetLineStyle(9);
hISm->SetLineStyle(9);

TCanvas * c = new TCanvas();

htotCm->Draw("l");
htotClm->Draw("lsame");
htotChm->Draw("lsame");
htotCm->GetXaxis()->SetRangeUser(0,6);
htotCm->GetYaxis()->SetRangeUser(-0.05,0.20);
htotSm->Draw("lsame");

/*
hICm->Draw("l");
hIClm->Draw("lsame");
hIChm->Draw("lsame");
hNaCm->Draw("lsame");
hNaClm->Draw("lsame");
hNaChm->Draw("lsame");
hNaSm->Draw("lsame");
hISm->Draw("lsame");
hICm->GetXaxis()->SetRangeUser(0,6);
hICm->GetYaxis()->SetRangeUser(-0.15,0.25);
*/

// Shade for errors
int i;
int nn=hNaChm->GetNbinsX();
grshadeNaCm = new TGraph(2*nn);
for (i=0;i<nn;i++)
{
  aux[0]= hNaCm->GetBinContent(i+1);
  aux[1]= hNaClm->GetBinContent(i+1);
  aux[2]= hNaChm->GetBinContent(i+1);
  //grshadeNaCm->SetPoint(i,hNaChm->GetBinCenter(i+1), hNaChm->GetBinContent(i+1));
  grshadeNaCm->SetPoint(i,hNaChm->GetBinCenter(i+1), TMath::MaxElement(nAux,aux));
  aux[0]= hNaCm->GetBinContent(nn-i);
  aux[1]= hNaClm->GetBinContent(nn-i);
  aux[2]= hNaChm->GetBinContent(nn-i);
  //grshadeNaCm->SetPoint(nn+i,hNaClm->GetBinCenter(nn-i), hNaClm->GetBinContent(nn-i));
  grshadeNaCm->SetPoint(nn+i,hNaClm->GetBinCenter(nn-i),TMath::MinElement(nAux,aux));
}
nn=hIChm->GetNbinsX();
grshadeICm = new TGraph(2*nn);
for (i=0;i<nn;i++)
{
  aux[0]= hICm->GetBinContent(i+1);
  aux[1]= hIClm->GetBinContent(i+1);
  aux[2]= hIChm->GetBinContent(i+1);
  //grshadeICm->SetPoint(i,hIChm->GetBinCenter(i+1), hIChm->GetBinContent(i+1));
  grshadeICm->SetPoint(i,hIChm->GetBinCenter(i+1), TMath::MaxElement(nAux,aux));
  aux[0]= hICm->GetBinContent(nn-i);
  aux[1]= hIClm->GetBinContent(nn-i);
  aux[2]= hIChm->GetBinContent(nn-i);
  //grshadeICm->SetPoint(nn+i,hIClm->GetBinCenter(nn-i), hIClm->GetBinContent(nn-i));
  grshadeICm->SetPoint(nn+i,hIClm->GetBinCenter(nn-i),TMath::MinElement(nAux,aux));
}

nn=htotChm->GetNbinsX();
grshadetotCm = new TGraph(2*nn);
for (i=0;i<nn;i++)
{
  aux[0]= htotCm->GetBinContent(i+1);
  aux[1]= htotClm->GetBinContent(i+1);
  aux[2]= htotChm->GetBinContent(i+1);
  grshadetotCm->SetPoint(i,htotChm->GetBinCenter(i+1), TMath::MaxElement(nAux,aux));
  aux[0]= htotCm->GetBinContent(nn-i);
  aux[1]= htotClm->GetBinContent(nn-i);
  aux[2]= htotChm->GetBinContent(nn-i);
  grshadetotCm->SetPoint(nn+i,htotClm->GetBinCenter(nn-i),TMath::MinElement(nAux,aux));
}

grshadetotCm->SetFillStyle(3013);
grshadetotCm->SetFillColor(kRed);

grshadeNaCm->SetFillStyle(3013);
grshadeNaCm->SetFillColor(kRed);
grshadeICm->SetFillStyle(3013);
grshadeICm->SetFillColor(kRed);

grshadetotCm->Draw("f");
//grshadeNaCm->Draw("f");
//grshadeICm->Draw("f");


TLegend * leg = new TLegend(0.55,0.7,0.9,0.9);
//leg->AddEntry(hNaS,"Na Q=0.3");
TH1F * haux = (TH1F*)hNaCm->Clone();
haux->SetFillStyle(3013);
haux->SetFillColor(kRed);
//leg->AddEntry(hNaC,"Na [Collar]");
//leg->AddEntry(haux,"Na [Collar]");
//leg->AddEntry(hISm,"I Q=0.1");
TH1F * haux2 = (TH1F*)hICm->Clone();
haux2->SetFillStyle(3013);
haux2->SetFillColor(kRed);
//leg->AddEntry(hIC,"I [Collar]");
//leg->AddEntry(haux2,"I [Collar]");
TH1F * hauxCm = (TH1F*)htotCm->Clone();
hauxCm->SetFillStyle(3013);
hauxCm->SetFillColor(kRed);
leg->AddEntry(hauxCm,"NaI [Collar]");
leg->AddEntry(htotSm,"NaI [Q_{Na}=0.3, Q_{I}=0.09]");
leg->Draw();
 leg->SetFillColor(kWhite);
  leg->SetTextSize(0.04);


TPaveText * pp = new TPaveText(0.7,0.55,0.90,.7,"NDC");
  pp->SetBorderSize(0);
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->Draw();
c->SaveAs(Form("modrateCollarDama_mW%d.png",(int)mass));

}
