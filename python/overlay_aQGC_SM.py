from ROOT import TFile
from ROOT import TH1F
from ROOT import TCanvas
from ROOT import TLegend
from ROOT import TStyle
from array import array
import sys

histCompareName = ""
if __name__=="__main__":
        histCompareName = sys.argv[1]

inRootFileLoc = "../test/RootFiles/LNuAA_aQGC_Histograms/aQGC_LHEFTreeLoop.root"
inRootFile = TFile(inRootFileLoc, 'READ')

suffix=histCompareName.strip("h1_LNuAA_")
identifier = suffix.rstrip("_PhoLeadPt_Weighted")

outRootFileDir = '../test/RootFiles/LNuAA_aQGC_Histograms/'
outRootFileName = 'overlay_SM_'+identifier+'.root'
outRootFileLoc = outRootFileDir + outRootFileName
outRootFile = TFile(outRootFileLoc, 'RECREATE')


#h1PhoPt_SM = TH1F()
h1PhoPt_SM = inRootFile.Get("h1_LNuAA_SM_0.0_PhoLeadPt_Weighted")
h1PhoPt_SM.Write()

#h1PhoPt_Compare = TH1F()
h1PhoPt_Compare = inRootFile.Get(histCompareName)
h1PhoPt_Compare.Write()

c1 = TCanvas()
c1.cd()

h1PhoPt_SM.SetTitle("SM vs " + identifier)
h1PhoPt_SM.Draw()
#gStyle.SetOptStat(0)

h1PhoPt_Compare.SetLineColor(2) #Red
h1PhoPt_Compare.Draw("same")
c1.Write()
#gStyle.SetOptStat(0)

#leg = TLegend(0.6, 0.6, 0.9, 0.9)
#leg.AddEntry(h1PhoPt_SM, "SM", "SM")
#leg.AddEntry(h1PhoPt_Compare, identifier, identifier)
#leg.Draw("same")


