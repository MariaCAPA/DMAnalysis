void compRate(double si=1e-4, double mass=100)
{

  gSystem->Load("libDMAnalysis");

//double si=1e-4;
//double mass = 10;
// RATE BINNING
double emin=0;
double emax=100;
int nbins = 200;


int i;

  //////////////////////
  // QUENCHING FACTORS
  // Open file with q factors
  TFile * f = new TFile ("$DMANALYSIS/templates/quenchingLuxLindhard_k0.11.root","read");
  if (!f) {std::cout << " CANNOT READ QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  TGraph * gQXe=(TGraph*)f->Get("gQXe_ee");
  if (!gQXe) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

DMRate * rXe = new DMRate();
DMRate * rXeq1 = new DMRate();
DMRate * rTeO2 = new DMRate();

rXe->Initialize((char*)"rateXe.dat");
rXe->GetElement(0)->SetREF(gQXe);
rXeq1->Initialize((char*)"rateXe.dat");
rXeq1->GetElement(0)->SetREF(1);
rTeO2->Initialize((char*)"rateTeO2.dat");

rXe->SetSigSI(si);
rXe->SetMW(mass);
rXeq1->SetSigSI(si);
rXeq1->SetMW(mass);

rTeO2->SetSigSI(si);
rTeO2->SetMW(mass);

DMRatePlotHandle plXe (rXe);
DMRatePlotHandle plXeq1 (rXeq1);
DMRatePlotHandle plTeO2 (rTeO2);

TH1F * hXe = plXe.GetRate(nbins,emin,emax);
TH1F * hXem = plXe.GetModulatedRate(nbins,emin,emax);
TH1F * hXeq1 = plXeq1.GetRate(nbins,emin,emax);
TH1F * hXeq1m = plXeq1.GetModulatedRate(nbins,emin,emax);

TH1F * hTeO2 = plTeO2.GetRate(nbins,emin,emax);
TH1F * hTeO2m = plTeO2.GetModulatedRate(nbins,emin,emax);

////////////////////////
// PLOT
hXe->SetLineColor(kRed-2);
hXe->SetLineWidth(3);
hXeq1->SetLineColor(kRed-2);
hXeq1->SetLineWidth(3);

hTeO2->SetLineColor(kBlue-2);
hTeO2->SetLineWidth(3);

TCanvas * c = new TCanvas();
c->SetLogy();

hXe->Draw("l");
hTeO2->Draw("lsame");

TLegend * leg = new TLegend(0.6,0.9,0.99,0.99);
leg->AddEntry(hXe,"Xe (Q Lindhart k=0.11)");
leg->AddEntry(hTeO2,"TeO_{2} bolometer (Q=1)");

leg->Draw();
leg->SetFillColor(kWhite);
leg->SetTextSize(0.04);

pp = new TPaveText(0.01,0.92,0.2,.99,"NDC");
pp->AddText(Form("M_{W}= %0.0f GeV",mass));
pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
pp->SetFillColor(kWhite);
pp->Draw();

c = new TCanvas();
c->SetLogy();

hXeq1->Draw("l");
hXeq1->GetXaxis()->SetTitle("E_{NR}");
hTeO2->Draw("lsame");

leg = new TLegend(0.6,0.9,0.99,0.99);
leg->AddEntry(hXeq1,"Xe");
leg->AddEntry(hTeO2,"TeO_{2}");

leg->Draw();
leg->SetFillColor(kWhite);
leg->SetTextSize(0.04);

pp = new TPaveText(0.01,0.92,0.2,.99,"NDC");
pp->AddText(Form("M_{W}= %0.0f GeV",mass));
pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
pp->SetFillColor(kWhite);
pp->Draw();

////////////////////////
// PLOT modulated rate
hXem->SetLineColor(kRed-2);
hXem->SetLineWidth(3);
hXeq1m->SetLineColor(kRed-2);
hXeq1m->SetLineWidth(3);

hTeO2m->SetLineColor(kBlue-2);
hTeO2m->SetLineWidth(3);

c = new TCanvas();

hXem->Draw("l");
hTeO2m->Draw("lsame");

//hXem->GetXaxis()->SetRangeUser(0,6);
//hXem->GetYaxis()->SetRangeUser(-0.15,0.25);


leg = new TLegend(0.6,0.9,0.99,0.99);
leg->AddEntry(hXem,"Xe (Q Lindhardt k=0.11)");
leg->AddEntry(hTeO2m,"TeO_{2} bolometer (Q=1)");

leg->Draw();
leg->SetFillColor(kWhite);
leg->SetTextSize(0.04);


 pp = new TPaveText(0.01,0.92,0.2,.99,"NDC");
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->Draw();

c = new TCanvas();

hXeq1m->Draw("l");
hXeq1m->GetXaxis()->SetTitle("E_{NR}");
hTeO2m->Draw("lsame");

//hXem->GetXaxis()->SetRangeUser(0,6);
//hXem->GetYaxis()->SetRangeUser(-0.15,0.25);


leg = new TLegend(0.6,0.9,0.99,0.99);
leg->AddEntry(hXeq1m,"Xe");
leg->AddEntry(hTeO2m,"TeO_{2}");

leg->Draw();
leg->SetFillColor(kWhite);
leg->SetTextSize(0.04);


 pp = new TPaveText(0.01,0.92,0.2,.99,"NDC");
  pp->AddText(Form("M_{W}= %0.0f GeV",mass));
  pp->AddText(Form("#sigma_{SI} = %0.0e pb",si));
  pp->SetFillColor(kWhite);
  pp->Draw();
}
