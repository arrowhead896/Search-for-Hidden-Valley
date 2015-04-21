#define ChainPlot_cxx
// The class definition in ChainPlot.h has been generated automatically
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
// Root > T->Process("ChainPlot.C")
// Root > T->Process("ChainPlot.C","some options")
// Root > T->Process("ChainPlot.C+")
//

#include "ChainPlot.h"
#include <math.h>  
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <algorithm>
#include <TVector2.h>

using namespace std;

void ChainPlot::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   noAssocJetHist = new TH2F("jet", "#Delta r against decay length; decay length [m]; #Delta r", 50, 5, 20.0, 100, 0.0, 4.0);
   deltaRHist = new TH1F("deltaR", "#Delta r; #Delta r;", 100, 0, 4.0);
   ptHist = new TH2F("p_{T}", "p_{T} of vpion against decay length; decay length [m]; #p_{T} [GeV]", 50, 5, 50.0, 100, 0, 1000);
   etaHist = new TH2F("#eta", "#eta of vpion against decay length; decay length [m]; #eta", 50, 5, 50.0, 100, 0.0, 4.0);
   phiHist = new TH2F("#phi", "#phi of vpion against decay length; decay length [m]; #phi", 50, 5, 50.0, 100, 0.0, 4.0);
   jetptBHist = new TH1F("jet p_{T} before", "p_{T} of nearest jet (before cut); #p_{T} [GeV]", 100, 0, 1000);
   jetptAHist = new TH1F("jet p_{T} after", "p_{T} of nearest jet (after cut); #p_{T} [GeV]", 100, 0, 1000);
   jetptHist = new TH2F("p_{T} of jet", "p_{T} of nearest jet against decay length; decay length [m]; #p_{T} [GeV]", 50, 5, 50.0, 100, 0, 1000);
   jetetaHist = new TH2F("#eta of jet", "#eta of nearest jet against decay length; decay length [m]; #eta", 50, 5, 50.0, 100, 0.0, 4.0);
   jetphiHist = new TH2F("#phi of jet", "#phi of nearest jet against decay length; decay length [m]; #phi", 50, 5, 50.0, 100, 0.0, 4.0);
   calRatioHist = new TH1F("calRatio", "calRatio; calRatio", 100, 0, 5);
   calRatioInCalHist = new TH1F("calRatioInCalHist", "calRatio associated with decays in calorimeter; calRatio", 50, 0, 5);
   calRatioBeforeCalHist = new TH1F("calRatioBeforeCalHist", "calRatio associated with decays before calorimeter; calRatio", 100, 0, 5);
   calRatioAfterCalHist = new TH1F("calRatioAfterCalHist", "calRatio associated with decays after calorimeter; calRatio", 100, 0, 5);
   calRatioVsDecayLengthHist = new TH2F("calRatioVsDecayLengthHist", "calRatio against decay length; decay length [m]; calRatio", 100, 0, 20.0, 100, 0, 5);
}

