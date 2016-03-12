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
  trkptHist = new TH1F("track pt", "#track p_t; #track p_t [GeV]", 100, 0, 100);
  numTrackHist = new TH1F("num tracks", "num tracks; num tracks", 15, 0, 15);
  noAssocJetHist = new TH2F("jet", "#Delta r against decay length; decay length [m]; #Delta r", 50, 5, 20.0, 100, 0.0, 4.0);
  deltaRHist = new TH1F("deltaR", "#Delta r; #Delta r;", 100, 0, 4.0);
  ptHist = new TH1F("p_{T}", "p_{T} of vpion; #p_{T} [GeV]", 100, 0, 1000);
  etaHist = new TH1F("#eta", "#eta of vpion; #eta", 100, 0.0, 4.0);
  distHist = new TH1F("distance", "decay length of vPion; decay length [m]", 100, 0, 6);
  phiHist = new TH1F("#phi", "#phi of vpion against decay length; decay length [m]; #phi", 100, 0.0, 4.0);
  jetptBHist = new TH1F("jet p_{T} before", "p_{T} of nearest jet (before cut); #p_{T} [GeV]", 100, 0, 1000);
  jetptAHist = new TH1F("jet p_{T} after", "p_{T} of nearest jet (after cut); #p_{T} [GeV]", 100, 0, 1000);
  jetptHist = new TH1F("p_{T} of jet", "p_{T} of nearest jet; #p_{T} [GeV]", 100, 0, 1000);
  jetetaHist = new TH1F("#eta of jet", "#eta of nearest jet; #eta", 100, 0.0, 4.0);
  jetphiHist = new TH1F("#phi of jet", "#phi of nearest jet; #phi", 100, 0.0, 4.0);
  calRatioHist = new TH1F("calRatio", "calRatio; calRatio", 100, -3, 5);
  calRatioInCalHist = new TH1F("calRatioInCalHist", "calRatio associated with decays in calorimeter; calRatio", 50, -3, 5);
  calRatioBeforeCalHist = new TH1F("calRatioBeforeCalHist", "calRatio associated with decays before calorimeter; calRatio", 100, -3, 5);
  calRatioAfterCalHist = new TH1F("calRatioAfterCalHist", "calRatio associated with decays after calorimeter; calRatio", 100, -3, 5);
  calRatioVsDecayLengthHist = new TH2F("calRatioVsDecayLengthHist", "calRatio against decay length; decay length [m]; calRatio", 100, 0, 20.0, 100, -3, 5);
  leptonpTHist = new TH1F("leptonpTHist", "p_{T} of leptons (from the W decay); #p_{T} [GeV]", 100, 0, 1000);
  missingpTHist = new TH1F("missingpTHist", "missing energy (p_{T} of neutrinos from W decay); #missing E_{T} [GeV]", 100, -1000, 1000);
  missingpTHist2 = new TH1F("missingpTHist (sumet)", "missing energy (p_{T} of neutrinos from W decay); #missing E_{T} [GeV]", 100, -1000, 1000);
  jetpTCuts = new TH1F("cuts on jet pT", "cut on jet pT vs. number passing cut; #jet p_{T} cut [GeV]; #number passing cut", 50, 0, 50);
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
  missingpTHist2->Fill(MET_RefFinal_sumet/1000);
  bool leptonValid = false;
  bool calRatioValid = false;
  bool distanceValid = false;
  bool trkValid = false;
  vector<float>* pionDistance = new vector<float>();
  for (size_t i = 0; i < mc_pdgId->size(); i++) {
    int pdgId = mc_pdgId->at(i);
    if (pdgId == -11 || pdgId == -13) {
      if (mc_pt->at(i)/1000 > 25 && abs(mc_eta->at(i)) <= 2.5) {
	leptonValid = true;
	break;
      }
    }
  }
  // THIS IS THE START OF THE LOOP
  for (size_t i = 0; i < mc_pdgId->size(); i++) { 
    if (mc_child_index->at(i).size() != 0 && jet_AntiKt4LCTopo_eta->size() != 0) {
      int pdgId = mc_pdgId->at(i);
      if (pdgId == 36) {
	//cout << "next pion" << endl;
	float startx = mc_vx_x->at(i);
	//cout << "Got startx" << endl;
	float starty = mc_vx_y->at(i);
	//cout << "Got starty" << endl;
	float endx = mc_vx_x->at(mc_child_index->at(i).at(0));
	//cout << "Got endx: " << endx << endl;
	float endy = mc_vx_y->at(mc_child_index->at(i).at(0));
	//cout << "Got endy: " << endy << endl;
	float distance = sqrt((endx-startx)*(endx-startx) + (endy-starty)*(endy-starty))/1000.0;
	//cout << "Got pion" << endl;
	float hvEta = mc_eta->at(i);
	//cout << "Got mcEta" << endl;
	float hvPhi = mc_phi->at(i);
	//cout << "Got mcPhi" << endl;
	size_t nearestJet = GetNearestJet(hvEta, hvPhi, jet_AntiKt4LCTopo_eta, jet_AntiKt4LCTopo_phi);
	//cout << "Got jet index: " << nearestJet << endl;
	float jetEta = jet_AntiKt4LCTopo_eta->at(nearestJet);
	//cout << "Got jetEta" << endl;
	float jetPhi = jet_AntiKt4LCTopo_phi->at(nearestJet);
	//cout << "Got jetPhi" << endl;
	float deltaPhi = TVector2::Phi_mpi_pi(hvPhi-jetPhi);
	float deltaEta = hvEta-jetEta;
	float deltaR = sqrt(deltaPhi*deltaPhi + deltaEta*deltaEta);
	float jetpt = (jet_AntiKt4LCTopo_pt->at(nearestJet))/1000;
	//cout << "Got deltaR" << endl;
	//check to see if deltaR is within the cut
	jetptBHist->Fill(jetpt);
	if (deltaR < 0.3) {
	  float calRatio = CalculateCalRatio(nearestJet);
	  calRatioHist->Fill(calRatio);
	  if (distance > 2.0 && distance < 4.25) {
	    calRatioInCalHist->Fill(calRatio);
	    distanceValid = true;
	    //cout << "In calorimeter" << endl;
	  }
	  else {
	    if (distance <= 2.0) {
	      calRatioBeforeCalHist->Fill(calRatio);
	      //cout << "Before calorimeter" << endl;
	    }
	    else {
	      calRatioAfterCalHist->Fill(calRatio);
	      //     cout << "After calorimeter" << endl;
	    }
	  }
	  if (calRatio > 1) {
	    pionDistance->push_back(distance);
	    calRatioValid = true;
	    //bool trackValid = CheckTrack(jetIndex);
	  }
	  calRatioVsDecayLengthHist->Fill(distance, calRatio);
	  noAssocJetHist->Fill(distance, deltaR);
	  deltaRHist->Fill(deltaR);
	}
	//cout << "Done with pion" << endl;
	// don't worry about this stuff below
      } else if (pdgId == -11 || pdgId == -13) {
	//cout << "lepton found" << endl;
	leptonpTHist->Fill(mc_pt->at(i)/1000);
      } else if (pdgId == 12 || pdgId == 14) {
	//cout << "neutrino found" << endl;
	missingpTHist->Fill(mc_pt->at(i)/1000);
      }
    }
  }
  
  for (size_t i = 0; i < jet_AntiKt4LCTopo_eta->size(); i++) {
    float jetPt = jet_AntiKt4LCTopo_pt->at(i)/1000;
    if (jetPt > 25) {
      totalJets++;	
      float jetEta = jet_AntiKt4LCTopo_eta->at(i);
      if (jetEta * jetEta < 1.7*1.7) {
	float calRatio = CalculateCalRatio(i);
	if (calRatio > 1.2) {
	  jetsPassingCalRatioCut++;
	  if (CheckTrack(i)) {	    
	    for (size_t j = 0; j < 50; j++) {
	      if (jetPt > j) {
		jetpTCuts->Fill(j);
	      }
	    }
	    jetsPassingTrackCut++;
	  }
	}
      }
    }
  }

  if (leptonValid) {
    passedLeptonCuts++;
    //    cout << "passed lepton cuts" << endl;
    if (MET_RefFinal_et/1000 >= 25) {  
      passedMETCuts++;
      //cout << "passed MET cuts" << endl;
      if (calRatioValid) {
	//cout << "passed calRatio cut" << endl;
	passedCalRatioCut++;
	if (trkValid) {
	  //cout << "passed track cut" << endl;
	  passedTrackCut++;
	}
	if (!distanceValid) {
	  for (size_t i = 0; i < pionDistance->size(); i++) {
	    distHist->Fill(pionDistance->at(i));
	    //cout << "3000" << endl;
	  }
	}
      }
    }
  } 
  if (distanceValid) {
    dTotal++;
    if (leptonValid) {
      dLepton++;
      //      cout << "passed lepton cuts" << endl;
      if (MET_RefFinal_et/1000 >= 25) {  
	dMET++;
	//cout << "passed MET cuts" << endl;
	if (calRatioValid) {
	  //cout << "passed calRatio cut" << endl;
	  dCalRatio++;
	  if (trkValid) {
	    //cout << "passed track cut" << endl;
	    dTrack++;
	  } 
	}
      }
    } 
  }
  return kTRUE;
}

