#ifndef ELECTRONEXT_H
#define ELECTRONEXT_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Electron.h"

class ElectronExt : public Electron
{
 public:
   
   ElectronExt();
   virtual ~ElectronExt();

   void sel(bool=false,int year=2016);
   void read(bool isdata);
   void init();
   float getEffArea(float eta,int year);
   
   int     ID;
   
   int     fakeType;
   
   float   E_preCorr;
   float   pt_preCorr;
   
   bool    isLooseCBId;
   bool    isMediumCBId;
   bool    isLoose;
   bool    isLoose80;
   bool    isMedium;
   bool    isTight;
   bool    isLooseMVA;
   bool    isTightMVA;
   
   float   dxy;
   float   dz;
   float   sip3d;
   float   ooEmooP;
   float   miniIso;
   float   PFRelIso04; //renamed
   int     nlosthits;
   bool    passCV;
   bool    passPtEta;
   float   ip3d;
   float   ip3dErr;
   bool    passTightCharge;
   bool    cutEventSel;
   bool    noLostHits;
   
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
   
   bool passChargeFlip;
   bool hasMatchedConversion;
   int isGsfCtfScPixChargeConsistent;
   int isGsfScPixChargeConsistent;
   
   float sigmaIetaIeta;
   float hadronicOverEm;
   float correctedEcalEnergy;
   float ecalEnergy;
   float eSuperClusterOverP;
   float deltaEtaSuperClusterTrackAtVtx;
   float deltaPhiSuperClusterTrackAtVtx;
   float see;
   float superCluster_eta;
   
   float trackMomentumError;
   float mvaIso;
   float mvaNoIso;
   
   bool passMuOverlap;
   bool passConditions;
   
   float genConv_pt;
   float genConv_eta;
   float genConv_phi;
   float genConv_m;
   float genConv_E;
   int genConv_status;
   int genConv_id;
   float genConv_dr;
   
   ClassDef(ElectronExt,1)
};

#endif
