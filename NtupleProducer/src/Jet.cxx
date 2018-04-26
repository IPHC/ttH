#include "include/NtupleProducer.h"
#include <iostream>
#include <iomanip>

ClassImp(Jet)

Jet::Jet()
{
}

Jet::~Jet()
{
}

void Jet::read(bool isdata)
{
    _ID = idx;

    // general informations
    if( CHECK(ntP->jet_E)       )       _E          = ntP->jet_E->at(idx);
    if( CHECK(ntP->jet_pt)      )       _pt         = ntP->jet_pt->at(idx);
    if( CHECK(ntP->jet_eta)     )       _eta        = ntP->jet_eta->at(idx);   
    if( CHECK(ntP->jet_phi)     )       _phi        = ntP->jet_phi->at(idx);   
    if( CHECK(ntP->jet_m)       )       _m          = ntP->jet_m->at(idx);
    if( CHECK(ntP->jet_qgtag)   )       _qg         = ntP->jet_qgtag->at(idx);


    // selection variables
    if( CHECK(ntP->jet_tightJetID) )    _tightJetID    = ntP->jet_tightJetID->at(idx);

    // other variables
    if ( CHECK(ntP->jet_ntrk)    )          _ntrk           = ntP->jet_ntrk->at(idx);
    if ( CHECK(ntP->jet_CSVv2)   )          _CSVv2          = ntP->jet_CSVv2->at(idx);
    if ( CHECK(ntP->jet_cMVAv2)  )          _cMVAv2         = ntP->jet_cMVAv2->at(idx);
    if ( CHECK(ntP->jet_DeepCSVProbudsg) )  _deepCSVudsg    = ntP->jet_DeepCSVProbudsg->at(idx);
    if ( CHECK(ntP->jet_DeepCSVProbb) )     _deepCSVb       = ntP->jet_DeepCSVProbb->at(idx);
    if ( CHECK(ntP->jet_DeepCSVProbbb) )    _deepCSVbb      = ntP->jet_DeepCSVProbbb->at(idx);
    if ( CHECK(ntP->jet_DeepCSVProbc) )     _deepCSVc       = ntP->jet_DeepCSVProbc->at(idx);
    if ( CHECK(ntP->jet_DeepCSVProbcc) )    _deepCSVcc      = ntP->jet_DeepCSVProbcc->at(idx);

    // Gen Jets variables

    if (!isdata)
    {
        _jet_partonFlavour    = ntP->jet_partonFlavour->at(idx);
        _jet_hadronFlavour    = ntP->jet_hadronFlavour->at(idx);
        _jet_genJet_pt        = ntP->jet_genJet_pt->at(idx); 
        _jet_genJet_E         = ntP->jet_genJet_E->at(idx);
        _jet_genParton_pt     = ntP->jet_genParton_pt->at(idx);
        _jet_genParton_id     = ntP->jet_genParton_id ->at(idx);
        _jet_genParton_E      = ntP->jet_genParton_E->at(idx);      
    }
    
    JECUncertainty();

}

void Jet::init()
{
    //general information
    _E       = -100.;
    _pt      = -100.;
    _eta     = -100.;
    _phi     = -100.;
    _m       = -100.;
    _qg      = -100.;

    // selection variables
    _tightJetID = 0;

    // other variables
    _ntrk           = -100;
    _CSVv2          = -100.;
    _cMVAv2         = -100.;

    _deepCSV        = -100.;
    _deepCSVudsg    = -100.;
    _deepCSVb       = -100.;
    _deepCSVbb      = -100.;
    _deepCSVc       = -100.;
    _deepCSVcc      = -100.;

    // Gen Jet variables
    _jet_partonFlavour    = -100.;
    _jet_hadronFlavour    = -100.;
    _jet_genJet_pt        = -100.;
    _jet_genParton_pt     = -100.;
    _jet_genParton_id     = -100.; 
    _jet_genJet_E         = -100.;
    _jet_genParton_E      = -100.; 
    
    _JES_uncert           = 0.;
    _pt_JER               = 0.;
    _pt_JER_down          = 0.;
    _pt_JER_up            = 0.;
}


