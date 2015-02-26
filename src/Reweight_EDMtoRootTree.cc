// -*- C++ -*-
//
// Package:    Reweight_EDMtoRootTree
// Class:      Reweight_EDMtoRootTree
// 
/**\class Reweight_EDMtoRootTree Reweight_EDMtoRootTree.cc Anomalous_QGC/Reweighting/src/Reweight_EDMtoRootTree.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Christopher Anelli
//         Created:  Thu Sep 11 09:38:41 EDT 2014
// $Id$
//
//

//Reweight_EDMtoRootTree header file
#include  "aQGC/LHEF_Analysis/interface/Reweight_EDMtoRootTree.h"

// Event Data Classes
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LesHouches.h"

//Root
#include "TLorentzVector.h"
#include "TVector3.h"

//Standard Library
#include <iostream>
#include "math.h"
#include <vector>

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

using namespace::std;

Reweight_EDMtoRootTree::Reweight_EDMtoRootTree(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
  
  _lheEventInput = iConfig.getParameter<edm::InputTag>("lheEventSrc");
  cout << _lheEventInput << endl;
  
  lnuaa_tree = _fileService->make<TTree>("lnuaa_tree", "Generator Data from Madgraph");
  initializeBranches();
}


Reweight_EDMtoRootTree::~Reweight_EDMtoRootTree()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Reweight_EDMtoRootTree::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // Clear any old data
   weights.clear();

   basic_lhe.numParticles=0;
   basic_lhe.pdgIds.clear();
   basic_lhe.firstMother.clear();
   basic_lhe.lastMother.clear();
   basic_lhe.Px.clear();
   basic_lhe.Py.clear();
   basic_lhe.Pz.clear();
   basic_lhe.E.clear();
   basic_lhe.M.clear();


   more_kinematics.Pt.clear();
   more_kinematics.Eta.clear();
   more_kinematics.Phi.clear();
   more_kinematics.Et.clear();


   // Get Event Data and Setup   

   Handle<LHEEventProduct> lheEvent;
   iEvent.getByLabel(_lheEventInput,lheEvent);

   //weights
   for(unsigned int i=0; i< lheEvent->weights().size(); i++){
     weights.push_back(lheEvent->weights().at(i).wgt);
   }

   //lhef::HEPEUP hepeup = lheEvent->hepeup();
   basic_lhe.numParticles = lheEvent->hepeup().NUP;
   basic_lhe.pdgIds = lheEvent->hepeup().IDUP;
   
   vector<pair<int,int>> mothers = lheEvent->hepeup().MOTHUP;
   for(unsigned int i=0; i < mothers.size(); i++){
     basic_lhe.firstMother.push_back(mothers.at(i).first);
     basic_lhe.lastMother.push_back(mothers.at(i).second);
   }
   //Loop over fiveVectors (Px, Py, Pz, E, M)
   vector<lhef::HEPEUP::FiveVector> fiveVectors = lheEvent->hepeup().PUP;
   for(unsigned int i =0; i < fiveVectors.size(); i++){
     //float px, py, pz, e ,m;
     double px, py, pz, e, m, pt, eta, phi, et;
     px = fiveVectors.at(i)[0];
     py = fiveVectors.at(i)[1];
     pz = fiveVectors.at(i)[2];
     e = fiveVectors.at(i)[3];
     m = fiveVectors.at(i)[4];
     
     TLorentzVector * fourVector = new TLorentzVector(px, py, pz, e);
     pt = fourVector->Pt();
     //cout << "Pt: "<< pt << endl;
     //cout << "Pz: " << pz << endl;
     //Handle Case where Pt = 0;
     if(fabs(pt) > 1e-3) {
       eta = fourVector->Eta();
     } else {
       if(pz>0) eta = 1000;
       else eta = -1000;
     }
     //cout << "Eta: " << eta << endl;
     phi = fourVector->Phi();
     et = fourVector->Et();
     
     basic_lhe.Px.push_back(px);
     basic_lhe.Py.push_back(py);
     basic_lhe.Pz.push_back(pz);
     basic_lhe.E.push_back(e);
     basic_lhe.M.push_back(m);
    
     more_kinematics.Pt.push_back(pt);
     more_kinematics.Eta.push_back(eta);
     more_kinematics.Phi.push_back(phi);
     more_kinematics.Et.push_back(et);
     
   }
   
 
   /*
   //Print Outs
   std::cout << numParticles << std::endl;
   for(unsigned int i=0; i < basic_lhe.pdgIds.size(); i++){
     std::cout << basic_lhe.pdgIds.at(i) << " ";
   }
   std::cout << endl;

   for( unsigned int i =0; i < fiveVectors.size(); i++){
     for(unsigned int j=0; j < 5; j++){
       std::cout << fiveVectors[i][j] << " ";
     }
     std::cout << std::endl;
   }
   */

   /*
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
   */
   
   lnuaa_tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
Reweight_EDMtoRootTree::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Reweight_EDMtoRootTree::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
Reweight_EDMtoRootTree::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
Reweight_EDMtoRootTree::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
Reweight_EDMtoRootTree::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
Reweight_EDMtoRootTree::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Reweight_EDMtoRootTree::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void Reweight_EDMtoRootTree::initializeBranches(){

  //Generator                                                      
  lnuaa_tree->Branch("nMC", &basic_lhe.numParticles);
  lnuaa_tree->Branch("mcPID",&basic_lhe.pdgIds);
  lnuaa_tree->Branch("firstMother",&basic_lhe.firstMother);
  lnuaa_tree->Branch("lastMother",&basic_lhe.lastMother);

  lnuaa_tree->Branch("mcPx", &basic_lhe.Px);
  lnuaa_tree->Branch("mcPy", &basic_lhe.Py);
  lnuaa_tree->Branch("mcPz", &basic_lhe.Pz);
  
  lnuaa_tree->Branch("mcPt", &more_kinematics.Pt);
  lnuaa_tree->Branch("mcMass", &basic_lhe.M);
  lnuaa_tree->Branch("mcEta", &more_kinematics.Eta);
  lnuaa_tree->Branch("mcPhi", &more_kinematics.Phi);
  lnuaa_tree->Branch("mcE", &basic_lhe.E);
  lnuaa_tree->Branch("mcEt", &more_kinematics.Et);
  
  lnuaa_tree->Branch("weights", &weights);

}

//define this as a plug-in
DEFINE_FWK_MODULE(Reweight_EDMtoRootTree);
