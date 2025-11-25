TGraph * grshadeNaC;
TGraph * grshadeNaI;
compRate(double si=1e-4, double mass=10)
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



DMRate * rtotC = new DMRate();
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
// init REFS variable with E
rNaC->GetElement(0)->SetREF(gQNaC);
rNaCl->GetElement(0)->SetREF(gQNaCl);
rNaCh->GetElement(0)->SetREF(gQNaCh);
rIC->GetElement(0)->SetREF(gQIC);
rICl->GetElement(0)->SetREF(gQICl);
rICh->GetElement(0)->SetREF(gQICh);
rtotC->GetElement(0)->SetREF(gQNaC);
rtotC->GetElement(1)->SetREF(gQIC);

rtotC->SetSigSI(si);
rNaC->SetSigSI(si);
rNaCl->SetSigSI(si);
rNaCh->SetSigSI(si);
rIC->SetSigSI(si);
rICl->SetSigSI(si);
rICh->SetSigSI(si);
rtotC->SetMW(mass);
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

// TRETYAK
DMRate * rbtotT = new DMRate();
DMRate * rNaT = new DMRate();
DMRate * rIT = new DMRate();
rNaT->Initialize("rateNa.dat");
rIT->Initialize("rateI.dat");
rbtotT->Initialize("rate.dat");
// init REFS variable with E

rNaT->GetElement(0)->SetREF(gQNaT);
rIT->GetElement(0)->SetREF(gQIT);
rbtotT->GetElement(0)->SetREF(gQNaT);
rbtotT->GetElement(1)->SetREF(gQIT);

rbtotT->SetSigSI(si);
rNaT->SetSigSI(si);
rIT->SetSigSI(si);
rbtotT->SetMW(mass);
rNaT->SetMW(mass);
rIT->SetMW(mass);

DMRatePlotHandle plNaT (rNaT);
DMRatePlotHandle plIT (rIT);
DMRatePlotHandle pltotT (rbtotT);

TH1F * hNaT = plNaT.GetRate(nbins,emin,emax);
TH1F * hNaTm = plNaT.GetModulatedRate(nbins,emin,emax);
TH1F * hIT = plIT.GetRate(nbins,emin,emax);
TH1F * hITm = plIT.GetModulatedRate(nbins,emin,emax);
TH1F * htotT = pltotT.GetRate(nbins,emin,emax);

hIT->Scale(AI/Atot);
hNaT->Scale(ANa/Atot);
hITm->Scale(AI/Atot);
hNaTm->Scale(ANa/Atot);



// STD
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
hNaC->SetLineColor(kRed-2);
hNaCl->SetLineColor(kRed-2);
hNaCh->SetLineColor(kRed-2);
hIC->SetLineColor(kRed-2);
hICl->SetLineColor(kRed-2);
hICh->SetLineColor(kRed-2);

hNaT->SetLineColor(kGreen-2);
hIT->SetLineColor(kGreen-2);

hNaS->SetLineColor(kBlack);
hIS->SetLineColor(kBlack);

hNaC->SetLineWidth(3);
hIC->SetLineWidth(3);
hNaT->SetLineWidth(3);
hIT->SetLineWidth(3);
hNaS->SetLineWidth(3);
hIS->SetLineWidth(3);

hNaCl->SetLineWidth(1);
hNaCh->SetLineWidth(1);
hICl->SetLineWidth(1);
hICh->SetLineWidth(1);

hIC->SetLineStyle(9);
hICl->SetLineStyle(9);
hICh->SetLineStyle(9);
hIT->SetLineStyle(9);
hIS->SetLineStyle(9);

TCanvas * c = new TCanvas();
c->SetLogy();

//htotC->Draw("l");
//htotT->Draw("lsame");

hIC->Draw("l");
hICl->Draw("lsame");
hICh->Draw("lsame");
hNaC->Draw("lsame");
hNaCl->Draw("lsame");
hNaCh->Draw("lsame");
hNaT->Draw("lsame");
hIT->Draw("lsame");
hNaS->Draw("lsame");
hIS->Draw("lsame");
hIC->GetXaxis()->SetRangeUser(0,6);
hIC->GetYaxis()->SetRangeUser(1e-7,100);

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
grshadeNaC->SetFillStyle(3013);
grshadeNaC->SetFillColor(kRed-2);
grshadeIC->SetFillStyle(3013);
grshadeIC->SetFillColor(kRed-2);
grshadeNaC->Draw("f");
grshadeIC->Draw("f");


