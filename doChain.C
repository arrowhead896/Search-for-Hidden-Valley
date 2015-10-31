#include "./ChainPlot.h"
#include <iostream>
#include "TSystem.h"

using std::cout;

void doChain()
{
  // Test run of chainPlot
  cout << "starting" << endl;
  TChain *c = new TChain("physics");
  c->Add("/phys/groups/tev/scratch3/users/HV/WHHV/ntup_001/*.root");
  gSystem->CompileMacro("ChainPlot.C");
  ChainPlot *processor = new ChainPlot();
  c->Process(processor);
  cout << "running..." << endl;
}
