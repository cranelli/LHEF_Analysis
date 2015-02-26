#ifndef __REWEIGHT_EDMTOROOTTREE_H__
#define __REWEIGHT_EDMTOROOTTREE_H__

// -*- C++ -*-
//
// Package:    Reweight_EDOtoRootTree
// Class:      Reweight_EDOtoRootTree
// 
/**\class Reweight_EDOtoRootTree Reweight_EDOtoRootTree.cc Anomalous_QGC/Reweighting/src/Reweight_EDMtoRootTree.cc

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


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//TFileService
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


// Event Data Classes                                                                                     
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LesHouches.h"

//Root Library
#include <TTree.h>

//Standard Library
#include <vector>

using namespace::std;

//Custom Structures

struct Basic_LHE{
  int numParticles;
  vector<int> pdgIds;
  vector<int> firstMother;
  vector<int> lastMother;
  vector<float> Px;
  vector<float> Py;
  vector<float> Pz;
  vector<float> E;
  vector<float> M;
};

struct More_Kinematics{
  vector<float> Pt;
  vector<float> Eta;
  vector<float> Phi;
  vector<float> Et;
};


//
// class declaration
//

class Reweight_EDMtoRootTree : public edm::EDAnalyzer {
   public:
      explicit Reweight_EDMtoRootTree(const edm::ParameterSet&);
      ~Reweight_EDMtoRootTree();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

  edm::Service<TFileService> _fileService;
  
  edm::InputTag _lheEventInput;

  TTree *lnuaa_tree;
  Basic_LHE basic_lhe;
  More_Kinematics more_kinematics;
  vector<double> weights;
  //std::vector<int> pdgIds;
  //double weight;
  void initializeBranches();

};

#endif
