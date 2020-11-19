////////////////////////
// Example plotExclusion.C
// - Initialize a DMExclusion class with parameters from templates/exclusion.dat
//       * Initialize detector & and halo parameters from templates/rate.dat:
//              - Detector with two elements Na, I 
//                 whose parameters are readed from templates/Na.dat, templates/I.dat 
//              - Isothermal halo model. Paramteres read from templates/iso.dat
//       * Initialize exposure, CL, Bkg(lineal), energy window
// - Change some of this parameters (threshold, exposure)
// - Calculate the exclusion (SI & SD) curve for 4 different values of the (lineal) bkg and 
//   superpose them in a plot
{
   gSystem->Load("libDMAnalysis");
  int error;
  DMExclusion * exclusion = new DMExclusion();
  error = exclusion->Initialize("$DMANALYSIS/templates/exclusion.dat");
  if (error<0) return;


  DMExclusionPlotHandle  plothl (exclusion);

  TCanvas * c = new TCanvas();
  c->SetLogx();
  c->SetLogy();

  // SET BKG, EXPOSURE AND THRESHOLD
  exclusion->SetThreshold(2); // in keV

  // 1 year * 250 kg with duty cycle 70% = 365*250*0.7=6.39e4
  //exclusion->SetExposure(6.39e4); // in kg*day
  exclusion->SetExposure(107*5*365); // in kg*day

  TGraph *gaux;
  //double bkg [4] = {1,0.5,0.1,0.01};
  double bkg [4] = {2,1,0.5,0.1};

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TGraph * gSI;
  for (int i=0; i<4; i++)
  {
    exclusion->SetLinearBkg(bkg[i]); // in c/keVee/kg/d
    gSI = plothl.GetSIExclusion(1,1e3); // from 1 GeV to 1 TeV
    gSI->SetLineColor(i+1);
    gSI->SetTitle(Form("%0.2f c/keV/kg/d",bkg[i]));
    if (i==0) gaux = (TGraph*)gSI->DrawClone("ac");
    else gSI->DrawClone("c");
  }

  // CHANGE AXIS HERE
  //gaux->GetYaxis()->SetLimits(1e-15, 1);
  //gaux->GetYaxis()->SetRangeUser(1e-8, 1);
  c->BuildLegend();


  /////////////////
  // SD proton
  c = new TCanvas();
  c->SetLogx();
  c->SetLogy();

  TGraph * gSD;

  for (int i=0; i<4; i++)
  {
    exclusion->SetLinearBkg(bkg[i]); // in c/keVee/kg/d
    gSD = plothl.GetSDpExclusion(1,1e3); // from 1 GeV to 1 TeV
    gSD->SetLineColor(i+1);
    gSD->SetTitle(Form("%0.2f c/keV/kg/d",bkg[i]));
    if (i==0) gaux = (TGraph*)gSD->DrawClone("ac");
    else gSD->DrawClone("c");
  }

  // CHANGE AXIS HERE
  //gaux->GetYaxis()->SetLimits(1e-15, 1e6);
  //gaux->GetYaxis()->SetRangeUser(1e-8, 1e6);
  c->BuildLegend();


}