Bool_t ChainPlot::CheckTrack(size_t jetIndex) {
   int badTracks = 0;
   float jetPhi = jet_AntiKt4LCTopo_phi->at(jetIndex);
   float jetEta = jet_AntiKt4LCTopo_eta->at(jetIndex);
   for (size_t j = 0; j < trk_pt->size(); j++) {
     //cout << "tracks" << endl;
     float trkDeltaPhi = TVector2::Phi_mpi_pi(jetPhi-trk_phi_wrtPV->at(j));
     float trkDeltaEta = jetEta-trk_eta->at(j);
     float trkDeltaRSquared = trkDeltaPhi*trkDeltaPhi + trkDeltaEta*trkDeltaEta;
     if (trkDeltaRSquared <= 0.04) {
       float trkPt = trk_pt->at(j)/1000;
       trkptHist->Fill(trkPt);
       if (trkPt >= 1) {
	 badTracks++;
       }
     }
   } 
   numTrackHist->Fill(badTracks);
   return (badTracks == 0); 
}

float ChainPlot::CalculateCalRatio(size_t jetIndex) {
  float emfrac = jet_AntiKt4LCTopo_emfrac->at(jetIndex);
  float energy = jet_AntiKt4LCTopo_E->at(jetIndex);
  float emEnergy = emfrac*energy;
  float hadEnergy = (1-emfrac)*energy;
  float calRatio = 0;
  if (emEnergy == 0 && hadEnergy ==0) {
    //  cout << "Is this really a jet?" << endl;
    calRatio = 0;
  } else if (emEnergy == 0 && hadEnergy != 0) {
    //cout << "Giant calRatio" << endl;
    calRatio = 20;
  } else {
    calRatio = log10(hadEnergy/emEnergy);
  }
}

