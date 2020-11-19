////////////////////////
{
   gSystem->Load("libDMAnalysis");
  // Initalize rate class
  int error;
  DMRate * rate = new DMRate();
  error = rate->Initialize("$DMANALYSIS/templates/rate.dat");
  if (error<0) return;

  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);

  // USUAL VALUES
  double refNa  = 0.3;
  double refI  = 0.09;

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TCanvas * c = new TCanvas();
  TH1F * haux;
  TH1F * hrate;


  rate->GetElement(0)->SetREF(refNa);
  rate->GetElement(1)->SetREF(refI);

  hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
  hrate->SetTitle(Form("Q_{I} = %0.2f, Q_{Na} = %0.2f",refI, refNa));
  hrate->SetLineColor(1);

  haux = (TH1F*)hrate->DrawClone("c");
  
  haux->GetXaxis()->SetRangeUser(0,10);



  // SECOND PLOT, WITH COLLAR Na
  TFile * f = new TFile ("$DMANALYSIS/templates/quenchingNaIee.root","read");
  if (!f) {std::cout << " CANNOT READ QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQ=(TGraph*)f->Get("gQNaCollaree");
  if (!gQ) {std::cout << " CANNOT FIND TGRAPH IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  rate->GetElement(0)->SetREF(gQ);
  rate->GetElement(1)->SetREF(refI);

  hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
  hrate->SetTitle(Form("Q_{Na} from Collar'13 arXiv:1302.0796"));
  hrate->SetLineColor(2);
  hrate->SetLineStyle(2);
  hrate->DrawClone("csame");
  c->BuildLegend();

}
