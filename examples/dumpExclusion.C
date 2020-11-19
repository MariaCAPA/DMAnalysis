////////////////////////
// Example dumpExclusion.C
// - Initialize a DMExclusion class with parameters from templates/exclusion.dat
//       * Initialize detector & and halo parameters from templates/rate.dat:
//              - Detector with two elements Na, I 
//                 whose parameters are readed from templates/Na.dat, templates/I.dat 
//              - Isothermal halo model. Paramteres read from templates/iso.dat
//       * Initialize exposure, CL, Bkg(lineal), energy window
// - Change some of this parameters (Exposure)
// - Calculate the exclusion curve and dump it to a text file. The output var meanings are:
//   MW: Wimp mass in GeV
//   SI: SI cross section in pb
//   SD: SD cross section in pb
{
   gSystem->Load("libDMAnalysis");

  // Initalize exclusion class
  int error;
  DMExclusion * exclusion = new DMExclusion();
  error = exclusion->Initialize("$DMANALYSIS/templates/exclusion.dat");
  if (error<0) return;

  // Create plot handle and pass the exclusion class
  DMExclusionPlotHandle  plothl (exclusion);

  // CHANGE PARAMETERS IF NEEDED
  exclusion->SetExposure(365*250*0.7); // kgxday

  // usage Dump("filename", MWini, MWend)
  // (By now, only fro 1 to 1000)
  plothl.Dump("exclusionOutput.dat");
}
