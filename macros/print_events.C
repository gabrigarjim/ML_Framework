#include "../headers/find_position.h"

void print_events()
{

  TStopwatch timer;
  timer.Start();

  // Put here the root file
  TString fileList = "/home/gabri/Analysis/s455/files/run0273_Calibrated.root";

  TFile *eventFile;
  TTree* eventTree;

  eventFile = TFile::Open(fileList);
  eventTree = (TTree*)eventFile->Get("evt");
  eventTree->SetBranchStatus("*",0);

  eventTree->SetBranchStatus("CalifaCrystalCalData*",1);

  TClonesArray *calCA = new TClonesArray("R3BCalifaCrystalCalData",5);
  TBranch  *calBranch = eventTree->GetBranch("CalifaCrystalCalData");
  calBranch->SetAddress(&calCA);

  Int_t nEvents = eventTree->GetEntries();


  /* --------------- Getting Mother Matrix ------------ */
  ifstream *califa_id_table = new ifstream("../params/califa_table.csv");
  Int_t idMatrix[25][64]={{0},{0}};


  string line,temp;
  int j=0;

  vector<string> row;

  while (getline(*califa_id_table,line)) {

    row.clear();

    std::istringstream iss(line);

    while(std::getline(iss, temp,' '))
      row.push_back(temp);

    for(int i = 0; i < 64; i++)
       idMatrix[j][i] = std::stoi(row.at(i));

     j++;
 }





  Int_t nCalifaCalHits,fCrystalId;
  Int_t columnIndex,rowIndex;


  //Float_t califaMatrix [25][64];

  Float_t fEnergy,fCalosum;


  for (Int_t j = 0; j<5000; j++) {

    calCA->Clear();

    eventTree->GetEvent(j);

    nCalifaCalHits = calCA->GetEntries();

    fCalosum=0.0;

    Float_t califaMatrix [25][64]={{0},{0}};


    if(!(j%1000))
     cout<<"Reading event "<<j<<" out of "<<nEvents<<" ("<<100.0*Float_t(j)/Float_t(nEvents)<<" % ) "<<endl;



     for(Int_t z=0;z<nCalifaCalHits;z++){

         fEnergy = 0.001*((R3BCalifaCrystalCalData*)calCA->At(z))->GetEnergy();

         fCrystalId = ((R3BCalifaCrystalCalData*)calCA->At(z))->GetCrystalId();
         find_position(fCrystalId,&columnIndex,&rowIndex,idMatrix);

         if(isnan(fEnergy)){
         cout<<"Bad Hit: "<<fCrystalId<<" "<<z<<endl;
         continue;

       }

         fCalosum = fCalosum + 0.001*((R3BCalifaCrystalCalData*)calCA->At(z))->GetEnergy();


         califaMatrix[rowIndex][columnIndex]=fEnergy;

    }

 if(nCalifaCalHits && fCalosum<600){
   cout<<"EVENT : "<<j<<endl;

    for(int i = 0 ; i < 25 ; i++){
     cout<<endl;

     for(int j = 0 ; j < 64 ; j++){

      cout<<califaMatrix[i][j]<<"    ";
    }}
    cout<<" Total Event Energy: "<<fCalosum<<endl;

   cout<<endl;
 }
}


   timer.Stop();
   Double_t rtime = timer.RealTime();
   Double_t ctime = timer.CpuTime();
   std::cout << std::endl << std::endl;
   std::cout << "Macro finished succesfully." << std::endl;
   std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;

}
