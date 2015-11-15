void doChain(char *path)
{
  // Test run of chainPlot
  cout << "starting" << endl;
  TChain *c = new TChain("physics");
  c->Add(path);
  gSystem->CompileMacro("/phys/groups/tev/scratch3/users/will896/WHProduction/Search-for-Hidden-Valley/ChainPlot.C");
  ChainPlot *processor = new ChainPlot();
  cout << "running..." << endl;
  c->Process(processor);
}
