# LowEnergy
CUPID low energy analysis

to compile, do make in the main directory

to use the library, export variable DMANALYSIS pointing to the main directory and update LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$DMANALYSIS/lib:$LD_LIBRARY_PATH

include the following line in your macro:

gSystem->Load("libDMAnalysis");
