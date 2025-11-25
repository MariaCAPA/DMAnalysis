compSen(double ei=2., double ef=4., double bkg=1.)
{
  int i,error;
  DMSensitivity * sensitivity = new DMSensitivity();
  error = sensitivity->Initialize("sensitivity.dat");
  if (error<0) return;


  sensitivity->SetWindow(ei,ef);
  sensitivity->SetLinearBkg(bkg);

  DMSensitivityPlotHandle  plothl (sensitivity);

  DMRate * theRate = sensitivity->GetTheoRate();

  TCanvas * c = new TCanvas();
  c->SetLogx();
  c->SetLogy();

  // SET BKG, EXPOSURE AND THRESHOLD
  //sensitivity->SetThreshold(2); // in keV
  // 1 year * 250 kg with duty cycle 70% = 365*250*0.7=6.39e4
  //sensitivity->SetExposure(6.39e4); // in kg*day
  //sensitivity->SetLinearBkg(bkg[i]); // in c/keVee/kg/d

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


  ////////////////////////
  // Spin Independent
  // loop in bkg
  TGraph * gSI;
  TLegend * leg = new TLegend (0.7,0.8,0.99,0.99);


  // CTE QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(0.3);
  theRate->GetElement(1)->SetREF(0.1);
  gSI = plothl.GetSISensitivity();
  gSI->SetLineColor(kBlack);
  gSI->SetTitle(Form("Q_{Na}=0.3 Q_{I}=0.1"));
  TGraph * gaxis = (TGraph*)gSI->DrawClone("ac");
  leg->AddEntry(gaxis,gaxis->GetTitle());

  // TRETYAK QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gQNaT);
  theRate->GetElement(1)->SetREF(gQIT);
  gSI = plothl.GetSISensitivity();
  gSI->SetLineColor(kGreen-2);
  gSI->SetTitle(Form("Tretyak"));
  (TGraph*)gSI->DrawClone("c");
  leg->AddEntry(gSI,gSI->GetTitle());

  // COLLAR QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQIC);
  gSI = plothl.GetSISensitivity();
  gSI->SetLineColor(kRed-2);
  gSI->SetTitle(Form("Collar"));
  (TGraph*)gSI->DrawClone("c");
  gSI->SetFillStyle(3013);
  gSI->SetFillColor(kRed-2);
  leg->AddEntry(gSI,gSI->GetTitle());

  // GET ENVELOPE SHADE GRAPH
  int nEnvC = 9;
  int j=0;
  TGraph ** gEnvC = new TGraph* [nEnvC];

  theRate->GetElement(0)->SetREF(gQNaCh);
  theRate->GetElement(1)->SetREF(gQICh);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaCh);
  theRate->GetElement(1)->SetREF(gQIC);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaCh);
  theRate->GetElement(1)->SetREF(gQICl);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQICh);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQIC);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQICl);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaCl);
  theRate->GetElement(1)->SetREF(gQICh);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaCl);
  theRate->GetElement(1)->SetREF(gQIC);
  gEnvC[j++] = plothl.GetSISensitivity();

  theRate->GetElement(0)->SetREF(gQNaCl);
  theRate->GetElement(1)->SetREF(gQICl);
  gEnvC[j++] = plothl.GetSISensitivity();
  //gSI->SetLineColor(2);
  //gSI->SetTitle(Form("Collarl"));
  //(TGraph*)gSI->DrawClone("c");

  // MMAKE ENVELOPE
  double * aux = new double[nEnvC];
  int n = gSI->GetN();
  TGraph *grshadeC = new TGraph(2*n);
  for (i=0;i<n;i++)
  {
    for(j=0;j<nEnvC;j++) aux[j] = gEnvC[j]->GetY()[i];
    grshadeC->SetPoint(i,gSI->GetX()[i],TMath::MaxElement(nEnvC,aux));
    for(j=0;j<nEnvC;j++) aux[j] = gEnvC[j]->GetY()[n-i-1];
    grshadeC->SetPoint(n+i,gSI->GetX()[n-i-1],TMath::MinElement(nEnvC,aux));
  }
  grshadeC->SetFillStyle(3013);
  grshadeC->SetFillColor(kRed-2);
  grshadeC->Draw("f");
  
 // for(j=0;j<nEnvC;j++) gEnvC[j]->Draw("c");



  // CHANGE AXIS HERE
  gaxis->GetYaxis()->SetRangeUser(1e-8, 1e-1);
  gaxis->GetXaxis()->SetLimits(1,1e3);
