void doWJets()
{
  // Test run of chainPlot
  cout << "starting" << endl;
  TChain *c = new TChain("physics");
  c->Add("/phys/groups/tev/scratch4/users/gwatts/GRIDDS/mc12_8TeV.117680.AlpgenPythia_P2011C_WenuNp0.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575/mc12_8TeV.117680.AlpgenPythia_P2011C_WenuNp0.merge.NTUP_COMMON.e1477_s1499_s1504_r3658/*.root.1");
  c->Add("/phys/groups/tev/scratch4/users/gwatts/GRIDDS/mc12_8TeV.117681.AlpgenPythia_P2011C_WenuNp1.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575/mc12_8TeV/*.root.1");
  c->Add("/phys/groups/tev/scratch4/users/gwatts/GRIDDS/mc12_8TeV.117682.AlpgenPythia_P2011C_WenuNp2.merge.NTUP_COMMON.e1477_s1499_s1504_r3658_r3549_p1575/mc12_8TeV/*.root.1");
  gSystem->CompileMacro("/phys/groups/tev/scratch3/users/will896/WHProduction/Search-for-Hidden-Valley/WJetsPlot.C");
  WJetsPlot *processor = new WJetsPlot();
  cout << "running..." << endl;
  c->Process(processor);
}
