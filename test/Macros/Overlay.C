#include "TFile.h"
#include "TH1F"
#include <iostream>
#include "AddOverFlow.C"
#include "plotHistsAndRatio.C"

/*
 * Quick Macro to Overlay Two Histograms
 * First One is Plotted in Blue
 * Second One is Plotted in Red
 */


const char* rootName = "../LNuAA_LM3_Reweight_Histograms.root";
const char* hist_Weight0_Name = "h1PhoLeadPt_Weight0";
const char* hist_Weight1_Name = "h1PhoLeadPt_Weight1";
const char* hist_Weight2_Name = "h1PhoLeadPt_Weight2";
const char* hist_Weight3_Name = "h1PhoLeadPt_Weight3";
const char* hist_Weight4_Name = "h1PhoLeadPt_Weight4";

//const char* hist_SM_Name = "h1_LNuAA_SM_1.0e-8_PhoLeadPtWeighted";
//const char* hist_aQGC_Name = "h1_LNuAA_FM3_5.0e-10_PhoLeadPtWeighted";

void Overlay(){
  TFile * rootFile = TFile::Open(rootName, "READ");


  TH1F * hist_Weight2 = rootFile->Get(hist_Weight2_Name);  
  TH1F * histWeight2_Overflow;
  hist_Weight2_Overflow= DrawOverflowBin(hist_Weight2);
  gStyle->SetOptStat(0);
  hist_Weight2_Overflow->SetTitle("Comparison of Lead Photon Pt Reweighted to Different aQGCs");
  hist_Weight2_Overflow->GetXaxis()->SetTitle("Lead Photon Pt");
  hist_Weight2_Overflow->GetYaxis()->SetTitle("Weighted Counts");
  hist_Weight2_Overflow->SetLineColor(kBlack);
  hist_Weight2_Overflow->Draw();

  TH1F * hist_Weight3 = rootFile->Get(hist_Weight3_Name);  
  TH1F * histWeight3_Overflow;
  hist_Weight3_Overflow= DrawOverflowBin(hist_Weight3);
  hist_Weight3_Overflow->SetLineColor(kBlue);
  hist_Weight3_Overflow->Draw("same");

  TH1F * hist_Weight4 = rootFile->Get(hist_Weight4_Name);
  TH1F * histWeight4_Overflow;
  hist_Weight4_Overflow= DrawOverflowBin(hist_Weight4);
  hist_Weight4_Overflow->SetLineColor(kRed);
  hist_Weight4_Overflow->Draw("same");
  // hist_Weight4_Overflow->Draw("same");
  //plotHistsAndRatio(hist_Weight4_Overflow, hist_Weight2_Overflow, 
  //	    "Comparison of Reweighted aQGC LM3=500 to LM3=0",
  //	    "Lead Photon Pt", "Weighted Events");
  //plotHistsAndRatio(hist_Weight3_Overflow, hist_Weight2_Overflow, 
  //		    "Comparison of Reweighted aQGC LM3=50 to LM3=0",
  //	    "Lead Photon Pt", "Weighted Events");

  
  TH1F * hist_Weight0 = rootFile->Get(hist_Weight0_Name);
  TH1F * histWeight0_Overflow;
  hist_Weight0_Overflow= DrawOverflowBin(hist_Weight0);
  hist_Weight0_Overflow->SetLineColor(kGreen);
  hist_Weight0_Overflow->Draw("same");
  

  TH1F * hist_Weight1 = rootFile->Get(hist_Weight1_Name);
  TH1F * histWeight1_Overflow;
  hist_Weight1_Overflow= DrawOverflowBin(hist_Weight1);
  hist_Weight1_Overflow->SetLineColor(kYellow);
  hist_Weight1_Overflow->Draw("same");  


  leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(hist_Weight0_Overflow,"LM3=-500");
  leg->AddEntry(hist_Weight1_Overflow,"LM3=-50");
  leg->AddEntry(hist_Weight2_Overflow,"LM3=0");
  leg->AddEntry(hist_Weight3_Overflow,"LM3=50");
  leg->AddEntry(hist_Weight4_Overflow,"LM3=500");
  leg->Draw();

  //rootFile->Close();
}
