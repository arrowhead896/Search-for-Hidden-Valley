#define WJetsPlot_cxx
// The class definition in WJetsPlot.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("WJetsPlot.C")
// Root > T->Process("WJetsPlot.C","some options")
// Root > T->Process("WJetsPlot.C+")
//

#include "WJetsPlot.h"
#include <math.h>  
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include <TVector2.h>

using namespace std;


float WJetsPlot::CalculateProbability(size_t numJets) {
  return 1 - pow(1 - SINGLE_JET_PROBABILITY, numJets);
}

void WJetsPlot::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();
  
  jetptHist = new TH1F("p_{T} of jet", "p_{T} of jets for events passing lepton and MET cuts; #p_{T} [GeV]", 100, 0, 1000);
  leptonpTHist = new TH1F("leptonpTHist", "p_{T} of leptons (from the W decay); #p_{T} [GeV]", 100, 0, 1000);
  missingpTHist = new TH1F("missingpTHist", "missing energy (p_{T} of neutrinos from W decay); #missing E_{T} [GeV]", 100, 0, 1000);
  numJetsHist = new TH1F("numJets", "number of jets per event with #p_{T} > 25GeV", 10, 0, 10);
}

void WJetsPlot::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();
  
}

Bool_t WJetsPlot::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either WJetsPlot::GetEntry() or TBranch::GetEntry()
  // to read either all or the required parts of the data. When processing
  // keyed objects with PROOF, the object is already loaded and is available
  // via the fObject pointer.
  //
  // This function should contain the "body" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.
  // cout << "Looking at entry " << entry << endl;
  GetEntry(entry);
  //cout << "  -> Got entry" << endl;
  totalEvents++;
  TBranch *b = fChain->GetBranch("mc_pdgId");
  if (b == 0)  {
    cout << "  -> Oh, that is very bad. This is boot!" << endl;
    return true;
  }
  b->GetEntry(entry);
  if (totalEvents % 1000 == 0) {
    cout << "events processed: " << totalEvents << endl;;
  }
  //cout << "Looking at particles" << endl;
  missingpTHist->Fill(MET_RefFinal_et/1000);
  bool leptonValid = false;
  for (size_t i = 0; i < mc_pdgId->size(); i++) {
    int pdgId = mc_pdgId->at(i);
    if (pdgId == -11 || pdgId == -13) {
      leptonpTHist->Fill(mc_pt->at(i)/1000);
      if (mc_pt->at(i)/1000 > 25 && abs(mc_eta->at(i)) <= 2.5) {
	leptonValid = true;
	break;
      }
    }
  }
  if (leptonValid) {
    passedLeptonCuts++;
    if (MET_RefFinal_et/1000 >= 25) {
      passedMETCuts++;
      int numJets = 0;
      for (size_t i = 0; i < jet_AntiKt4LCTopo_pt->size(); i++) {
	float jetPt = jet_AntiKt4LCTopo_pt->at(i)/1000;
	jetptHist->Fill(jetPt);
	if (jetPt > 25) {
	  numJets++;
	}
      }
      numJetsHist->Fill(numJets);
      expectedEvents += CalculateProbability(numJets);
    }
  }
  return kTRUE;
}


void WJetsPlot::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
}

void WJetsPlot::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  cout << "Done processing" << endl;
  cout << "Total Events: " << totalEvents << endl;
  cout << "Passed Lepton Cuts: " << passedLeptonCuts << endl;
  cout << "Passed MET Cuts: " << passedMETCuts << endl;
  cout << "Expected events: " << expectedEvents << endl;

  TFile *f = new TFile("wjetsplot.root", "RECREATE");

  jetptHist->Write();
  leptonpTHist->Write();
  missingpTHist->Write();
  numJetsHist->Write();

  f->Write();
  f->Close();
}
