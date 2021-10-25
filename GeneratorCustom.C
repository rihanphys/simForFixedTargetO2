AliGenerator * GeneratorCustom() {
 
  const Float_t vtxZ = 480.0;     // Origin of the Events in MC. 
 
  TVirtualMCDecayer* decayer = new AliDecayerPythia();
  decayer->Init();
  gMC->SetExternalDecayer(decayer);
 
  gSystem->Load("libHIJING");         // Load Libraries
  gSystem->Load("libTHijing");
 
  AliGenHijing *gener = new AliGenHijing(-1);
  Float_t BeamEnergy = 7000;            // Beam Energy, For Fixed Target mode       
  gener->SetEnergyCMS(BeamEnergy);
  gener->SetReferenceFrame("LAB");      // Note: if "LAB" is choosen then the energy mentioned above is beam energy!
                                        // if "CMS" is choosen then the energy is center of mass energy (i.e., \/s_NN)
  gener->SetImpactParameterRange(0,0.5);// ranges are in fm   
  gener->SetProjectile("P",1, 1);
  //gener->SetProjectile("A",208,82);   // For Pb-beam. Also change beam energy     
  gener->SetTarget("A", 184, 74);       // Tungsten Target
  gener->SetSpectators(0);              // Do not store spectators.  
  gener->KeepFullEvent();               //keep the decay chains for reconstruction                                            
  gener->SetJetQuenching(0);            // enable jet quenching                                  
  gener->SetShadowing(0);               // enable shadowing                                 
  gener->SetSelectAll(0);
  gener->SetFlipTrackPz(kTRUE);         // So that tracks are boosted in A side ()  
  gener->SetOrigin(0,0,vtxZ);
 
  return gener;
  
 }
