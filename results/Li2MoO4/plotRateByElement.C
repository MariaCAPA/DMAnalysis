////////////////////////
// Example plotRateMW.C
// - Initialize a DMRate class with parameters from templates/rate.dat
//          * Detector with three elements Li Mo O
//            whose parameters are readed from  files
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Calculate the rate for 3 different wimp masses (10, 100, 1000 GeV)
//   and superpose them in a plot
void plotRateByElement(double si=1, double sd=0, double theta=0)
{
  gSystem->Load("libDMAnalysis");

  double cRefLi = 1;
  double cRefMo = 1;
  double cRefO = 1;



double ALi=7;
double AMo=100;
double AO=16;
double Atot=2*ALi+AMo+4*AO;

  // Initalize rate class
  int error;
  DMRate * rate = new DMRate();
  DMRate * rLi = new DMRate();
  DMRate * rMo = new DMRate();
  DMRate * rO = new DMRate();
  //error = rate->Initialize("rateCUPID.dat");
  error = rate->Initialize("rateSI.dat");
  error = rLi->Initialize("rateLi.dat");
  error = rMo->Initialize("rateMo.dat");
  error = rO->Initialize("rateO.dat");
  if (error<0) return;

/*
  for (int  iel=0; iel<rate->GetNElements(); iel++)
    rate->GetElement(0)->SetREF(cRef[iel]);
  rLi->GetElement(0)->SetREF(cRef[0]);
  rMo->GetElement(0)->SetREF(cRef[1]);
  rO->GetElement(0)->SetREF(cRef[2]);
*/


  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);
  DMRatePlotHandle  plothlLi (rLi);
  DMRatePlotHandle  plothlMo (rMo);
  DMRatePlotHandle  plothlO (rO);

  double MW [3] = {10,50,100}; // GeV

  ////////////////////////
  // Spin Independent
  // loop in bkg
  TCanvas * c = new TCanvas();
  TH1F * haux;
  TH1F * hrate, *hrLi, *hrMo, *hrO;
  for (int i=0; i<3; i++)
  {
    rate->SetParams(MW[i],si,sd,theta);
    rLi->SetParams(MW[i],si,sd,theta);
    rMo->SetParams(MW[i],si,sd,theta);
    rO->SetParams(MW[i],si,sd,theta);

    hrate = plothl.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrate->SetTitle(Form("rate M_{W} = %d GeV",(int)MW[i]));
    hrate->SetLineColor(i+1);
    hrate->SetLineWidth(3);

    hrLi = plothlLi.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrLi->SetTitle(Form("Li M_{W} = %d GeV",(int)MW[i]));
    hrLi->SetLineColor(i+1);
    hrLi->SetLineStyle(10);

    hrMo = plothlMo.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrMo->SetTitle(Form("Mo M_{W} = %d GeV",(int)MW[i]));
    hrMo->SetLineColor(i+1);
    hrMo->SetLineStyle(7);

    hrO = plothlO.GetRate(1000); // NBins between 0 and 100 keV, by default 100
    hrO->SetTitle(Form("O M_{W} = %d GeV",(int)MW[i]));
    hrO->SetLineColor(i+1);
    hrO->SetLineStyle(2);


    hrLi->Scale(2*ALi/Atot);
    hrMo->Scale(AMo/Atot);
    hrO->Scale(4*AO/Atot);

    if (i==0) 
    {
      haux = (TH1F*)hrate->DrawClone("c");
      //haux = (TH1F*)hrMo->DrawClone("c");
    }
    else 
    {
      hrate->DrawClone("csame");
      //hrMo->DrawClone("csame");
    }
    hrLi->DrawClone("csame");
    hrMo->DrawClone("csame");
    hrO->DrawClone("csame");
  }
  // change axis here
  haux->GetXaxis()->SetRangeUser(0,30);
  c->BuildLegend();

  c->SetLogy();
  //c->SaveAs("plotRateMW.jpg");

}