bool Jet::sel()
{
    // selection
   bool pass_pt      = (_pt > 25.);
   bool pass_eta     = (fabs(_eta) < 2.4);
   bool pass_tightJetID = (_tightJetID);

/*   float pileupJetId = ntP->jet_pileupJetId->at(idx);
   
   if( fabs(_eta) >= 0 && fabs(_eta) < 2.5 )
     if( pileupJetId > -0.63 ) pass_jetId = 1;
   else if( fabs(_eta) >= 2.5 && fabs(_eta) < 2.75 )
     if( pileupJetId > -0.60 ) pass_jetId = 1;
   else if( fabs(_eta) >= 2.75 && fabs(_eta) < 3.0 )
     if( pileupJetId > -0.55 ) pass_jetId = 1;
   else if( fabs(_eta) >= 3.0 && fabs(_eta) < 5.2 )
     if( pileupJetId > -0.45 ) pass_jetId = 1;*/
   
    bool pass_muOverlap = 1;
    int nMuon = nt->NtMuon->size();
    for(int im=0;im<nMuon;im++)
    {
        float dr = GetDeltaR(_eta,_phi,nt->NtMuon->at(im).eta(),nt->NtMuon->at(im).phi());
        if( dr < 0.4 && nt->NtMuon->at(im).pt() > 10. && nt->NtMuon->at(im).isFakeableTTH() ) pass_muOverlap = 0;
    }  

    bool pass_elOverlap = 1;
    int nElectron = nt->NtElectron->size();
    for(int ie=0;ie<nElectron;ie++)
    {
        float dr = GetDeltaR(_eta,_phi,nt->NtElectron->at(ie).eta(),nt->NtElectron->at(ie).phi());
        if( dr < 0.4 && nt->NtElectron->at(ie).pt() > 10. && nt->NtElectron->at(ie).isFakeableTTH() ) pass_elOverlap = 0;
    }

    bool pass_tauOverlap = 1;
    int nTau = nt->NtTau->size();
    for(int it=0;it<nTau;it++)
    {
        float dr = GetDeltaR(_eta,_phi,nt->NtTau->at(it).eta(),nt->NtTau->at(it).phi());
        if( dr < 0.4 && nt->NtTau->at(it).pt() > 10. ) 
        {
            pass_tauOverlap = 0; //&& nt->NtTau->at(it).isTight() ) pass_tauOverlap = 0;
            //std::cout << nt->NtTau->at(it).pt() << std::endl;
        }
    }

    bool isSelectionJet = ( pass_pt         &&
                            pass_eta        &&
                            pass_tightJetID &&
                            pass_muOverlap  &&
                            pass_elOverlap  &&
                            pass_tauOverlap 
                          );

    // synchronization printout
    if( false ) std::cout
    //if( isSelectionJet) std::cout
                            << nt->NtEvent->at(0).id()          << " "
                            << _pt                              << " "
                            << _eta                             << " "
                            << _phi                             << " "
                            << _tightJetID                      << " "
                            << _E                               << " "
                            << pass_muOverlap                   << " "
                            << pass_elOverlap                   << " "
                            << pass_tauOverlap
                            << std::endl;

    return isSelectionJet;
}

void Jet::setJESUncertainty(float JES_uncert)
{
  _JES_uncert = JES_uncert;
}

void Jet::JECUncertainty()
{  
   // JER taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
   
   double _cJER[5];
   double _cJER_down[5];
   double _cJER_up[5];

   _cJER[0] = 1.052; // 0.0-0.5
   _cJER[1] = 1.057; // 0.5-1.1
   _cJER[2] = 1.096; // 1.1-1.7
   _cJER[3] = 1.134; // 1.7-2.3
   _cJER[4] = 1.288; // 2.3-5.0
   
   _cJER_down[0] = 0.990;
   _cJER_down[1] = 1.001;
   _cJER_down[2] = 1.032;
   _cJER_down[3] = 1.042;
   _cJER_down[4] = 1.089;

   _cJER_up[0] = 1.115;
   _cJER_up[1] = 1.114;
   _cJER_up[2] = 1.161;
   _cJER_up[3] = 1.228;
   _cJER_up[4] = 1.488;
   
   int etaIdx = -1;
   if( fabs(_eta) >= 0.  && fabs(_eta) < 0.5 ) etaIdx = 0;
   if( fabs(_eta) >= 0.5 && fabs(_eta) < 1.1 ) etaIdx = 1;
   if( fabs(_eta) >= 1.1 && fabs(_eta) < 1.7 ) etaIdx = 2;
   if( fabs(_eta) >= 1.7 && fabs(_eta) < 2.3 ) etaIdx = 3;
   if( fabs(_eta) >= 2.3 && fabs(_eta) < 5.0 ) etaIdx = 4;	

   double pt_uncorr = (_pt - _jet_genJet_pt) / _cJER[etaIdx] + _jet_genJet_pt;
  
   _pt_JER	= _jet_genJet_pt + _cJER[etaIdx]*(pt_uncorr-_jet_genJet_pt);
   _pt_JER_down = _jet_genJet_pt + _cJER_down[etaIdx]*(pt_uncorr-_jet_genJet_pt);
   _pt_JER_up   = _jet_genJet_pt + _cJER_up[etaIdx]*(pt_uncorr-_jet_genJet_pt);
		    
}
