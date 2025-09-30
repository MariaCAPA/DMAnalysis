////////////////////////
// Example plotRateMW.C
// - Initialize a DMRate class with parameters from templates/rate.dat
//          * Detector with two elements Na, I 
//            whose parameters are readed from templates/Na.dat, templates/I.dat 
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Calculate the rate for 3 different wimp masses (10, 100, 1000 GeV)
//   and superpose them in a plot
{
   gSystem->Load("libDMAnalysis");
  double cRefNa = 1;
  double cRefI = 1;
  double si = 1e-5;



  double ANa=23;
double AI=127;
double Atot=ANa+AI;

  // Initalize rate class
  int error;
  DMRate * rate = new DMRate();
  DMRate * rNa = new DMRate();
  DMRate * rI = new DMRate();
  error = rate->Initialize("$DMANALYSIS/templates/rate.dat");
  error = rNa->Initialize("rateNa.dat");
  error = rI->Initialize("rateI.dat");
  if (error<0) return;

  rate->GetElement(0)->SetREF(cRefNa);
  rNa->GetElement(0)->SetREF(cRefNa);
  rate->GetElement(1)->SetREF(cRefI);
  rI->GetElement(0)->SetREF(cRefI);
  rate->SetSigSI(si);
  rNa->SetSigSI(si);
  rI->SetSigSI(si);

  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);
  DMRatePlotHandle  plothlNa (rNa);
  DMRatePlotHandle  plothlI (rI);

  double MW [3] = {10,50,100}; // GeV

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TCanvas * c = new TCanvas();
  TH1F * haux;
  TH1F * hrate;
  for (int i=0; i<3; i++)
  {
    rate->SetMW(MW[i]);
    rNa->SetMW(MW[i]);
    rI->SetMW(MW[i]);

    TH1F * hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrate->SetTitle(Form("M_{W} = %d GeV",(int)MW[i]));
    hrate->SetLineColor(i+1);
    TH1F * hrNa = plothlNa.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrNa->SetTitle(Form("Na M_{W} = %d GeV",(int)MW[i]));
    hrNa->SetLineColor(i+1);
    TH1F * hrI = plothlI.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrI->SetTitle(Form("I M_{W} = %d GeV",(int)MW[i]));
    hrI->SetLineColor(i+1);
    hrI->SetLineStyle(9);


    hrNa->Scale(ANa/Atot);
    hrI->Scale(AI/Atot);

    if (i==0) 
    {
      //haux = (TH1F*)hrate->DrawClone("chist");
      haux = (TH1F*)hrI->DrawClone("chist");
    }
    else 
    {
      //hrate->DrawClone("chistsame");
      hrI->DrawClone("chistsame");
    }
    hrNa->DrawClone("chistsame");
  }
  // change axis here
  haux->GetXaxis()->SetRangeUser(0,30);
  c->BuildLegend();

  //c->SaveAs("plotRateMW.jpg");

}