//  TLegend * leg = c->BuildLegend();
  leg->SetFillColor(kWhite);
  leg->SetTextSize(0.05);
  leg->Draw();


  TPaveText * pp = new TPaveText(100,5e-8,1000,5e-7);
  pp->AddText("Bkg: 1 c/keV/kg/d");
  pp->Draw();
  pp->AddText(Form("Energy window: %0.1f-%0.1f keV",ei,ef));
  pp->SetFillColor(kWhite);

  /////////////////
  /////////////////
  /////////////////
  /////////////////
  /////////////////
  /////////////////
  // SD
  c = new TCanvas();
  c->SetLogx();
  c->SetLogy();

  TGraph * gSD=0;
  leg = new TLegend (0.7,0.8,0.99,0.99);

  // CTE QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gSD); // Important!! PUT TO TGraph* = 0
  theRate->GetElement(0)->SetREF(0.3);
  theRate->GetElement(1)->SetREF(gSD);
  theRate->GetElement(1)->SetREF(0.1);
  gSD = plothl.GetSDSensitivity();
  gSD->SetLineColor(kBlack);
  gSD->SetTitle(Form("Q_{Na}=0.3 Q_{I}=0.1"));
  gaxis = (TGraph*)gSD->DrawClone("ac");
  leg->AddEntry(gaxis,gaxis->GetTitle());

  // TRETYAK QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gQNaT);
  theRate->GetElement(1)->SetREF(gQIT);
  gSD = plothl.GetSDSensitivity();
  gSD->SetLineColor(kGreen-2);
  gSD->SetTitle(Form("Tretyak"));
  (TGraph*)gSD->DrawClone("c");
  leg->AddEntry(gSD,gSD->GetTitle());

  // COLLAR QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQIC);
  gSD = plothl.GetSDSensitivity();
  gSD->SetLineColor(kRed-2);
  gSD->SetTitle(Form("Collar"));
  (TGraph*)gSD->DrawClone("c");
  gSD->SetFillStyle(3013);
  gSD->SetFillColor(kRed-2);
  leg->AddEntry(gSD,gSD->GetTitle());

  // GET ENVELOPE SHADE GRAPH
  nEnvC = 9;
  j=0;
  gEnvC = new TGraph* [nEnvC];

  theRate->GetElement(0)->SetREF(gQNaCh);
  theRate->GetElement(1)->SetREF(gQICh);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaCh);
  theRate->GetElement(1)->SetREF(gQIC);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaCh);
  theRate->GetElement(1)->SetREF(gQICl);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQICh);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQIC);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQICl);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaCl);
  theRate->GetElement(1)->SetREF(gQICh);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaCl);
  theRate->GetElement(1)->SetREF(gQIC);
  gEnvC[j++] = plothl.GetSDSensitivity();

  theRate->GetElement(0)->SetREF(gQNaCl);
  theRate->GetElement(1)->SetREF(gQICl);
  gEnvC[j++] = plothl.GetSDSensitivity();
  //gSD->SetLineColor(2);
  //gSD->SetTitle(Form("Collarl"));
  //(TGraph*)gSD->DrawClone("c");

  // MMAKE ENVELOPE
  aux = new double[nEnvC];
  n = gSD->GetN();
  TGraph *grshadeCSD = new TGraph(2*n);
  for (i=0;i<n;i++)
  {
    for(j=0;j<nEnvC;j++) aux[j] = gEnvC[j]->GetY()[i];
    grshadeCSD->SetPoint(i,gSD->GetX()[i],TMath::MaxElement(nEnvC,aux));
    for(j=0;j<nEnvC;j++) aux[j] = gEnvC[j]->GetY()[n-i-1];
    grshadeCSD->SetPoint(n+i,gSD->GetX()[n-i-1],TMath::MinElement(nEnvC,aux));
  }
  grshadeCSD->SetFillStyle(3013);
  grshadeCSD->SetFillColor(kRed-2);
  grshadeCSD->Draw("f");
  
 // for(j=0;j<nEnvC;j++) gEnvC[j]->Draw("c");



  // CHANGE AXIS HERE
  gaxis->GetYaxis()->SetRangeUser(1e-2, 1e3);
  gaxis->GetXaxis()->SetLimits(1,1e3);
//  TLegend * leg = c->BuildLegend()3
  leg->SetFillColor(kWhite);
  leg->SetTextSize(0.05);
  leg->Draw();

  TPaveText * pp = new TPaveText(100,5e-2,1000,5e-1);
  pp->AddText(Form("Bkg: %1g c/keV/kg/d",bkg));
  pp->Draw();
  pp->AddText(Form("Energy window: %0.1f-%0.1f keV",ei,ef));
  pp->SetFillColor(kWhite);



/*

  // COLLAR QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gQNaC);
  theRate->GetElement(1)->SetREF(gQIC);
  gSD = plothl.GetSDSensitivity();
  gSD->SetLineColor(2);
  gSD->SetTitle(Form("Collar"));
  (TGraph*)gSD->DrawClone("c");
  // TRETYAK QUENCHING FACTORS
  theRate->GetElement(0)->SetREF(gQNaT);
  theRate->GetElement(1)->SetREF(gQIT);
  gSD = plothl.GetSDSensitivity();
  gSD->SetLineColor(3);
  gSD->SetTitle(Form("Tretyak"));
  (TGraph*)gSD->DrawClone("c");

  // CHANGE AXIS HERE
  gaxis->GetYaxis()->SetRangeUser(1e-2, 10);
  gaxis->GetXaxis()->SetLimits(1,1e3);
  leg = c->BuildLegend();
  leg->SetFillColor(kWhite);
  leg->SetTextSize(0.05);


*/
}
