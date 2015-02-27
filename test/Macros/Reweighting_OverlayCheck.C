#include "TFile.h"
#include "TH1F"
#include <iostream>

#include "plotHistsAndRatio.C"

/*
 * Quick Macro to Overlay Two Histograms
 * First One is Plotted in Blue
 * Second One is Plotted in Red
 */
TH1F * DrawOverflowBin(TH1F * h);

const char* root_direct_name = "../LNuAA_SM_LHEFTreeLoop.root";
const char* hist_direct_name = "h1_LNuAA_SM_PhoLeadPt_Weighted";

//const char* root_direct_name = "../LNuAA_LM3_500_LHEFTreeLoop.root";
//const char* hist_direct_name = "h1_LNuAA_LM3_500_PhoLeadPt_Weighted";

const char* root_reweight_name = "../LNuAA_LM3_Reweight_Histograms.root";
const char* hist_reweight_name = "h1PhoLeadPt_Weight2";
//const char* hist_reweight_name = "h1PhoLeadPt_Weight4";


//const char* hist_SM_Name = "h1_LNuAA_SM_1.0e-8_PhoLeadPtWeighted";
//const char* hist_aQGC_Name = "h1_LNuAA_FM3_5.0e-10_PhoLeadPtWeighted";

void Reweighting_OverlayCheck(){
 
  TFile * root_direct = TFile::Open(root_direct_name, "READ");
  TH1F * histDirect = root_direct->Get(hist_direct_name);
  TH1F * histDirect_Overflow=DrawOverflowBin(histDirect);
  
  histDirect_Overflow->SetLineColor(kBlue);
  //gStyle->SetOptStat(0);
  histDirect_Overflow->SetTitle("Comparison of Reweighted to Direct");
  //histDirect->GetXaxis()->SetTitle("Lead Photon Pt");
  //histDirect->GetYaxis()->SetTitle("Weighted Counts");
  //histDirect->Draw();
  //histDirect_Overflow->Draw();

  
  TFile * root_reweight = TFile::Open(root_reweight_name, "READ");
  TH1F * histReweight = root_reweight->Get(hist_reweight_name);
  TH1F * histReweight_Overflow=DrawOverflowBin(histReweight);
  
  histReweight_Overflow->SetLineColor(kRed);
  //histReweight_Overflow->Draw("same");  
  //rootFile->Close();

  plotHistsAndRatio(histReweight_Overflow, histDirect_Overflow, 
		    "Comparison of Reweighted to Direct for SM",
		    "Lead Photon Pt", "Weighted Events");

}


TH1F * DrawOverflowBin(TH1F * h)
{
  // This function paint the histogram h with an extra bin for overflows                                                                               
  
  UInt_t nx = h->GetNbinsX()+1;
  Double_t *xbins= new Double_t[nx+1];
  for (UInt_t i=0;i<nx;i++){
    xbins[i]=h->GetBinLowEdge(i+1);
  }
  xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
  
  //char *tempName= new char[strlen(h->GetName())+10];
  //sprintf(tempName,"%swtOverFlow",h->GetName());
  
  stringstream tempName;
  tempName << h->GetName() << "wtOverFlow";
  // Book a temporary histogram having ab extra bin for overflows                                                                                      
  TH1F *htmp = new TH1F(tempName.str().c_str(), h->GetTitle(), nx, xbins);
  
  // Reset the axis labels                                                                                                                             
  htmp->SetXTitle(h->GetXaxis()->GetTitle());
  htmp->SetYTitle(h->GetYaxis()->GetTitle());
  
  // Fill the new hitogram including the extra bin for overflows                                                                                       
  for (UInt_t i=1; i<=nx; i++){
    htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
    htmp->SetBinError(i, h->GetBinError(i));
  }
  //htmp->Draw();
  // Fill the underflows                                                                                                                               
  //htmp->Fill(h->GetBinLowEdge(1)-1, h->GetBinContent(0));                                                                                            
  // Restore the number of entries                                                                                                                       
 
  htmp->SetEntries(h->GetEntries());
   /*
  // FillStyle and color                                                                                                                               
  htmp->SetFillStyle(h->GetFillStyle());
  htmp->SetFillColor(h->GetFillColor());
  */
  return htmp;                          
  //return h;
}
