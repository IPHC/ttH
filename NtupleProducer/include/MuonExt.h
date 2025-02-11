#ifndef MUONEXT_H
#define MUONEXT_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Muon.h"

class MuonExt : public Muon
{
 public:
   
   MuonExt();
   virtual ~MuonExt();
   
   void sel(bool=false,int year=2016);
   void read(bool isdata);
   void init();
   float getEffArea(float eta,int year);
   float smoothBFlav(float jetpt,float ptmin,float ptmax,int year);
   
   int ID;
   
   int fakeType;
   
   float ptCor;
   float ptUnc;
   
   bool isLoose;
   bool isMedium;
   bool isTight;
   bool isPFMuon;
   
   float dxy;
   float dz;
   float iso;
   float PFRelIso04; //renamed
   float sip3d;
   float bestTrack_pt;
   float bestTrack_ptError;
   bool cutEventSel;
   bool noLostHits;
   
   float lepMVA_miniRelIsoCharged;
   float lepMVA_miniRelIsoNeutral;
   float lepMVA_jetPtRelv2;
   float lepMVA_jetPtRatio;
   float jetRelIso;
   float lepMVA_jetBTagCSV;
   float lepMVA_jetBTagDeepCSV;
   float lepMVA_jetBTagDeepFlavour;
   float lepMVA_sip3d;
   float lepMVA_dxy;
   float lepMVA_dz;
   float lepMVA_mvaId;
   float lepMVA_eta;
   float lepMVA_jetNDauChargedMVASel;
   
   ClassDef(MuonExt,1)
};

#endif
