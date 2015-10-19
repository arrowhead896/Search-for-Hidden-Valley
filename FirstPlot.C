#define FirstPlot_cxx
// The class definition in FirstPlot.h has been generated automatically
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
// Root > T->Process("FirstPlot.C")
// Root > T->Process("FirstPlot.C","some options")
// Root > T->Process("FirstPlot.C+")
//

#include "FirstPlot.h"
#include <math.h>  
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include <TVector2.h>

using namespace std;

void FirstPlot::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   ptHist = new TH1F("ptHist", "p_{T} of HV pions;p_{T} [GeV]", 100, 0, 1000);
   etaHist = new TH1F("etaHist", "#eta of HV pions; #eta", 100, -4.0, 4.0);
   phiHist = new TH1F("phiHist", "#phi of HV pions; #phi", 100, -4.0, 4.0);
   angDiffHist = new TH1F("angDiffHist", "#Delta r between HV pion and jet; sqrt(#eta^2+#phi^2)", 100, 0, 4.0);
   jetEtaHist = new TH1F("jetEtaHist", "jet #eta; #eta", 100, 0, 4.0);
   jetPhiHist = new TH1F("jetPhiHist", "jet #phi; #phi", 100, 0, 4.0);
   jetptHist = new TH1F("jetptHist", "jet p_{T}; p_{T} [GeV]", 100, 0, 1000);
   missingpTHist = new TH1F("missingpTHist", "missing energy (p_{T} of neutrinos from W decay); #p_{T} [GeV]", 100, -1000, 1000);
}

void FirstPlot::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t FirstPlot::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either FirstPlot::GetEntry() or TBranch::GetEntry()
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
  cout << "Looking at entry " << entry << endl;
  GetEntry(entry);
  cout << "  -> Got entry" << endl;

  TBranch *b = fChain->GetBranch("mc_pdgId");
  if (b == 0) 
{
    cout << "  -> Oh, that is very bad. This is boot!" << endl;
    return true;
  }
  b->GetEntry(entry);
  cout << "Got entry" << endl;
  missingpTHist->Fill(MET_MuonMuons_et);
  /*
  for (size_t i = 0; i < mc_pdgId->size(); i++)
    {
	//check if it's a HV pion
	if (mc_pdgId->at(i) == 36)
	{
		float hvEta = mc_eta->at(i);
		float hvPhi = mc_phi->at(i);
		ptHist->Fill((mc_pt->at(i))/1000);
	  	etaHist->Fill(hvEta);
	  	phiHist->Fill(hvPhi);
		size_t nearestJet = GetNearestJet(hvEta, hvPhi, jet_AntiKt4LCTopo_eta, jet_AntiKt4LCTopo_phi);
		float jetEta = jet_AntiKt4LCTopo_eta->at(nearestJet);
		float jetPhi = jet_AntiKt4LCTopo_phi->at(nearestJet);
		float deltaPhi = TVector2::Phi_mpi_pi(hvPhi-jetPhi);
		float deltaEta = hvEta-jetEta;
		float deltaR = sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);
		angDiffHist->Fill(deltaR);
		if (deltaR < 0.3) 
		{
			jetptHist->Fill(jet_AntiKt4LCTopo_pt->at(nearestJet)/1000);
			cout << "jet index: " << nearestJet << endl;
			cout << "pt: " << jet_AntiKt4LCTopo_pt->at(nearestJet)/1000 << endl;
			jetEtaHist->Fill(jet_AntiKt4LCTopo_eta->at(nearestJet));
			jetPhiHist->Fill(jet_AntiKt4LCTopo_phi->at(nearestJet));
		}
	}
    }
  */
   return kTRUE;
}

size_t FirstPlot::GetNearestJet(float hvEta, float hvPhi, vector<float> *jetEta, vector<float> *jetPhi)
{
  /* float minDeltaR = 1000;
	int minIndex = 0;
  	for (size_t j = 0; j < jetEta->size(); j++) 
	{
		float jetEta = jet_AntiKt4LCTopo_eta->at(j);
		float jetPhi = jet_AntiKt4LCTopo_phi->at(j);
		float deltaPhi = TVector2::Phi_mpi_pi(hvPhi-jetPhi);
		float deltaEta = hvEta-jetEta;
		float deltaR = deltaPhi*deltaPhi + deltaEta*deltaEta;
		if (deltaR < minDeltaR) 
		{
			minIndex = j;
			minDeltaR = deltaR;
		}
	}
	return minIndex;*/
  return 0;
}

void FirstPlot::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void FirstPlot::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   TFile *f = new TFile("firstplot.root", "RECREATE");
   ptHist->Write();
   etaHist->Write();
   phiHist->Write();
   angDiffHist->Write();
   jetEtaHist->Write();
   jetptHist->Write();
   jetPhiHist->Write();
   missingpTHist->Write();
   f->Write();
   f->Close();
}
