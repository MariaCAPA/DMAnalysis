////////////////////////
// Example dumpRate.C
// - Initialize a DMRate class with parameters from templates/rate.dat
// 			* Detector with two elements Na, I 
//            whose parameters are readed from templates/Na.dat, templates/I.dat 
//          * Isothermal halo model. Paramteres read from templates/iso.dat
// - Change some of this parameters (Wimp mass, SI cross section, SD cross section)  
// - Calculate the expected rate and dump it to a text file. The output var meanings are:
//   E: energy in keV
//   S0: Non modulated expected rate 
//   Sm: Modulated expected rate 
//   Phi: Phase of the maximum in years
//        (For the isothermal sphere it is always 1st June = 0.414717, but it can change for other halo models
//        So the rate in the detector is S(t) = S0 + Sm*cosw(t-Phi)
//   FF2SI_1: squared form factor SI for element 1 (Na)
//   FF2SD_1: squared form factor SD for element 1 (Na)
//   FF2SI_2: squared form factor SI for element 2 (I)
//   FF2SD_2: squared form factor SD for element 2 (I)
{
   gSystem->Load("libDMAnalysis");
  // Initalize rate class
  int error;
  DMRate * rate = new DMRate();
  error = rate->Initialize("$DMANALYSIS/templates/rate.dat");
  if (error<0) return;

  // Create plot handle and pass the rate class
  DMRatePlotHandle  plothl (rate);

  double MW = 10; // GeV
  double SI=1e-5; // pb
  double SD=0; // pb

  rate->SetMW(MW);
  rate->SetSigSI(SI);
  rate->SetSigSD(SD);

  // usage Dump("filename", NBins, Eini, Eend)
  // energy in keV
  // by default NBins=100, Eini=0, Eend = 100 keV
  plothl.Dump("rate10GeV_SI1e-5.dat",1000);
}
