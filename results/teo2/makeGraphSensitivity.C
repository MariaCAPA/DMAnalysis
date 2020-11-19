// CUORE: 741 kg * 5 years = 3705;
makeGraphSensitivity(double exposure_kgy = 3705)
{
  gSystem->Load("libDMAnalysis");

  double exposure = 365*exposure_kgy;
 int error;

///////////////////////////////////
// SENSITIVITY
//////////////////////////////////
 // BOLOMETER


  DMSensitivity * senBOLO = new DMSensitivity();
  error = senBOLO->Initialize("sensitivityBolo.dat");
  if (error<0) return;

  senBOLO->SetThreshold(5); // in keV // PARA EVITAR EL PICO EN UN PRIMER TEST
  // 1 year * 250 kg with duty cycle 70% = 365*250*0.7=6.39e4
  senBOLO->SetExposure(exposure); // in kg*day

  // FOR A FRIST TEST
  senBOLO->SetLinearBkg(3); // in c/keVee/kg/d


  DMSensitivityPlotHandle  plothlB (senBOLO);

   // DUMP bolo data
  plothlB.Dump("sensitivityOutput_3.dat",5,1000);


  TTree * ts2 = new TTree("ts2","");
  ts2->ReadFile("sensitivityOutput_3.dat");
  ts2->Draw("SI*1e-36:MW","","goff"); // in cm2
  //TGraph * gs2 = new TGraph(ts2->GetSelectedRows(), ts2->GetV2(), ts2->GetV1());
  // Do not include points with 0 si
  TGraph * gs2 = new TGraph();
  int cont=0;
  for (int ii=0; ii<ts2->GetSelectedRows(); ii++)
  {
    if (ts2->GetV1()[ii]>0) gs2->SetPoint(cont++,ts2->GetV2()[ii],ts2->GetV1()[ii]);
  }


  c = new TCanvas("c","SI",1500,850);
  //TH1 * frame = gPad->DrawFrame(5,1e-43,50,1e-39);
  gPad->SetLogx(1);
  gPad->SetLogy(1);

  double mWm = 5;
  double mWM = 1000;

  gs2->Draw("al");
  gs2->GetXaxis()->SetRangeUser(mWm,mWM);
  gs2->GetYaxis()->SetRangeUser(1e-43,1e-39);
  gs2->SetLineColor(kRed+2);
  gs2->SetFillColor(kWhite);
  gs2->SetLineWidth(6);

  gs2->GetXaxis()->SetTitle("M_{WIMP} (GeV)");
  gs2->GetYaxis()->SetTitle("#sigma_{SI} (cm^{2})");

  TLegend * l = new TLegend(0.7,0.8,0.80,0.88);
  l->AddEntry(gs2,"CUORE");
  l->SetFillColor(kWhite);
  l->Draw();

  TGaxis * ax = new TGaxis(mWM,1e-43,mWM,1e-39,1e-7,1e-3,510,"G-=");
  ax->SetTitle("#sigma_{SI} (pb)");
  ax->SetTitleOffset(1);
  ax->Draw();
  ax->SetLabelSize(0.06);
  ax->SetLabelFont(42);
  ax->SetLabelOffset(0.04);
  ax->SetTitleSize(0.06);
  ax->SetTitleFont(42);
  ax->SetTitleOffset(1.4);


}
