//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 10 15:11:59 2014 by ROOT version 5.34/21
// from TTree physics/physics
// found on file: /phys/groups/tev/scratch3/users/HV/WHHV/ntup_001/ntup_aod_00_201_250.root
//////////////////////////////////////////////////////////

#ifndef ChainPlot_h
#define ChainPlot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1F.h>
#include <TH2F.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

#ifdef __CINT__

#pragma link C++ class vector<vector<int> >+;

#endif

class ChainPlot : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   TH2F	*noAssocJetHist;

   // Declaration of leaf types

   vector<float>   *jet_AntiKt4LCTopo_flavor_weight_MV1;
   vector<float>   *mc_pt;
   vector<float>   *mc_eta;
   vector<float>   *mc_phi;
   vector<int>     *mc_pdgId;
   vector<float>   *mc_vx_x;
   vector<float>   *mc_vx_y;
   vector<vector<int> > *mc_child_index;
   vector<float>   *jet_AntiKt4LCTopo_pt;
   vector<float>   *jet_AntiKt4LCTopo_eta;
   vector<float>   *jet_AntiKt4LCTopo_phi;
   vector<float>   *jet_AntiKt4LCTopo_emfrac;
   vector<int>     *jet_AntiKt4LCTopo_isUgly;
   vector<float>   *trk_pt;
   vector<float>   *trk_eta;
   vector<float>   *trk_phi_wrtPV;
   vector<float>   *trk_cov_d0_wrtPV;
   
   //List of branches
   TBranch   *b_jet_AntiKt4LCTopo_flavor_weight_MV1;
   TBranch   *b_mc_pt;
   TBranch   *b_mc_eta;
   TBranch   *b_mc_phi;
   TBranch   *b_mc_pdgId;
   TBranch   *b_mc_vx_x;
   TBranch   *b_mc_vx_y;
   TBranch   *b_mc_child_index;
   TBranch   *b_jet_AntiKt4LCTopo_pt;
   TBranch   *b_jet_AntiKt4LCTopo_eta;
   TBranch   *b_jet_AntiKt4LCTopo_phi;
   TBranch   *b_jet_AntiKt4LCTopo_emfrac;
   TBranch   *b_jet_AntiKt4LCTopo_isUgly;
   TBranch   *b_trk_pt;
   TBranch   *b_trk_eta;
   TBranch   *b_trk_phi_wrtPV;
   TBranch   *b_trk_cov_d0_wrtPV;
   
   ChainPlot(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~ChainPlot() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual size_t  GetNearestJet(float hvEta, float hvPhi, vector<float> *jetEta, vector<float> *jetPhi);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(ChainPlot,0);
};
#endif // #ifndef ChainPlot_h

#ifdef ChainPlot_cxx

void ChainPlot::Init(TTree *tree)
{
   //setting object pointers
   jet_AntiKt4LCTopo_flavor_weight_MV1 = 0;
   mc_pt = 0;
   mc_eta = 0;
   mc_phi = 0;
   mc_pdgId = 0;
   mc_vx_x = 0;
   mc_vx_y = 0;
   mc_child_index = 0;
   jet_AntiKt4LCTopo_pt = 0;
   jet_AntiKt4LCTopo_eta = 0;
   jet_AntiKt4LCTopo_phi = 0;
   jet_AntiKt4LCTopo_emfrac = 0;
   jet_AntiKt4LCTopo_isUgly = 0;
   trk_pt = 0;
   trk_eta = 0;
   trk_phi_wrtPV = 0;
   trk_cov_d0_wrtPV = 0;
   
   //setting branch addresses
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);
   
   fChain->SetBranchStatus("*", false);

   fChain->SetBranchAddress("jet_AntiKt4LCTopo_flavor_weight_MV1", &jet_AntiKt4LCTopo_flavor_weight_MV1, &b_jet_AntiKt4LCTopo_flavor_weight_MV1);

   //fChain->SetBranchStatus("mc_pt", true);
   fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);

   fChain->SetBranchStatus("mc_eta", true);
   fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);

   fChain->SetBranchStatus("mc_phi", true);
   fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);

   fChain->SetBranchStatus("mc_pdgId", true);
   fChain->SetBranchAddress("mc_pdgId", &mc_pdgId, &b_mc_pdgId);

   fChain->SetBranchStatus("mc_vx_x", true);
   fChain->SetBranchAddress("mc_vx_x", &mc_vx_x, &b_mc_vx_x);
   fChain->SetBranchStatus("mc_vx_y", true);
   fChain->SetBranchAddress("mc_vx_y", &mc_vx_y, &b_mc_vx_y);
   //if this next line is commented, the code works up to the point that I try to access mc_child_index
   //as is, it will fail as soon as the GetEntry method is called
   fChain->SetBranchStatus("mc_child_index*", true);
   fChain->SetBranchAddress("mc_child_index", &mc_child_index, &b_mc_child_index);
   fChain->SetBranchStatus("jet_AntiKt4LCTopo_pt", true);
   fChain->SetBranchAddress("jet_AntiKt4LCTopo_pt", &jet_AntiKt4LCTopo_pt, &b_jet_AntiKt4LCTopo_pt);
   fChain->SetBranchStatus("jet_AntiKt4LCTopo_eta", true);
   fChain->SetBranchAddress("jet_AntiKt4LCTopo_eta", &jet_AntiKt4LCTopo_eta, &b_jet_AntiKt4LCTopo_eta);
   fChain->SetBranchStatus("jet_AntiKt4LCTopo_phi", true);
   fChain->SetBranchAddress("jet_AntiKt4LCTopo_phi", &jet_AntiKt4LCTopo_phi, &b_jet_AntiKt4LCTopo_phi);
   fChain->SetBranchAddress("jet_AntiKt4LCTopo_emfrac", &jet_AntiKt4LCTopo_emfrac, &b_jet_AntiKt4LCTopo_emfrac);
   fChain->SetBranchAddress("jet_AntiKt4LCTopo_isUgly", &jet_AntiKt4LCTopo_isUgly, &b_jet_AntiKt4LCTopo_isUgly);
   fChain->SetBranchAddress("trk_pt", &trk_pt, &b_trk_pt);
   fChain->SetBranchAddress("trk_eta", &trk_eta, &b_trk_eta);
   fChain->SetBranchAddress("trk_phi_wrtPV", &trk_phi_wrtPV, &b_trk_phi_wrtPV);
   fChain->SetBranchAddress("trk_cov_d0_wrtPV", &trk_cov_d0_wrtPV, &b_trk_cov_d0_wrtPV);
}
Bool_t ChainPlot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif //ifdef ChainPlot_cxx

