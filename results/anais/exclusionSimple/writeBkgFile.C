{
TFile * f = new TFile("BEhistos_year123456.root","READ");
TH1F * h = (TH1F*)f->Get("hbea_123456y");
fstream fq ("ANAIS112.bkg",ios::out);
for (int i=0; i<60; i++) fq << h->GetBinContent(i+1) << std::endl;
fq.close();
}
