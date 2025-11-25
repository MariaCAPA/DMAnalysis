/**********************************
 * Maria Martinez 12/03/12
 * Class DMVPlotHandle
 * Virtual mother class for PlotHandle objects
 *********************************/
#include "DMVPlotHandle.hh"
#include "DMUtil.hh"
#include <TTree.h>
#include <TObjArray.h>
#include <TLeaf.h>
#include <TBranch.h>
#include <TMath.h>

// Conctructor
DMVPlotHandle::DMVPlotHandle (){fScaleY=1;fScaleX=1;massUnit = "GeV";}
 
// Destructor
DMVPlotHandle::~DMVPlotHandle(){}

// AUXILIAR FUNCITONS

// Dump tree contents in filename fileName
int DMVPlotHandle::Dump(char * fileName, TTree * tree)
{
  std::string parsed = DMParseShellVars(fileName);
  fstream fq (parsed.c_str(), std::ios::out);
  if (!fq.good())
  {
    std::cout << "Cannot open output file " << parsed.c_str() << std::endl;
    return -1;
  }


  // Get branches names
  int i, j;
  TObjArray *branches = tree->GetListOfBranches();
  int nbranches = branches->GetEntriesFast();

  //fq << "#";
  for (j=0; j<nbranches;j++) 
  {
    fq << ((TBranch*)branches->At(j))->GetName();
    if (j<nbranches-1) fq << ":";
  }
  fq << std::endl;

  // Get entries
  int nRows = tree->GetEntries();
  for (i=0; i<nRows; i++)
  {
    tree->GetEntry(i);
    TObjArray *leaves = tree->GetListOfLeaves();
    for (j=0; j<nbranches;j++) 
    {
      double val = (double)(((TLeaf*)leaves->At(j))->GetValue()) ;
      if (TMath::IsNaN(val)) fq << 0 << " ";
      else fq << val << " ";
    }
    fq << std::endl;
  }
  
  return 0;
}
