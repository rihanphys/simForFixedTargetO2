

  TH1D* RescaleByMean(TH1D* h1){
    Double_t val,mean,error;
    Int_t nBinX = h1->GetNbinsX();
    const char *name1 = h1->GetName();
    TH1D *hnew  = (TH1D *) h1->Clone(Form("%s_new",name1));
    hnew->Reset();
    
    for(int i=1; i<=nBinX; i++){
      mean = h1->GetBinCenter(i);
      val  =  h1->GetBinContent(i);
      error =  h1->GetBinError(i);
      if(val==0 && error==0) continue;
      hnew->SetBinContent(i,val/mean);
      hnew->SetBinError(i,error/mean);
    }
    return hnew;
  }


TH1D* RescaleByMean(TH1D* h1,TH1D* hmean){
    Double_t val,mean,error;
    Int_t nBinX = h1->GetNbinsX();
    const char *name1 = h1->GetName();
    TH1D *hnew  = (TH1D *) h1->Clone(Form("%s_new",name1));
    hnew->Reset();
    
    for(int i=1; i<=nBinX; i++){
      mean = hmean->GetBinCenter(i);
      val  =  h1->GetBinContent(i);
      error =  h1->GetBinError(i);
      if(val==0 && error==0) continue;
      cout<<" bin = "<<i<<" val = "<<val<<" mean = "<<mean<<endl;
      hnew->SetBinContent(i,val/mean);
      hnew->SetBinError(i,error/mean);
    }
    return hnew;
  }

TH1D* RescaleByMean(TH1D* h1,Double_t meanIn){
    Double_t val,mean,error;
    Int_t nBinX = h1->GetNbinsX();
    const char *name1 = h1->GetName();
    TH1D *hnew  = (TH1D *) h1->Clone(Form("%s_new",name1));
    //hnew->Reset();
    hnew->Scale(1./meanIn);
    
    /*
    for(int i=1; i<=nBinX; i++){
      //mean = hmean->GetBinCenter(i);
      val  =  h1->GetBinContent(i);
      error =  h1->GetBinError(i);
      if(val==0 && error==0) continue;
      cout<<" bin = "<<i<<" val = "<<val<<" mean = "<<meanIn<<" val/mean = "<<val/meanIn<<endl;
      hnew->SetBinContent(i,val/meanIn);
      hnew->SetBinError(i,error/meanIn);
    }*/
    return hnew;
  }






TCanvas *GetCanvas(TString title,int xpos,int ypos,int sizeX,int sizeY,Bool_t gridx,Bool_t gridy,float topMgn,float botMgn,float leftMgn,float rightMgn)
{
  TCanvas *c1 = new TCanvas(title,title,xpos,ypos,sizeX,sizeY);
  //c1->SetCanvasSize(sizeX,sizeY);
  //c1->SetTitle(title);
  c1->SetTopMargin(topMgn);
  c1->SetRightMargin(rightMgn);
  c1->SetLeftMargin(leftMgn);
  c1->SetBottomMargin(botMgn);
  if(gridx)
    c1->SetGridx();
  if(gridy)
    c1->SetGridy();
  return c1;
}

//--------------------------------
void SetMarkerTH1(TH1 *h1,TString hTitle,int markSyle,float markSize,int markColor,int lineColor){
  h1->SetTitle(hTitle);
  h1->SetMarkerStyle(markSyle);
  h1->SetMarkerSize(markSize);
  h1->SetMarkerColor(markColor);
  h1->SetLineColor(lineColor);
}
void SetAxisTH1(TH1 *h1,float yAxisLow,float yAxisHigh,float xAxisLow,float xAxisHigh,float yLabelsize,float xLabelsize){
  h1->GetYaxis()->SetRangeUser(yAxisLow,yAxisHigh);
  h1->GetXaxis()->SetRangeUser(xAxisLow,xAxisHigh);
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(xLabelsize);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(yLabelsize);
}
void SetTitleTH1(TH1 *h1,TString yTitle,float yTileSize,float yOffset,TString xTitle,float xTileSize,float xOffset){
  h1->GetYaxis()->SetTitle(yTitle);
  h1->GetYaxis()->SetTitleSize(yTileSize);
  h1->GetYaxis()->SetTitleOffset(yOffset);
  h1->GetYaxis()->CenterTitle(true);
  h1->GetYaxis()->SetTitleFont(42);
  h1->GetXaxis()->SetTitle(xTitle);
  h1->GetXaxis()->SetTitleSize(xTileSize);
  h1->GetXaxis()->SetTitleOffset(xOffset);
  h1->GetXaxis()->CenterTitle(true);
  h1->GetXaxis()->SetTitleFont(42);
}
//--------------------------------
void SetMarkerTH2(TH2 *h1,TString hTitle,int markSyle,float markSize,int markColor,int lineColor){
  h1->SetTitle(hTitle);
  h1->SetMarkerStyle(markSyle);
  h1->SetMarkerSize(markSize);
  h1->SetMarkerColor(markColor);
  h1->SetLineColor(lineColor);
}
void SetAxisTH2(TH2 *h1,float yAxisLow,float yAxisHigh,float xAxisLow,float xAxisHigh,float yLabelsize,float xLabelsize){
  h1->GetYaxis()->SetRangeUser(yAxisLow,yAxisHigh);
  h1->GetXaxis()->SetRangeUser(xAxisLow,xAxisHigh);
  h1->GetXaxis()->SetLabelFont(42);
  h1->GetXaxis()->SetLabelSize(xLabelsize);
  h1->GetYaxis()->SetLabelFont(42);
  h1->GetYaxis()->SetLabelSize(yLabelsize);
}
void SetTitleTH2(TH2 *h1,TString yTitle,float yTileSize,float yOffset,TString xTitle,float xTileSize,float xOffset){
  h1->GetYaxis()->SetTitle(yTitle);
  h1->GetYaxis()->SetTitleSize(yTileSize);
  h1->GetYaxis()->SetTitleOffset(yOffset);
  h1->GetYaxis()->CenterTitle(true);
  h1->GetYaxis()->SetTitleFont(42);
  h1->GetXaxis()->SetTitle(xTitle);
  h1->GetXaxis()->SetTitleSize(xTileSize);
  h1->GetXaxis()->SetTitleOffset(xOffset);
  h1->GetXaxis()->CenterTitle(true);
  h1->GetXaxis()->SetTitleFont(42);
}



void drawBox(Float_t xstart,Float_t ystart,Float_t xstop,Float_t ystop, Int_t color, Int_t style){

  /// bottom edge:
  TLine *line1 = new TLine(xstart,ystart,xstop,ystart);
  line1->SetLineColor(color);
  line1->SetLineStyle(style);
  line1->Draw();
  /// top edge:
  TLine *line2 = new TLine(xstart,ystop,xstop,ystop);
  line2->SetLineColor(color);
  line2->SetLineStyle(style);
  line2->Draw();
  /// left edge:
  TLine *line3 = new TLine(xstart,ystart,xstart,ystop);
  line3->SetLineColor(color);
  line3->SetLineStyle(style);
  line3->Draw();
  /// right edge:
  TLine *line4 = new TLine(xstop,ystart,xstop,ystop);
  line4->SetLineColor(color);
  line4->SetLineStyle(style);
  line4->Draw();  
}


Double_t thetaFromEta(Double_t eta){
  return 2.*TMath::ATan(TMath::Exp(-1.*eta));
}

