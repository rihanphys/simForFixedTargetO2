#if !defined(__CLING__) || defined(__ROOTCLING__)

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TObjArray.h"
#include "DataFormatsTPC/TrackTPC.h"
#include "SimulationDataFormat/MCCompLabel.h"
#include "SimulationDataFormat/MCTrack.h"

#include "Field/MagneticField.h"
#include <TGeoGlobalMagField.h>
#include "DetectorsBase/GeometryManager.h"
#include "DetectorsCommonDataFormats/NameConf.h"
#include "TPCBase/ParameterElectronics.h"
#include "TPCBase/ParameterGas.h"

#include "GlobalTracking/MatchTOF.h"
#include "GlobalTracking/MatchTPCITS.h"
#include "DetectorsBase/Propagator.h"
#include <CommonUtils/ConfigurableParam.h>
#include "ReconstructionDataFormats/Vertex.h"



#include <Rtypes.h>
#include <array>
#include <deque>
#include <vector>
#include <string>
#include <gsl/span>
#include "ReconstructionDataFormats/Track.h"
#include "ReconstructionDataFormats/TrackTPCITS.h"
#include "ReconstructionDataFormats/GlobalTrackID.h"
#include "GlobalTracking/MatchTPCITSParams.h"
#include "GPUO2InterfaceRefit.h"
#include "DetectorsBase/Propagator.h"

#endif

