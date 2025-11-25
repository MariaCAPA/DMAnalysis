/////
// Maria 041125
// Quenchings in Tamara's thesis
// Na: Lindhard modified
// I: Linear decreasing
// RETURN QF FOR E_ee in keVee
/////
TGraph* QFNa()
{
    TF1* qf = new TF1("qf",
        [](double* x, double* p) {
            double ER = x[0];
            double epsilon = p[1] * ER;
            double g = 3.0 * pow(epsilon, 0.15) + 0.7 * pow(epsilon, 0.6) + epsilon;
            double k = p[0];
            return (k * g) / (1.0 + k * g);
        }, 1, 100, 2);
    qf->SetParameters(0.072, 0.007);
    qf->SetParNames("k", "alpha");

    const int N = 200;
    double xmin = 1.0, xmax = 100.0;
    double dx = (xmax - xmin) / (N - 1);
    std::vector<double> xvals, yvals;
    for (int i = 0; i < N; ++i) 
    {
        double ER = xmin + i * dx;
        double y = qf->Eval(ER);
        double x = ER*y;
        xvals.push_back(x);
        yvals.push_back(y);
        
    }
    TGraph* result = new TGraph(N, xvals.data(), yvals.data());
    return result;
}

double getQFNa(double ee)
{
  TGraph * g = QFNa();
  return g->Eval(ee);
}


TGraph* QFI()
{
    TF1* qf = new TF1("qf",
        [](double* x, double* p) {
            double ER = x[0];
            double p0 = p[0];
            double p1 = p[1];
            double limit = p[2];
            if (ER<=limit) return p0+p1*ER;
            return p0+p1*limit;
        }, 1, 100, 3);
    qf->SetParameters(0.03, 0.0006, 80);
    qf->SetParNames("p0", "p1","limit");
    const int N = 200;
    double xmin = 1.0, xmax = 100.0;
    double dx = (xmax - xmin) / (N - 1);
    std::vector<double> xvals, yvals;
    for (int i = 0; i < N; ++i) 
    {
        double ER = xmin + i * dx;
        double y = qf->Eval(ER);
        double x = ER*y;
        xvals.push_back(x);
        yvals.push_back(y);
        
    }
    TGraph* result = new TGraph(N, xvals.data(), yvals.data());
    return result;
}
double getQFI(double ee)
{
  TGraph * g = QFI();
  return g->Eval(ee);
}

// Get TGRaph with QF Na in 0.1 keVee bins from 0 to 20 keVee
TGraph * getQFNa() 
{
  double eini = 0;
  double eend = 20;
  double deltaE=0.1;
  int n= (eend-eini)/deltaE;
  TGraph * g = QFNa();
  for (int i=0; i<n; i++) g->SetPoint(i,eini+deltaE*i, g->Eval(eini+deltaE*i));
  return g;
}
// Get TGRaph with QF eI in 0.1 keVee bins from 0 to 20 keVee
TGraph * getQFI() 
{
  double eini = 0;
  double eend = 20;
  double deltaE=0.1;
  int n= (eend-eini)/deltaE;
  TGraph * g = QFI();
  for (int i=0; i<n; i++) g->SetPoint(i,eini+deltaE*i, g->Eval(eini+deltaE*i));
  return g;
}

void QFNaI_save(std::string filename="QFTamara.root")
{
  TFile * f = new TFile (filename.c_str(),"RECREATE");
  TGraph * gNa= getQFNa();
  gNa->SetName("gNa");
  gNa->Write();
  TGraph * gI= getQFI();
  gI->SetName("gI");
  gI->Write();
  f->Close();
}
