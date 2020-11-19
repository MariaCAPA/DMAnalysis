////////////////////////
// Example plotRateREF.C
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
  DMRate * rate = new DMRate();
  error = rate->Initialize("$DMANALYSIS/templates/rate.dat");
  if (error<0) return;

  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);

  double refNa [3] = {0.3, 0.33, 0.25};
  double refI [3] = {0.09, 0.11, 0.07};

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TCanvas * c = new TCanvas();
  TH1F * haux;
  TH1F * hrate;
  for (int i=0; i<3; i++)
  {
    rate->GetElement(0)->SetREF(refNa[i]);
    rate->GetElement(1)->SetREF(refI[i]);

    hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrate->SetTitle(Form("Q_{I} = %0.2f, Q_{Na} = %0.2f",refI[i], refNa[i]));
    hrate->SetLineColor(i+1);
    if (i==0) 
    {
      haux = (TH1F*)hrate->DrawClone("c");
    }
    else 
    {
      hrate->SetLineStyle(2);
      hrate->DrawClone("csame");
    }
  }
  // change axis here
  haux->GetXaxis()->SetRangeUser(0,10);
  c->BuildLegend();

}