void getEfficiency(const std::string& fname1 = "tpctracks.root",const std::string& fnameMC = "o2sim_Kine.root",const std::string& foutname = "outputfile.root")
{


  //******* IF YOU ADD NEW HISTOGRAM, DONT FORGET to WRITE in the OUTPUT FILE *******
  
  Double_t pTbins[13] = {0,0.1,0.2,0.3,0.4,0.5,0.7,0.9,1.1,1.3,1.6,2.0,3.5};
    
  
  TH1F *hPtGenMC = new TH1F("hPtGenMC","pT MC Gen",12,pTbins);
  TH1F *hPtRecMC = new TH1F("hPtRecMC","pT MC Rec",12,pTbins);
  TH2F *hPtDiffvsMCpT = new TH2F("hPtDiffvsMCpT","#Delta p_{T} vs p_{T}",12,pTbins,100,-2.5,+2.5);

  TH2F *hEtaPtMC = new TH2F("hEtaPtMC","#eta vs pT MC prim",100,-5,5,100,0,5.0);
  TH1F *hEtaGenMC = new TH1F("hEtaGenMC","#eta MC Gen",100,-3.5,1.5);
  TH1F *hEtaRecMC = new TH1F("hEtaRecMC","#eta MC Rec",100,-3.5,1.5);


  TH2F *hEtaPtTPC = new TH2F("hEtaPtTPC","#eta vs pT TPC prim",100,-5,5,100,0,5.0);
  TH1F *hNclsTPC  = new TH1F("hNclsTPC","ncluster TPC",200,0,200);
  TH1F *hNclsTPCUsed = new TH1F("hNclsTPCUsed","ncluster TPC",200,0,200);
  TH1F *hTrkTglTPC = new TH1F("hTrkTglTPC","tgl TPC",200,-10,10);

  TH2F *hNclsvsEtaAside = new TH2F("hNclsvsEtaAside","nCls vs Eta TPC-A",100,-5,5,200,0,200);
  TH2F *hNclsvsEtaCside = new TH2F("hNclsvsEtaCside","nCls vs Eta TPC-C",100,-5,5,200,0,200);
  TH2F *hNclsvsEtaBothAC = new TH2F("hNclsvsEtaBothAC","nCls vs Eta AnC",100,-5,5,200,0,200);

  TH2F *hPtDiffvsMCEta = new TH2F("hPtDiffvsMCEta","#Delta p_{T} vs #eta",60,-3.0,3.0,600,-6,6);  
  TH2F *hPhiDiffvsMCpT = new TH2F("hPhiDiffvsMCpT","#Delta #phi vs p_{T}",60,0,6.0,600,-6,6);
  TH2F *hThetaDiffvsMCpT = new TH2F("hThetaDiffvsMCpT","#Delta #theta vs p_{T}",60,0,6.0,100,-100,100);
  TH2F *hSplitNclsvsPt  = new TH2F("hSplitNclsvsPt","nclsTPC vs pT",60,0,6.0,200,0,200);



  const Double_t vzMean = 480.0;
  Double_t  fVzHigh = vzMean+40;  // <Vz> + 30cm
  Double_t  fVzLow  = vzMean-40;  // <Vz> - 30cm 
  
  TH2F *hDCAzVsEvent = new TH2F("hDCAzVsEvent","DCAz for each event",120,0,120,200,fVzLow,fVzHigh);
  TH2F *hDCAyVsEvent = new TH2F("hDCAyVsEvent","DCAy for each event",120,0,120,200,-20,20);

  TH1D *hVzDist = new TH1D("hVzDist"," Vz (cm)",200,fVzLow,fVzHigh);
  TH1D *hVyDist = new TH1D("hVyDist"," Vy (cm)",200,-10,10);
  TH2F *hnTrkvsNcont =  new TH2F("hnTrkvsNcont","ntrk vs ncont Vz",100,0,100,100,0,100);


      

  Double_t DCAzForVz[100][10] = {{0.,},{0.,}};
  Double_t DCAyForVy[100][10] = {{0.,},{0.,}};
    
  Int_t nTrkContVz[100] = {0,};
  Int_t nClustCont[100][10] = {{0,},{0}};
  Int_t nTrackUsable[100] = {0,};
  

  
  // open files and trees
  TFile trFile1(fname1.c_str());
  TTree* trTree1 = (TTree*)trFile1.Get("events");
  int nev = trTree1->GetEntriesFast();

  //std::cout<<" N0. of Simulated event = "<<nev<<std::endl;

  TFile trFileMC(fnameMC.c_str());
  TTree* trTreeMC = (TTree*)trFileMC.Get("o2sim");
  
  std::vector<o2::tpc::TrackTPC> *trvPtr = nullptr;
  std::vector<o2::MCCompLabel> *mctrPtr = nullptr;
  std::vector<o2::MCTrack> *mctrGenPtr = nullptr;

  trTree1->SetBranchAddress("Tracks",&trvPtr);


//MC info:
  if (trTree1->GetBranch("TracksMCTruth")) {
    trTree1->SetBranchAddress("TracksMCTruth",&mctrPtr);
  }
  if (trTreeMC->GetBranch("MCTrack")) {
    trTreeMC->SetBranchAddress("MCTrack",&mctrGenPtr);
  }



  o2::base::GeometryManager::loadGeometry();
  o2::base::Propagator::initFieldFromGRP(o2::base::NameConf::getGRPFileName());
  auto field = static_cast<o2::field::MagneticField*>(TGeoGlobalMagField::Instance()->GetField());
  LOG(INFO) << "simulation B field = " << field ;

  auto& elParam = o2::tpc::ParameterElectronics::Instance(); 
  auto mTPCtimebinMus = elParam.ZbinWidth;
 
  //return;
  auto& gasParam = o2::tpc::ParameterGas::Instance();
  auto mTPCVdrift0  = gasParam.DriftV;
  LOG(INFO) << "tpc timebin = " << mTPCtimebinMus <<" tpc drift vel. = "<< mTPCVdrift0;

  float chi2 = 0.f;
  const float maxStep = 2.f;	
  auto propagator = o2::base::Propagator::Instance();

  o2::dataformats::VertexBase vtxDummy; 
  vtxDummy.setZ(vzMean);
  vtxDummy.setX(0.0);
  vtxDummy.setY(0.0);
  
  o2::globaltracking::TrackLocTPC mTPCWork;
  o2::base::Propagator::MatCorrType mUseMatCorrFlag = o2::base::Propagator::MatCorrType::USEMatCorrTGeo;

 	

  //return;

  int pdgMC = 0, nTrkPrim,nClsTPC,nTrkAccept=0,nTrkRepeat=0;
  double etaMC,ptMC,phiMC,thetaMC,deltaPt;
  double tpcPt,tpcEta,tpcPhi,tpcTheta,tpcTime0;
  double dcaX,dcaY,dcaZ;
  bool prim;
  int eventid,trackid;


/// MC primary Loop:
  for (int iev=0;iev<100;iev++) {  
    trTreeMC->GetEntry(iev);
    
    int ntr = mctrGenPtr->size();
    std::cout<<" No. MC trk = "<<ntr<<" in MC event = "<<iev<<std::endl;
    //return;
    for (int itr=0;itr<ntr;itr++) {

      o2::MCTrack mcTrk;	
      mcTrk = (*mctrGenPtr)[itr];

      pdgMC = mcTrk.GetPdgCode();
      prim = mcTrk.isPrimary();
      if(!prim) continue;         // Only analyse primaries. 
      nTrkPrim++;
      etaMC = mcTrk.GetEta();	
      ptMC  = mcTrk.GetPt();

      hEtaPtMC->Fill(etaMC,ptMC); // All genenerated primary particles
      
      if(fabs(pdgMC)==211 || fabs(pdgMC)==321 || fabs(pdgMC)==2212){
	//LOG(INFO) <<" pdg = "<<pdgMC<<"\t Vz = "<<mcTrk.Vz()<<"\t pt = " <<ptMC<<"\t eta = "<<etaMC<<"\tMC event = "<<iev<<" trk " << itr;
	if(ptMC>0.4){
	  hEtaGenMC->Fill(etaMC);   // eta distribution for pT>0.4 GeV tracks. 
	}
	if(etaMC<-2.2 || etaMC> -1.2) continue;  //Defult Eta cut for best analysis region.
        hPtGenMC->Fill(ptMC);
      }

      //LOG(INFO) << "#" << itr  << " MC: " << lbl << " " << track.asString();

    }
  }

///------- MC Loop done --------









  

  ///------- now we run loop over reconstructed tracks -------
  std::vector<int> MCeventId;
  std::vector<int> MCtrackId;

  int allParticles[20000];

  o2::track::TrackParCov selParticles[20000];
  Int_t icont = 0;
  Int_t ntrkAna = 0;
    
  
  for (int iev=0;iev<1;iev++) {   /// All tracks are in one entry.

    trTree1->GetEntry(iev);
    int ntr = trvPtr->size();

    nTrkPrim = 0;
    nTrkAccept=0;
    std::cout<<" No. of TPC trk = "<<ntr<<" in Rec event = "<<iev<<std::endl;


    
    for (int itr=0;itr<ntr;itr++) {

      const auto& track = (*trvPtr)[itr];
      o2::track::TrackParCov& tTPC = (*trvPtr)[itr];
     	
      nClsTPC = track.getNClusters();
      hNclsTPC->Fill(nClsTPC); 
     
      tpcTime0 = track.getTime0();	

      o2::MCCompLabel lbl;
      if (mctrPtr) {
	lbl = (*mctrPtr)[itr];
      }

      eventid = lbl.getEventID();  // MC labels event and tracks
      trackid = lbl.getTrackID();

      ///Get MC information for this track.
      trTreeMC->GetEntry(eventid);
      
      o2::MCTrack mcTrk = (*mctrGenPtr)[trackid];

      //if(!mcTrk) continue;
      prim = mcTrk.isPrimary();
      if(!prim)       continue;

      etaMC = mcTrk.GetEta();	

      if(etaMC<-2.20 || etaMC>-1.2) continue; // redundant cut as this is on MC.

      pdgMC = mcTrk.GetPdgCode();
      ptMC  = mcTrk.GetPt();
      phiMC = mcTrk.GetPhi(); 
      thetaMC = mcTrk.GetTheta(); 


      if(fabs(pdgMC)==211 || fabs(pdgMC)==321 || fabs(pdgMC)==2212){

        //tpcEta = track.getEta();   /// this is reconstructed Eta.

	/// Some QA for the experts: Not needed for us!
        if(ptMC>0.4){
          if(track.hasASideClustersOnly()){
            hNclsvsEtaAside->Fill(etaMC,nClsTPC);
	  }
          if(track.hasCSideClustersOnly()){
            hNclsvsEtaCside->Fill(etaMC,nClsTPC);
	  }
	  if(track.hasBothSidesClusters()){
	    hNclsvsEtaBothAC->Fill(etaMC,nClsTPC);	   
	  }
	  
	  //LOG(INFO)<<"#"<<itr<<" pdg = "<<pdgMC<<"\tnClsTPC "<<nClsTPC<<"\tpt = " <<ptMC<<"\teta = "<<etaMC<<"\tMCevent " <<eventid  <<"\t MCtrk "<<trackid ;	  
	}


	/// when the problem of track merging is solved, we would have only 1 copy per MC track.
	/// Right now there are multiple tracks per 1 MC tracks that is why we need to remove the
	/// double counting. For the same reason we have poor pT resolution. When we have merged
	/// all track segments into one single track, then we should have best possible resolution
	/// (i.e., values similar to Run2 Simulation results)

	/// This part below is to remove double (or tripple counting) of unmerged track segments:
        if(nTrkAccept>0){
          if(std::find(MCeventId.begin(),MCeventId.end(),eventid) != MCeventId.end() && std::find(MCtrackId.begin(),MCtrackId.end(),trackid) != MCtrackId.end()){	    
	    // LOG(INFO)<<"==> track reapeated "<<" pt = "<<ptMC<<"\tnClsTPC "<<nClsTPC<<" MCevt = "<<eventid<<" trk = "<<trackid;
	    nTrkRepeat++;
	    hSplitNclsvsPt->Fill(ptMC,nClsTPC);	      
	    int nclsOld = allParticles[trackid];	      
	    if (nClsTPC > nclsOld){
	      selParticles[trackid] = tTPC;
	    }
	    else {
	      continue;
	    }
	  }
        }

	
	allParticles[trackid] = nClsTPC;
		
	
	if(nTrkAccept==0){
	  selParticles[trackid] = tTPC; //just one time;
	}
	
	
        MCeventId.push_back(eventid);  /// keeping list of used event and track information 
        MCtrackId.push_back(trackid);  /// used for identifying double counting of tracks. 

	nTrkAccept++;

       
        //dcaZ = track.getZ();
        //dcaX = track.getX();
        //dcaY = track.getY();
        //LOG(INFO)<<"before prop: trk#"<<itr<<" dcaz = "<<dcaZ<<" dcax= "<<dcaX<<" dcay = "<<dcaY;

	
	//Propagate the TPC tracks to beam pipe to get the DCA_y and DCA_z positions:
        if (!propagator->propagateToDCA(vtxDummy, tTPC, propagator->getNominalBz(), maxStep, mUseMatCorrFlag, nullptr, nullptr)) {
	  LOG(ERROR) << "LTOF integral might be incorrect";
	}

	//return 0;
        dcaZ = tTPC.getZ();
        dcaX = tTPC.getX();
        dcaY = tTPC.getY();	
	hDCAzVsEvent->Fill(eventid,dcaZ);
	hDCAyVsEvent->Fill(eventid,dcaY);
	
        ///LOG(INFO)<<"after prop: trk#"<<itr<<" dcaz = "<<dcaZ<<" dcax= "<<dcaX<<" dcay = "<<dcaY;

       
	      
	if(dcaZ >= fVzLow && dcaZ <= fVzHigh){
	  icont = nTrkContVz[eventid];       // Candidate tracks we have for Vz estimation 
	  DCAzForVz[eventid][icont] = dcaZ;  //
	  DCAyForVy[eventid][icont] = dcaY;  //	
	  nClustCont[eventid][icont] = nClsTPC;
	  icont++;                           // increase one more candidate
	  nTrkContVz[eventid] = icont;       // store the updated number of contributors.
	}
	
	ntrkAna = nTrackUsable[eventid];     // check how many track the event had earlier.
	ntrkAna++;                           // One more track found in that event.
	nTrackUsable[eventid] = ntrkAna;     // store updated number of tracks in that event.


	hPtRecMC->Fill(ptMC);      // this is reconstructed pT. Ratio with hPtGenMC would give us efficiency. 
	if(ptMC>0.4){
	  hEtaRecMC->Fill(etaMC);  // Eta dependence of Efficiency.  
	}
	
	//// Now lets fill some QA Histograms:
        hNclsTPCUsed->Fill(nClsTPC);
	hTrkTglTPC->Fill(track.getTgl());

	
        tpcPt  = track.getPt();
        tpcPhi = track.getPhi();
        tpcTheta = track.getTheta();
	
        hEtaPtTPC->Fill(track.getEta(),tpcPt);

        deltaPt = ptMC-tpcPt; 
	if(nClsTPC>=70){
	  hPtDiffvsMCpT->Fill(ptMC,deltaPt);
	  if(ptMC>0.4){
	    hPtDiffvsMCEta->Fill(etaMC,deltaPt);
	  }	  
	  hPhiDiffvsMCpT->Fill(ptMC,(phiMC-tpcPhi));	  
	  hThetaDiffvsMCpT->Fill(ptMC,1000*(thetaMC-tpcTheta));
	}//ncls cut	
      }//PID cut
    }///all tracks in one event. 

    
    
    // Now, Get Vz and Vy distribution from the Candidate tracks we saved earlier:
    // Ruben: Just to get an idea about the Z resolution, you can fit the peak of
    // Z positions of TPC tracks at beam line by a Gaussian, and scale the
    // extracted sigma by sqrt(Ntracks_per_event_expected / Ntracks_used) <- why we need this scaling?
    // to be asked to Ruben.
    
    
    Int_t nContEvent = 0;
    Int_t ntrkEvent = 0;

    for(int iv =0; iv<100; iv++) {
      
      ntrkEvent  = nTrackUsable[iv];
      nContEvent = nTrkContVz[iv];

      hnTrkvsNcont->Fill(ntrkEvent,nContEvent);
      
      Double_t wgtSum=0; // weighted Sum
      Int_t    sumWgt=0; // sum of weights
      Double_t VzPos=0,VyPos=0;

      for(int it=0;it<nContEvent;it++){
	wgtSum += nClustCont[iv][it]*DCAzForVz[iv][it];
	sumWgt += nClustCont[iv][it];
      }
      VzPos = wgtSum/sumWgt; 
      hVzDist->Fill(VzPos);
      
      wgtSum = 0;
      sumWgt = 0;
      
      for(int it=0;it<nContEvent;it++){
        wgtSum += nClustCont[iv][it]*DCAyForVy[iv][it];
        sumWgt += nClustCont[iv][it];
      }
      VyPos = wgtSum/sumWgt;
      hVyDist->Fill(VyPos);      
    }
   
    // DCAyForVy[eventid][icont] = dcaY; 
    std::cout<<" N0. of primary trk = "<<nTrkPrim<<" passed = "<<nTrkAccept<<" repeated tracks = "<<nTrkRepeat<<std::endl;
  }
  

  delete trTree1;
  delete trTreeMC;






  /// Write down all histograms in the file:
  
  TFile *fout = new TFile(foutname.c_str(),"RECREATE");
  fout->cd();
  hEtaPtMC->Write();
  hPtRecMC->Write();
  hPtGenMC->Write();
  hEtaGenMC->Write();
  hEtaRecMC->Write();  
  hEtaPtTPC->Write();
  hTrkTglTPC->Write();
  hNclsTPC->Write();
  hNclsTPCUsed->Write();
  hSplitNclsvsPt->Write();
  hNclsvsEtaAside->Write();  
  hNclsvsEtaCside->Write(); 
  hNclsvsEtaBothAC->Write();  
  hPtDiffvsMCpT->Write();
  hPtDiffvsMCEta->Write();
  hPhiDiffvsMCpT->Write();
  hThetaDiffvsMCpT->Write();
  hDCAzVsEvent->Write();
  hDCAyVsEvent->Write();
  hVyDist->Write();    
  hVzDist->Write();    
  hnTrkvsNcont->Write(); 
    
     
  fout->Close();


  
}


