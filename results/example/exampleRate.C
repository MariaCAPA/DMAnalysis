////////////////////////
// Example plotRateMW.C
// - Initialize a DMRate class with parameters from templates/rate.dat
//          * Detector with two elements Na, I 
//            whose parameters are readed from templates/Na.dat, templates/I.dat 
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Calculate the rate for 3 different wimp masses (10, 100, 1000 GeV)
//   and superpose them in a plot
{
  double si = 1e-45; // cm2
 std::cout << " cross section " << si << " cm2 ";
  double pb2cm=1e-36;
  si/=pb2cm;
 std::cout << si << " pbarn" << std::endl;


/*

  double cRefNa = 1;
  double cRefI = 1;
  double ANa=23;
double AI=127;
double Atot=ANa+AI;
*/

  // Initalize rate class
  int error;
  DMRate * rate = new DMRate();

  error = rate->Initialize((char*)("exampleRate.dat"));
  if (error<0) return;

  //rate->GetElement(0)->SetREF(cRefNa);
  //rate->GetElement(1)->SetREF(cRefI);
  rate->SetSigSI(1); // to comute sigma

  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);

  std::vector<double>MW={30}; //{10,100,1000}; // GeV
  int nn=MW.size();

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TCanvas * c = new TCanvas();
  TH1F * hrate;
  for (int i=0; i<nn; i++)
  {
    rate->SetMW(MW[i]);

    TH1F * hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100

    // convert to c/keV/kg/y
    hrate->Scale(365);
    hrate->SetTitle(Form("M_{W} = %d GeV",(int)MW[i]));
    hrate->SetLineColor(i+1);
    hrate->GetYaxis()->SetTitle("c/keV/kg/y");
   // hrate->GetYaxis()->SetRangeUser(1e-5,1e-1);

    if (i==0) hrate->Draw("hist");
    else  hrate->Draw("hist same");
  }
  // change axis here
  c->SetLogy();
  c->BuildLegend();


}