size_t ChainPlot::GetNearestJet(float hvEta, float hvPhi, vector<float> *jetEta, vector<float> *jetPhi)
{
  float minDeltaR = 1000;
  int minIndex = 0;
  for (size_t j = 0; j < jetEta->size(); j++)  {
    float jetEtaValue = jetEta->at(j);
    float jetPhiValue = jetPhi->at(j);
    float deltaPhi = TVector2::Phi_mpi_pi(hvPhi-jetPhiValue);
    float deltaEta = hvEta-jetEtaValue;
    float deltaR = deltaPhi*deltaPhi + deltaEta*deltaEta;
    if (deltaR < minDeltaR)  {
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
  cout << "Done processing" << endl;
  cout << "Total Events: " << totalEvents << endl;
  cout << "Passed Lepton Cuts: " << passedLeptonCuts << endl;
  cout << "Passed MET Cuts: " << passedMETCuts << endl;
  cout << "Passed calRatio cuts: " << passedCalRatioCut << endl;
  cout << "Passed track cuts: " << passedTrackCut << endl;
  cout << "WITH PION IN CALORIMETER" << endl;
  cout << "Total Events: " << dTotal << endl;
  cout << "Passed Lepton Cuts: " << dLepton << endl;
  cout << "Passed MET Cuts: " << dMET << endl;
  cout << "Passed calRatio cuts: " << dCalRatio << endl;
  cout << "Passed track cuts: " << dTrack << endl;

  cout << "Total Jets: " << totalJets << endl;
  cout << "Passed calRatio cuts: " << jetsPassingCalRatioCut << endl;
  cout << "Passed track cuts: " << jetsPassingTrackCut << endl;

  TFile *f = new TFile("qcdplot.root", "RECREATE");
  noAssocJetHist->Write();
  deltaRHist->Write();
  trkptHist->Write();
  numTrackHist->Write();
  ptHist->Write();
  etaHist->Write();
  distHist->Write();
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
  leptonpTHist->Write();
  missingpTHist->Write();
  missingpTHist2->Write();
  jetpTCuts->Write();
  f->Write();
  f->Close();
}
