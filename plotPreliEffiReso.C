#include "headerfunction.h"

void plotPreliEffiReso(){

  TLegend *legend;
  TLatex *tex;
  TLine *line1,*line2;
  Bool_t success;
  char *name1 = "Run-2";
  char *name2 = "-2.5 < #eta < -1.0";
  char *name3 = "-2.2 < #eta < -1.2 (new)";
  gStyle->SetOptStat("0000");

  //Run2:Org---
  TFile* mFileRun2 = TFile::Open("./run2codes/outputPWNewRecTPCRightEtacut.root","READ");
  TH1F *hPtMCGenHadron1 = (TH1F *) mFileRun2->Get("hMCGenPtFTAll");
  TH1F *hPtMCRecHadron1 = (TH1F *) mFileRun2->Get("hMCRecPtFTAll");
  hPtMCGenHadron1->Sumw2();
  hPtMCRecHadron1->Sumw2();
  TH1D *hEffChRun2 = (TH1D *) hPtMCRecHadron1->Clone("hEffChRun2");
  success = hEffChRun2->Divide(hEffChRun2,hPtMCGenHadron1,1,1,"B");
  
  TFile *mFileVar1 = TFile::Open("outputEffiEta1p2to2p2andPtResNclsCut70vz480cmNewPtBin2.root","READ");
  TH1D *hPtChGenVar1 = (TH1D *) mFileVar1->Get("hPtGenMC");
  TH1D *hPtChRecVar1 = (TH1D *) mFileVar1->Get("hPtRecMC");
  hPtChGenVar1->Sumw2();
  hPtChRecVar1->Sumw2();
  TH1D *hEffChRun3Var1 = (TH1D *) hPtChRecVar1->Clone("hEffChRun3Var1");
  success = hEffChRun3Var1->Divide(hEffChRun3Var1,hPtChGenVar1,1,1,"B");

  
  TFile *mFileVar2 = TFile::Open("outputEffiEta1p2to2p2andPtResNclsCut70vz495cmNewPtBin2.root","READ");
  TH1D *hPtChGenVar2 = (TH1D *) mFileVar2->Get("hPtGenMC");
  TH1D *hPtChRecVar2 = (TH1D *) mFileVar2->Get("hPtRecMC");
  hPtChGenVar2->Sumw2();
  hPtChRecVar2->Sumw2();
  TH1D *hEffChRun3Var2 = (TH1D *) hPtChRecVar2->Clone("hEffChRun3Var2");
  success = hEffChRun3Var2->Divide(hEffChRun3Var2,hPtChGenVar2,1,1,"B");


  Float_t xLabelPos = 0.12;



  
  TCanvas *can1 = GetCanvas("TPCEfficiency480",400,40,500,350,0,0,0.02,0.15,0.14,0.01);
  can1->cd();
  can1->SetTicks();
  SetTitleTH1(hEffChRun3Var1,"Efficiency#times Acceptance",0.06,0.95,"p_{T}(GeV/c)",0.06,0.95);
  SetAxisTH1(hEffChRun3Var1,0.0,1.38,0.0,1.81,0.05,0.05);
  SetMarkerTH1(hEffChRun3Var1,"",24,0.9,2,2);
  hEffChRun3Var1->Draw("P");
  //SetMarkerTH1(hEffChRun3Var2,"",27,1.6,kGreen+3,kGreen+3);
  //hEffChRun3Var2->Draw("PSAME");   
  tex = new TLatex(xLabelPos,1.25,"TPC Performance (ALICE Fixed Target)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.0615);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,1.14,"p-W, #sqrt{s_{NN}} = 115 GeV,  Z_{target} = 480 cm");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,1.02,"Run-3 Reconstruction");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,0.92,"h^{#pm}, -2.2 < #eta < -1.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();

  can1->SaveAs("./outputPreliminaryO2/EfficienyChforFTVz480.pdf");


  
  TCanvas *can2 = GetCanvas("TPCEfficiency495",500,40,500,350,0,0,0.02,0.15,0.14,0.01);
  can2->cd();
  can2->SetTicks();
  SetTitleTH1(hEffChRun3Var2,"Efficiency#times Acceptance",0.06,0.95,"p_{T}(GeV/c)",0.06,0.95);
  SetAxisTH1(hEffChRun3Var2,0.0,1.38,0.0,1.81,0.05,0.05);
  SetMarkerTH1(hEffChRun3Var2,"",25,0.9,4,4);
  hEffChRun3Var2->Draw("P");
  //SetMarkerTH1(hEffChRun3Var2,"",27,1.6,kGreen+3,kGreen+3);
  //hEffChRun3Var2->Draw("PSAME");
  tex = new TLatex(xLabelPos,1.25,"TPC Performance (ALICE Fixed Target)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.0615);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,1.14,"p-W, #sqrt{s_{NN}} = 115 GeV,  Z_{target} = 495 cm");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,1.02,"Run-3 Reconstruction");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,0.92,"h^{#pm}, -2.2 < #eta < -1.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  
  can2->SaveAs("./outputPreliminaryO2/EfficienyChforFTVz495.pdf");




  TCanvas *can3 = GetCanvas("TPCEfficiencyIPCompar",600,40,500,350,0,0,0.02,0.15,0.14,0.01);
  can3->cd();
  can3->SetTicks();
  SetTitleTH1(hEffChRun3Var1,"Efficiency#times Acceptance",0.06,0.95,"p_{T}(GeV/c)",0.06,0.95);
  SetAxisTH1(hEffChRun3Var1,0.0,1.38,0.0,1.81,0.05,0.05);
  SetMarkerTH1(hEffChRun3Var1,"",24,0.9,2,2);
  hEffChRun3Var1->Draw("P");
  SetMarkerTH1(hEffChRun3Var2,"",25,0.8,4,4);
  hEffChRun3Var2->Draw("PSAME");
  tex = new TLatex(xLabelPos,1.25,"TPC Performance (ALICE Fixed Target)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.0615);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,1.14,"p-W, #sqrt{s_{NN}} = 115 GeV");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,1.02,"Run-3 Reconstruction");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,0.92,"h^{#pm}, -2.2 < #eta < -1.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
   

  
  legend = new TLegend(0.58,0.225,0.9,0.35);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0525);
  legend->AddEntry(hEffChRun3Var1,"Z_{target} = 480 cm","P");
  legend->AddEntry(hEffChRun3Var2,"Z_{target} = 495 cm","P");  
  legend->Draw();
  can3->SaveAs("./outputPreliminaryO2/EfficienyChIPcomparison.pdf");
  
  
  //------------------------------------------





  TH2F *hDeltaPtvsPtVar1 = (TH2F *) mFileVar1->Get("hPtDiffvsMCpT");
  TH2F *hDeltaPtvsPtVar2 = (TH2F *) mFileVar2->Get("hPtDiffvsMCpT");

  TH2F *hDeltaPtvsPtRecVar1 = (TH2F *)hDeltaPtvsPtVar1->Clone("hDeltaPtvsPtRecVar1");
  TH2F *hDeltaPtvsPtRecVar2 = (TH2F *)hDeltaPtvsPtVar2->Clone("hDeltaPtvsPtRecVar2");

  ///hDeltaPtvsPtRecVar1->RebinX(2);
  hDeltaPtvsPtRecVar1->FitSlicesY();
  TH1D *hMeanPtDiffVar1 = (TH1D*) gDirectory->Get("hDeltaPtvsPtRecVar1_1");
  TH1D *hSigmaPtDiffVar1 = (TH1D*) gDirectory->Get("hDeltaPtvsPtRecVar1_2");
  TH1D* hSigmaByMeanPtVar1 = RescaleByMean(hSigmaPtDiffVar1);
  hSigmaByMeanPtVar1->Scale(100);  

  ///hDeltaPtvsPtRecVar2->RebinX(2);
  hDeltaPtvsPtRecVar2->FitSlicesY();
  TH1D *hMeanPtDiffVar2 = (TH1D*) gDirectory->Get("hDeltaPtvsPtRecVar2_1");
  TH1D *hSigmaPtDiffVar2 = (TH1D*) gDirectory->Get("hDeltaPtvsPtRecVar2_2");
  TH1D* hSigmaByMeanPtVar2 = RescaleByMean(hSigmaPtDiffVar2);
  hSigmaByMeanPtVar2->Scale(100);  



  xLabelPos = 0.27;

  TH2F *htempPt = new TH2F("htempPt","",1000,0,5,1000,0,50);
  
  TCanvas *canResPt1 = GetCanvas("PtResIP480",450,200,500,350,0,0,0.02,0.15,0.14,0.01);
  canResPt1->cd();
  canResPt1->SetTicks();
  SetTitleTH1(htempPt,"#Deltap_{T}/p_{T} % ",0.06,0.95,"p_{T} (GeV/c)",0.06,0.95);  
  SetAxisTH1(htempPt,-1.15,28,0.21,1.66,0.05,0.05);
  htempPt->Draw();
  SetMarkerTH1(hSigmaByMeanPtVar1,"",24,0.8,2,2);
  hSigmaByMeanPtVar1->Draw("PSAME");


  tex = new TLatex(xLabelPos,25.2,"TPC Performance (ALICE Fixed Target)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.0615);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,22.8,"p-W, #sqrt{s_{NN}} = 115 GeV, Z_{target} = 480 cm");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,20.2,"Run-3 Reconstruction");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,18,"h^{#pm}, -2.2 < #eta < -1.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  
  legend = new TLegend(0.58,0.71,0.975,0.92);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0525);
  legend->AddEntry(hSigmaByMeanPtVar1,name2,"P");
  legend->AddEntry(hSigmaByMeanPtVar2,name3,"P");     
  //legend->Draw();  
  canResPt1->SaveAs("./outputPreliminaryO2/PtResolutionFTVz480cm.pdf");






  
  TCanvas *canResPt2 = GetCanvas("PtResIP495",550,200,500,350,0,0,0.02,0.15,0.14,0.01);
  canResPt2->cd();
  canResPt2->SetTicks();
  //SetTitleTH1(hSigmaByMeanPtVar2,"#Deltap_{T}/p_{T} % ",0.06,0.95,"p_{T} (GeV/c)",0.06,0.95);
  //SetAxisTH1(hSigmaByMeanPtVar2,-1.15,28,0.21,1.51,0.05,0.05);
  htempPt->Draw();
  SetMarkerTH1(hSigmaByMeanPtVar2,"",25,0.8,4,4);
  hSigmaByMeanPtVar2->Draw("PSAME");


  tex = new TLatex(xLabelPos,25.2,"TPC Performance (ALICE Fixed Target)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.0615);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,22.8,"p-W, #sqrt{s_{NN}} = 115 GeV, Z_{target} = 495 cm");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,20.2,"Run-3 Reconstruction");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,18,"h^{#pm}, -2.2 < #eta < -1.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  
  
  legend = new TLegend(0.58,0.71,0.975,0.92);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0525);
  legend->AddEntry(hSigmaByMeanPtVar1,name2,"P");
  legend->AddEntry(hSigmaByMeanPtVar2,name3,"P");     
  //legend->Draw();  
  canResPt2->SaveAs("./outputPreliminaryO2/PtResolutionFTVz495cm.pdf");




    
  TCanvas *canResCompIP = GetCanvas("PtResIPComp",650,200,500,350,0,0,0.02,0.15,0.14,0.01);
  canResCompIP->cd();
  canResCompIP->SetTicks();
  //SetTitleTH1(hSigmaByMeanPtVar1,"#Deltap_{T}/p_{T} % ",0.06,0.95,"p_{T} (GeV/c)",0.06,0.95);
  //SetAxisTH1(hSigmaByMeanPtVar1,-1.15,28,0.21,1.51,0.05,0.05);
  htempPt->Draw();
  SetMarkerTH1(hSigmaByMeanPtVar1,"",24,0.8,2,2);
  hSigmaByMeanPtVar1->Draw("PSAME");
  SetMarkerTH1(hSigmaByMeanPtVar2,"",25,0.85,4,4);
  hSigmaByMeanPtVar2->Draw("PSAME");

  tex = new TLatex(xLabelPos,25.2,"TPC Performance (ALICE Fixed Target)");
  tex->SetTextFont(42);
  tex->SetTextSize(0.0615);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,22.8,"p-W, #sqrt{s_{NN}} = 115 GeV");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,20.2,"Run-3 Reconstruction");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(xLabelPos,18,"h^{#pm}, -2.2 < #eta < -1.2");
  tex->SetTextFont(42);
  tex->SetTextSize(0.055);
  tex->SetLineWidth(2);
  tex->Draw();
  
  
  legend = new TLegend(0.7,0.7,0.9,0.82);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.0525);
  legend->AddEntry(hSigmaByMeanPtVar1,"Z_{target} = 480 cm","P");
  legend->AddEntry(hSigmaByMeanPtVar2,"Z_{target} = 495 cm","P");     
  legend->Draw();  
  canResCompIP->SaveAs("./outputPreliminaryO2/PtResolutionFTCompIP.pdf");









  
  
}//main ends