void ChainPlot::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t ChainPlot::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either ChainPlot::GetEntry() or TBranch::GetEntry()
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
  cout << "Looking at particles" << endl;
  for (size_t i = 0; i < mc_pdgId->size(); i++) {
	if (mc_child_index->at(i).size() != 0 && jet_AntiKt4LCTopo_eta->size() != 0) {
		if (mc_pdgId->at(i) == 36 && jet_AntiKt4LCTopo_eta->size() != 0) {
			float startx = mc_vx_x->at(i);
			cout << "Got startx" << endl;
			float starty = mc_vx_y->at(i);
			cout << "Got starty" << endl;
			float endx = mc_vx_x->at(mc_child_index->at(i).at(0));
			cout << "Got endx: " << endx << endl;
			float endy = mc_vx_y->at(mc_child_index->at(i).at(0));
			cout << "Got endy: " << endy << endl;
			float distance = sqrt((endx-startx)*(endx-startx) + (endy-starty)*(endy-starty))/1000.0;
			cout << "Got pion" << endl;
			float hvEta = mc_eta->at(i);
			cout << "Got mcEta" << endl;
			float hvPhi = mc_phi->at(i);
			cout << "Got mcPhi" << endl;
			size_t nearestJet = GetNearestJet(hvEta, hvPhi, jet_AntiKt4LCTopo_eta, jet_AntiKt4LCTopo_phi);
			cout << "Got jet index: " << nearestJet << endl;
			float jetEta = jet_AntiKt4LCTopo_eta->at(nearestJet);
			cout << "Got jetEta" << endl;
			float jetPhi = jet_AntiKt4LCTopo_phi->at(nearestJet);
			cout << "Got jetPhi" << endl;
			float deltaPhi = TVector2::Phi_mpi_pi(hvPhi-jetPhi);
			float deltaEta = hvEta-jetEta;
			float deltaR = sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);
			float jetpt = (jet_AntiKt4LCTopo_pt->at(nearestJet))/1000;
			cout << "Got deltaR" << endl;
			//check to see if deltaR is within the cut
			jetptBHist->Fill(jetpt);
			if (deltaR < 0.3)
			{
				float emfrac = jet_AntiKt4LCTopo_emfrac->at(nearestJet);
				float energy = jet_AntiKt4LCTopo_E->at(nearestJet);
				float emEnergy = emfrac*energy;
				float hadEnergy = (1-emfrac)*energy;
				float calRatio = log10(emEnergy/hadEnergy);
				calRatioHist->Fill(calRatio);
				if (distance > 2.0 && distance < 3.27)
				{
					calRatioInCalHist->Fill(calRatio);
					cout << "In calorimeter" << endl;
				}
				else if (distance <= 2.0)
				{
					calRatioBeforeCalHist->Fill(calRatio);
					cout << "Before calorimeter" << endl;
				}	
			else
			{
				calRatioAfterCalHist->Fill(calRatio);
				cout << "After calorimeter" << endl;
			}
			calRatioVsDecayLengthHist->Fill(distance, calRatio);
						noAssocJetHist->Fill(distance, deltaR);
						deltaRHist->Fill(deltaR);
						ptHist->Fill(distance,(mc_pt->at(i))/1000);
		   				etaHist->Fill(distance, hvEta);
		  				phiHist->Fill(distance, hvPhi);   
						jetptHist->Fill(distance, jetpt);
		   				jetetaHist->Fill(distance, jetEta);
						jetphiHist->Fill(distance, jetPhi);
				jetptAHist->Fill(jetpt);
			}
				cout << "Done with pion" << endl;
		}

	}
    }

   return kTRUE;
}

size_t ChainPlot::GetNearestJet(float hvEta, float hvPhi, vector<float> *jetEta, vector<float> *jetPhi)
{
	float minDeltaR = 1000;
	int minIndex = 0;
  	for (size_t j = 0; j < jetEta->size(); j++) 
	{
		float jetEtaValue = jetEta->at(j);
		float jetPhiValue = jetPhi->at(j);
		float deltaPhi = TVector2::Phi_mpi_pi(hvPhi-jetPhiValue);
		float deltaEta = hvEta-jetEtaValue;
		float deltaR = deltaPhi*deltaPhi + deltaEta*deltaEta;
		if (deltaR < minDeltaR) 
		{
			minIndex = j;
			minDeltaR = deltaR;
		}
	}
	return minIndex;
}

void ChainPlot::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void ChainPlot::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   cout << "Done processing";
   TFile *f = new TFile("chainplot.root", "RECREATE");
   noAssocJetHist->Write();
   deltaRHist->Write();
   ptHist->Write();
   etaHist->Write();
   phiHist->Write(); 
   jetptBHist->Write();
   jetptAHist->Write();
   jetptHist->Write();
   jetetaHist->Write();
   jetphiHist->Write();
   calRatioHist->Write();
   calRatioInCalHist->Write();
   calRatioBeforeCalHist->Write();
   calRatioAfterCalHist->Write();
   calRatioVsDecayLengthHist->Write();
   f->Write();
   f->Close();
}