TLegend * leg = new TLegend(0.75,0.7,0.99,0.99);
leg->AddEntry(hNaS,"Na Q=0.3");
TH1F * haux = (TH1F*)hNaC->Clone();
haux->SetFillStyle(3013);
haux->SetFillColor(kRed-2);
//leg->AddEntry(hNaC,"Na [Collar]");
leg->AddEntry(haux,"Na [Collar]");
leg->AddEntry(hNaT,"Na [Tretyak]");
leg->AddEntry(hIS,"I Q=0.1");
TH1F * haux2 = (TH1F*)hIC->Clone();
haux2->SetFillStyle(3013);
haux2->SetFillColor(kRed-2);
//leg->AddEntry(hIC,"I [Collar]");
leg->AddEntry(haux2,"I [Collar]");
leg->AddEntry(hIT,"I [Tretyak]");
leg->Draw();
 leg->SetFillColor(kWhite);
  leg->SetTextSize(0.04);


 TPaveText * pp = new TPaveText(0.25,0.88,0.5,.99,"NDC");
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->Draw();

////////////////////////
// PLOT modulated rate
hNaCm->SetLineColor(kRed-2);
hNaClm->SetLineColor(kRed-2);
hNaChm->SetLineColor(kRed-2);
hICm->SetLineColor(kRed-2);
hIClm->SetLineColor(kRed-2);
hIChm->SetLineColor(kRed-2);

hNaTm->SetLineColor(kGreen-2);
hITm->SetLineColor(kGreen-2);

hNaSm->SetLineColor(kBlack);
hISm->SetLineColor(kBlack);

hNaCm->SetLineWidth(3);
hICm->SetLineWidth(3);
hNaTm->SetLineWidth(3);
hITm->SetLineWidth(3);
hNaSm->SetLineWidth(3);
hISm->SetLineWidth(3);

hNaClm->SetLineWidth(1);
hNaChm->SetLineWidth(1);
hIClm->SetLineWidth(1);
hIChm->SetLineWidth(1);

hICm->SetLineStyle(9);
hIClm->SetLineStyle(9);
hIChm->SetLineStyle(9);
hITm->SetLineStyle(9);
hISm->SetLineStyle(9);

TCanvas * c = new TCanvas();

//htotC->Draw("l");
//htotT->Draw("lsame");

hICm->Draw("l");
hIClm->Draw("lsame");
hIChm->Draw("lsame");
hNaCm->Draw("lsame");
hNaClm->Draw("lsame");
hNaChm->Draw("lsame");
hNaTm->Draw("lsame");
hITm->Draw("lsame");
hNaSm->Draw("lsame");
hISm->Draw("lsame");
hICm->GetXaxis()->SetRangeUser(0,6);
hICm->GetYaxis()->SetRangeUser(-0.15,0.25);

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
grshadeNaCm->SetFillStyle(3013);
grshadeNaCm->SetFillColor(kRed-2);
grshadeICm->SetFillStyle(3013);
grshadeICm->SetFillColor(kRed-2);
grshadeNaCm->Draw("f");
grshadeICm->Draw("f");


TLegend * leg = new TLegend(0.75,0.7,0.99,0.99);
leg->AddEntry(hNaS,"Na Q=0.3");
TH1F * haux = (TH1F*)hNaCm->Clone();
haux->SetFillStyle(3013);
haux->SetFillColor(kRed-2);
//leg->AddEntry(hNaC,"Na [Collar]");
leg->AddEntry(haux,"Na [Collar]");
leg->AddEntry(hNaTm,"Na [Tretyak]");
leg->AddEntry(hISm,"I Q=0.1");
TH1F * haux2 = (TH1F*)hICm->Clone();
haux2->SetFillStyle(3013);
haux2->SetFillColor(kRed-2);
//leg->AddEntry(hIC,"I [Collar]");
leg->AddEntry(haux2,"I [Collar]");
leg->AddEntry(hITm,"I [Tretyak]");
leg->Draw();
 leg->SetFillColor(kWhite);
  leg->SetTextSize(0.04);


 TPaveText * pp = new TPaveText(0.25,0.88,0.5,.99,"NDC");
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->Draw();

}
