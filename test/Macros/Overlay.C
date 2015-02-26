#include "TFile.h"
#include "TH1F"
#include <iostream>
#include "AddOverFlow.C"

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
  
  TH1F * histWeight2_Overflow;
  hist_Weight3_Overflow= DrawOverflowBin(hist_Weight3);
  hist_Weight3_Overflow->SetLineColor(kBlue);
  hist_Weight3_Overflow->Draw("same");

  TH1F * hist_Weight4 = rootFile->Get(hist_Weight4_Name);
  TH1F * histWeight4_Overflow;
  hist_Weight4_Overflow= DrawOverflowBin(hist_Weight4);
  hist_Weight4_Overflow->SetLineColor(kRed);
  hist_Weight4_Overflow->Draw("same");
  
  /*
  TH1F * hist_Weight2 = rootFile->Get(hist_Weight2_Name);
  hist_Weight2->SetLineColor(kGreen);
  hist_Weight2->Rebin(80); //Rebin to 40 GeV per bin
  hist_Weight2->Draw("same");

  TH1F * hist_Weight3 = rootFile->Get(hist_Weight3_Name);
  hist_Weight3->SetLineColor(kYellow);
  hist_Weight3->Rebin(80); //Rebin to 40 GeV per bin
  hist_Weight3->Draw("same");
  */

  //rootFile->Close();
}
