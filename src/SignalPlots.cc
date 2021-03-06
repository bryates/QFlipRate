#include "SignalPlots.h"

SignalPlots::SignalPlots(TString name) {
  h_jjmass =         new TH1F("h_dijetsmass_"    + name,"Invariant mass of the two leading jets",100,0,1000);
  h_llmass =         new TH1F("h_llmass_"        + name,"Invariant mass of the two leading muons",100,0,1000);
  h_l1jjmass =       new TH1F("h_l1jjmass_"      + name,"Invariant mass of the leading muon plus jets",100,0,1000);
  h_l2jjmass =       new TH1F("h_l2jjmass_"      + name,"Invariant mass of the trailing muon plus jets",100,0,1000);
  h_lljjmass =       new TH1F("h_lljjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
  h_MET =            new TH1F("h_MET_"           + name,"Missing Et",100,0.0,500.0);
  h_MET_phi =        new TH1F("h_MET_phi_"       + name,"Missing Et #phi",100,-3.14,3.14);
  h_MT2ll =          new TH1F("h_MT2ll_"         + name,"MT2(ll)",50,0.0,250.0);
  h_MT2bb =          new TH1F("h_MT2bb_"         + name,"MT2(bb)",100,80.0,580.0);
  h_MT2lblb =        new TH1F("h_MT2lblb_"       + name,"MT2(lblb)",110,0.0,550.0);
  h_dilepPt =        new TH1F("h_dilepPt_"       + name,"Sum dilepton p_{T}",100,0.0,500.0);
  h_cosTheta1 =      new TH1F("h_cosTheta1_"     + name,"cos#theta first muon",100,-1,1);
  h_cosTheta2 =      new TH1F("h_cosTheta2_"     + name,"cos#theta second muon",100,-1,1);
  h_DeltaPhi =       new TH1F("h_DeltaPhi_"      + name,"#Delta#phi between two muons",100,0.0,3.15);
  h_PV =             new TH1F("h_PV_"            + name,"number of primary vertices",60,0,60);
}

SignalPlots::~SignalPlots() {
  delete h_jjmass;
  delete h_llmass;
  delete h_l2jjmass;
  delete h_l1jjmass;
  delete h_lljjmass;
  delete h_MET;
  delete h_MET_phi;
  delete h_MT2ll;
  delete h_MT2bb;
  delete h_MT2lblb;
  delete h_dilepPt;
  delete h_cosTheta1;
  delete h_cosTheta2;
  delete h_DeltaPhi;
  delete h_PV;
}

void SignalPlots::Fill(UInt_t numberVertices, Double_t MET, Double_t MET_phi, std::vector<Lepton>& leptons, std::vector<Jet>& jets, Double_t weight, Int_t channel, Int_t cut) {
  m=0; n=1; i=0; j=1;
    
  h_PV->Fill(numberVertices, weight);
  h_MET->Fill(MET, weight);
  h_MET_phi->Fill(MET_phi, weight);
  h_llmass->Fill( (leptons[i].lorentzVec()+leptons[j].lorentzVec()).M(),weight);
  
  h_MT2ll->Fill(getMT2(leptons[i].lorentzVec(), leptons[j].lorentzVec(), MET, MET_phi), weight);

  if (cut>1 && cut!=3 && cut!=4) {
    h_MT2bb->Fill( getMT2bb(jets, leptons, MET, MET_phi), weight);
    h_MT2lblb->Fill( getMT2lblb(jets, leptons, MET, MET_phi), weight);  

    h_jjmass->Fill( (jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
    h_lljjmass->Fill( (leptons[i].lorentzVec()+leptons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
    h_l1jjmass->Fill( (leptons[i].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
    h_l2jjmass->Fill( (leptons[j].lorentzVec()+jets[m].lorentzVec()+jets[n].lorentzVec()).M(),weight);
  }
  
  h_cosTheta1->Fill(cos(leptons[i].lorentzVec().Theta()),weight);
  h_cosTheta2->Fill(cos(leptons[j].lorentzVec().Theta()),weight);
  h_DeltaPhi->Fill(fabs(leptons[i].lorentzVec().DeltaPhi(leptons[j].lorentzVec())),weight);
  
  
}

void SignalPlots::Write() {
  h_jjmass->Write();
  h_llmass->Write();
  h_l1jjmass->Write();
  h_l2jjmass->Write();
  h_lljjmass->Write();
  h_MET->Write();
  h_MET_phi->Write();
  h_MT2ll->Write();
  h_MT2bb->Write();
  h_MT2lblb->Write();
  h_dilepPt->Write();
  h_cosTheta1->Write();
  h_cosTheta2->Write();
  h_DeltaPhi->Write();
  h_PV->Write();
}

