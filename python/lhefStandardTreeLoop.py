from ROOT import gSystem
from ROOT import TFile
from ROOT import TTree
from ROOT import TDirectory, gDirectory
from ROOT import TLorentzVector
from ROOT import TH1F, TH2F
from ROOT import TBranchElement
from math import sqrt, cos
from array import array
import sys
import histogramBuilder
from string import rsplit

from array import array


inRootFileLoc = ""
if __name__=="__main__":
    inRootFileLoc = sys.argv[1]

# Define Root File Locations and Names
#inRootFileDir = '../test/RootFiles/AnomalousCouplings/'
#inRootFileName = "/LNuAA_LM3_1e-9.root"
#prefix = "SM_1e-9"
inRootFileName = inRootFileLoc.rsplit('/',1)[1]
prefix = inRootFileName.rstrip('.root')
print prefix


TREENAME = "LHEF"

outRootFileDir = '../test/'
outRootFileName = prefix+'_LHEFTreeLoop.root'


# Load needed LHEF Libraries 
gSystem.Load( 'ExRootClasses_cc.so')
from ROOT import TSortableObject
from ROOT import TRootLHEFEvent
from ROOT import TRootLHEFParticle


# Begining of Script
#inRootFileLoc = inRootFileDir + inRootFileName
inRootFile = TFile(inRootFileLoc, "READ")
# Set Histograms
#binLowEdge = [0, 15, 25, 40, 80, 400]
#h1PhoLeadPtWeighted = TH1F("h1"+prefix+"_PhoLeadPt_Weighted", prefix + "Lead Photon Pt", 5,array('d', binLowEdge))

#h1PhoLeadPt = TH1F("h1"+prefix+"PhoLeadPt", prefix + "Lead Photon Pt", 400, 0, 200)
bins = 4
binLowE = [15,25,40,70,200]
h1PhoLeadPtWeighted = TH1F("h1_" + prefix + "_PhoLeadPt_Weighted", prefix +"Lead Photon Pt Weighted",
                           bins, array('d',binLowE))
h1PhoLeadPtWeighted.Sumw2()
#h1Mt = TH1F("h1"+prefix+"Mt", prefix + "Transverse Mass LV", 20, 0, 100)

analysis_tree = inRootFile.Get(TREENAME)
print "Tree ", analysis_tree

num_entries = analysis_tree.GetEntries()
print "Number of Entries: ", num_entries

for entry in xrange(num_entries):
    analysis_tree.GetEntry(entry)
    #print analysis_tree.__dict__

    # Select Event, should be only one per entry.
    event = analysis_tree.Event[0]
    weight = event.Weight
    
    #num_particles = analysis_tree.Particle.GetEntries()
    
    photons = []
    ele = None
    muon = None
    lep = None
    nu_e = None
    nu_m = None
    nu = None
    w = None
    nu = None
    #for particleIndex in xrange(num_particles):
    particles = analysis_tree.Particle
    for particle in particles:
        if particle.PID == 22: photons.append(particle)
        #if particle.PID == 11 or particle.PID == -11: print particle.PID; print "lepton"
        if abs(particle.PID) == 11: ele = particle; lep = particle
        if abs(particle.PID) == 13: muon = particle; lep = particle
        if abs(particle.PID) == 12: nu_e = particle; nu = particle
        if abs(particle.PID) == 14: nu_m = particle; nu = particle
        if abs(particle.PID) == 24: w = particle
    #
    # Analyze Photons
    #

    photonPts = []
    for photon in photons:    
        photonPts.append(photon.PT)
        
    # Make Histogram of Lead Photon Pt

    #h1PhoLeadPt.Fill(max(photonPts))
    #print event.Weight;
    h1PhoLeadPtWeighted.Fill(max(photonPts), weight);

    #
    # Analyze Leptons and Neutrinos
    #
    #lepLV = TLorentzVector(lep.Px, lep.Py, lep.Pz, lep.E)
    #nuLV = TLorentzVector(nu.Px, nu.Py, nu.Pz, nu.E)
    #Mt2 = 2*lepLV.Et()*nuLV.Et()*(1-cos(lepLV.DeltaPhi(nuLV)))
    #Mt = sqrt(Mt2)
    #h1Mt.Fill(Mt, weight)
    
outRootFileLoc = outRootFileDir + outRootFileName
outRootFile = TFile(outRootFileLoc, 'RECREATE')
outRootFile.cd() 
#outRootFile.Write #Does not seem to have anything in memmory.
#h1PhoLeadPt.Draw()
#h1PhoLeadPt.Write()
h1PhoLeadPtWeighted.GetXaxis().SetTitle("Lead Photon Pt (GeV)")
h1PhoLeadPtWeighted.GetYaxis().SetTitle("Weighted Counts")
h1PhoLeadPtWeighted.Write()
#h1Mt.Write()

inRootFile.Close()
outRootFile.Close()
    


