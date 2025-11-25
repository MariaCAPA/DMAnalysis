////////////////////////
// - Initialize a DMRate class with parameters from templates/rate.dat
//          * Detector with two elements Na, I 
//            whose parameters are readed from templates/Na.dat, templates/I.dat 
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Calculate the rate for 3 different set of the quenching factors
//   and superpose them in a plot

{
  gSystem->Load("libDMAnalysis");
  // Initalize rate class
  int error;
  DMRate * theRate = new DMRate();
  error = theRate->Initialize("rateANAIS.dat");
  if (error<0) return;

  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TCanvas * c = new TCanvas();
  TH1F * hrate;

   /////////////////////
  // QUENCHING FACTORS
  // Open file with q factors
  TFile * f = new TFile ("QFTamara.root","READ");
  if (!f) {std::cout << " CANNOT READ QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  TGraph * gQNa=(TGraph*)f->Get("gNa");
  if (!gQNa) {std::cout << " CANNOT FIND gNa IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}
  TGraph * gQI=(TGraph*)f->Get("gI");
  if (!gQI) {std::cout << " CANNOT FIND gI IN QUENCHING FACTOR FILE!!" << std::endl; exit(0);}

  theRate->GetElement(0)->SetREF(gQNa);
  theRate->GetElement(1)->SetREF(gQI);
  hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
  hrate->SetLineStyle(2);
  hrate->SetTitle(Form("QF Tamara"));



  rate->GetElement(0)->SetREF(0.3);
  rate->GetElement(1)->SetREF(0.09);
  hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
  hrate->SetTitle(Form("Q_{I} = %0.2f, Q_{Na} = %0.2f",0.09, 0.3));
  hrate->SetLineColor(2);
  hrate->SetLineStyle(2);
  hrate->Draw("csame");

  c->BuildLegend();

}
