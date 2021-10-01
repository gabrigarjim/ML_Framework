#include "headers.h"



 int main (){


TString inputFile = "protons.root";

TFile *eventFile;
TTree* eventTree;

eventFile = TFile::Open(inputFile);
eventTree = (TTree*)eventFile->Get("evt");
eventTree->SetBranchStatus("*",0);

eventTree->SetBranchStatus("CalifaCrystalCalData*",1);

TClonesArray *calCA = new TClonesArray("R3BCalifaCrystalCalData",5);
TBranch  *hitBranch = eventTree->GetBranch("CalifaCrystalCalData");
hitBranch->SetAddress(&calCA);


Int_t nEvents = eventTree->GetEntries();

Float_t nCrystalHits,compRatio,totEnergy,nPrimaries,ns,nf;
Int_t nHits,nMCTracks;

std::vector<Float_t> hitsVec;
std::vector<Float> ratioVec;
std::vector<Float> enVec;
std::vector<Float> primVec;


for (Int_t j = 0; j<nEvents; j++) {

  calCA->Clear();

  eventTree->GetEvent(j);
  nHits = calCA->GetEntries();

  totEnergy=0.0;

  if(!(j%1000))
   cout<<"Reading event "<<j<<" out of "<<nEvents<<" ("<<100.0*Float_t(j)/Float_t(nEvents)<<" % ) "<<endl;

   for(Int_t k=0;k<nHits;k++){

    totEnergy = totEnergy + 1000*((R3BCalifaCrystalCalData*)calCA->At(k))->GetEnergy();
    ns =  1000*((R3BCalifaCrystalCalData*)calCA->At(k))->GetNs();
    nf =  1000*((R3BCalifaCrystalCalData*)calCA->At(k))->GetNf();

   }

   if(nHits){
     hitsVec.push_back(nHits);
     enVec.push_back(totEnergy);
     ratioVec.push_back(ns/nf);
   }
}

 
