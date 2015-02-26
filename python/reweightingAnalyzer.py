from ROOT import gSystem
from ROOT import TFile
from ROOT import TTree
from ROOT import TDirectory, gDirectory
from ROOT import TLorentzVector
from ROOT import TH1F, TH2F
from ROOT import TBranchElement
from math import sqrt, cos
from array import array

#import sys
#My Own Helper Modules
import particleIdentification
import histogramBuilder

#
# Define Root Files and Tree Locations and Names
#

num_weights=5

workDirLoc = '/home/cranelli/WGamGam/Anomolous_QGC/CMSSW_5_3_12/src/Anomolous_QGC/Analysis/python/'
inRootFileDir = '../test/'
inRootFileName = 'LNuAA_LM3_Reweight_Tree.root'
#inRootFileDir = '/data/users/cranelli/WGamGam/SignalTruth'
#inRootFileName = "/signaltruth_job_summer12_WAA_ISR.root"
treeLoc = "ntuple/lnuaa_tree"
outRootFileLoc = '../test/LNuAA_LM3_Reweight_Histograms.root'
#print sys.path

#
# Begining of Analysis Code
#

def reweightingAnalyzer():

    outRootFile = TFile(outRootFileLoc, 'RECREATE')
    inRootFileLoc = inRootFileDir + inRootFileName
    inRootFile = TFile(inRootFileLoc, "READ")
    
    analysis_tree = inRootFile.Get(treeLoc)
    print "Tree ", analysis_tree
    
    num_entries = analysis_tree.GetEntries()
    print "Number of Entries: ", num_entries

    # Create Histograms for each Weight
    bins = 4
    binLowE = [15,25,40,70,200]
    for weight_index in range(0,num_weights):
        # Set Histograms
        h1PhoLeadPt = TH1F("h1PhoLeadPt_Weight"+str(weight_index), "Lead Photon Pt Weight "+ str(weight_index), bins,array('d',binLowE))
        h1PhoLeadPt.Sumw2()
        # h1DiPhoM = TH1F("DiPhoM", "DiPhoton Mass", 800, 0, 400)
    
        #
        # Loop Over Entries
        #
        for entry in xrange(num_entries):
            analysis_tree.GetEntry(entry)
            # print analysis_tree.__dict__

            #Assign Weights
            weight = analysis_tree.weights[weight_index]
        
            # Assign Particles
            # Will be filled with TLorentz Vector, for now.
            photons = []
            electrons = []
            muons = []
            nu_es = []
            nu_ms = []
            ws = []
            #
            # Particle Identification
            #
            particleIdentification.assignParticles(analysis_tree, photons, electrons, muons, nu_es, nu_ms, ws)    
            leptons = electrons + muons
            nus = nu_es + nu_ms
            
            leadPhoton = selectLead(photons)
            # lepton = selectLead(leptons) # Have signal electron be the one with highest Pt 
            # nu = selectLead(nus)
            # subPhoton = selectSub(photons)
            
            if leadPhoton != None :
                h1PhoLeadPt.Fill(leadPhoton.Pt(),weight)
                # for weight_index in range(0, num_weights):
                # h1PhoLeadPt_Weight=TH1F();
                # h1PhoLeadPt_Weight=inRootFile.Get("h1PhoLeadPt_Weight"+str(weight_index));
                # h1PhoLeadEta.Fill(leadPhoton.Eta())
            
                """
                if leadPhoton != None and subPhoton != None and lepton != None and nu != None:
                m3 = (leadPhoton + lepton + nu).M() #Does not include sub leading lepton
                m4 = (leadPhoton + subPhoton + lepton +nu).M()
                h2M3M4.Fill(m3, m4)
                """
            
    
        # outRootFile.Write #Does not seem to have anything in memmory.
        outRootFile.cd()
        h1PhoLeadPt.Write()
        # h1PhoLeadEta.Write()

    # Difference of Weights
    # Set Histograms
    #h1PhoLeadPtWeightDif = TH1F("h1PhoLeadPt_WeightDif_32", "Lead Photon Pt Weight 3-2", bins,array('d',binLowE))
    #h1PhoLeadPtWeightDif.Sumw2()
    # h1DiPhoM = TH1F("DiPhoM", "DiPhoton Mass", 800, 0, 400)
    

    #Iterate Over Selection Histograms
    #for key, Histogram in histogramBuilder.Histograms.iteritems():
    #    Histogram.Write()

    #h2M3M4.Write()
    inRootFile.Close()
    outRootFile.Close()

def selectLead(particles):
    maxPt = 0
    lead = None
    for particle in particles:
        if particle.Pt() > maxPt :
            maxPt = particle.Pt()
            lead =  particle
    return lead

def selectSub(particles):
    maxPt = 0
    lead = None
    sub = None
    for particle in particles:
        if particle.Pt() > maxPt:
            maxPt = particle.Pt()
            sub = lead
            lead = particle
        
    return sub

if __name__=="__main__":
    reweightingAnalyzer()
    


