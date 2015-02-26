from ROOT import TFile
from ROOT import TH1F
from array import array
import sys

histCompareName = ""
if __name__=="__main__":
        histCompareName = sys.argv[1]

lastPt = 200 # 200 GeV should be in the last bin.
inRootFileLoc = "../test/RootFiles/LNuAA_aQGC_Histograms/aQGC_LHEFTreeLoop.root"

inRootFile = TFile(inRootFileLoc, 'READ')

binLowEdges = [0, 15, 25, 40, 80, 400]
numbins = 5

#h1PhoPt_SM = TH1F()
h1PhoPt_SM = inRootFile.Get("h1_LNuAA_SM_0.0_PhoLeadPt_Weighted")
h1PhoPt_SM_Rebinned = h1PhoPt_SM.Rebin(numbins,
				    "h1_LNuAA_SM_0.0_PhoLeadPt_Weighted_Rebin",
				    array('d',binLowEdges))
#h1PhoPt_Compare = TH1F()
h1PhoPt_Compare = inRootFile.Get(histCompareName)
h1PhoPt_Compare_Rebinned = h1PhoPt_Compare.Rebin(numbins,
						    histCompareName+"_Rebin",
						    array('d',binLowEdges))
						    
#h1PhoPt_Compare_Rebinned.Draw()

lastPt_SM = h1PhoPt_SM_Rebinned.GetBinContent(h1PhoPt_SM_Rebinned.FindBin(lastPt))  

#print lastPtBinSize_SM
lastPt_Compare = h1PhoPt_Compare_Rebinned.GetBinContent(h1PhoPt_Compare_Rebinned.FindBin(lastPt))  

#print lastPtBinSize_Compare

#print "Ratio: ", lastPtBinSize_Compare/lastPtBinSize_SM
print lastPt_Compare/lastPt_SM
