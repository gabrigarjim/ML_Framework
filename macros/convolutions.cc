////////////////////////////////////////////////////////////////////////////////
//                      Convolutions in TensorFlow                            //
//                                                                            //
//        Author: Gabriel García Jiménez (gabrielgarcia.jimenez@usc.es)       //
//        Date:   September 2020                                              //
////////////////////////////////////////////////////////////////////////////////

#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/framework/gradients.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "R3BCalifaNNHeaders.h"
#include "find_position.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

int main() {

  // ------------------- FILES WITH DATA --------------------

  TString dataFile = "/home/gabri/Analysis/s455/files/run0273_Calibrated.root";

  TFile *eventFile;
  TTree* eventTree;

  eventFile = TFile::Open(dataFile);
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


  int matrixRows    = 25;
  int matrixColumns = 64;
  int batchSize = 1;

  Tensor testMatrix(DT_FLOAT, TensorShape({batchSize,matrixRows,matrixColumns,1})); // Shape = {batch,height,width,channels (3 for a RGB image...)}
  vector<Tensor> outsTensor;

  /* ------ Initalizing Matrix ------ */
  for (int k = 0 ; k < batchSize ; k++) {
   for (int j = 0 ; j < matrixRows ; j++) {
    for (int i = 0 ; i < matrixColumns ; i++) {

       testMatrix.tensor<float,4>()(k,j,i,0) = 0.0;  // Second index means "Rows", Third index means "Columns"

      }
    }
  }

  /* ------------------ Filling Matrix -------------------- */

  Int_t nCalifaCalHits,fCrystalId;
  Int_t columnIndex,rowIndex;
  Float_t fEnergy;


  for (Int_t k = 4872; k<4873; k++) {

    calCA->Clear();

    eventTree->GetEvent(k);

    nCalifaCalHits = calCA->GetEntries();

    if(!(k%10))
     cout<<"Reading event "<<k<<" out of "<<batchSize<<" ("<<100.0*Float_t(k)/Float_t(batchSize)<<" % ) "<<endl;

     for(Int_t z= 0 ; z < nCalifaCalHits ; z++){

         fEnergy = 0.001*((R3BCalifaCrystalCalData*)calCA->At(z))->GetEnergy();

         fCrystalId = ((R3BCalifaCrystalCalData*)calCA->At(z))->GetCrystalId();
         find_position(fCrystalId,&columnIndex,&rowIndex,idMatrix);

         if(!isnan(fEnergy)){
           testMatrix.tensor<float,4>()(0,rowIndex,columnIndex,0) = fEnergy;
       }


    }
}






  // ================ Things for convolutional Layers ================

  Tensor kernel(DT_FLOAT,TensorShape({2,2,1,1}));   // Kernel

  for (int i = 0 ;  i < 2 ; i++){
    for (int k = 0 ; k < 2 ; k++){

      kernel.tensor<float,4>()(i,k,0,0)=1;

    }
  }

  int strides[4] = {1,1,1,1};   // Strides. It's common to use 0 and 3 elements as 1. 3 & 3 here means filter does not overlap

  string padding="SAME"; // Padding




   // ========== Things for Pooling Layers ===========
   int poolKernelSize[4]={1,4,4,1};

   cout <<"Matrix Shape : "<<testMatrix.shape()<<endl;


   // ======================= THE GRAPH ==========================

   Scope scope = Scope::NewRootScope();

   auto x = Placeholder(scope, DT_FLOAT);

   auto doesNothing = Identity(scope,x);                    // Identity Matrix

   auto conv = Conv2D(scope,x,kernel,strides,padding);
   auto pool = AvgPool(scope,x,poolKernelSize,strides,padding);
   auto maxPool = MaxPool(scope,x,poolKernelSize,strides,padding);



   ClientSession session(scope);

   TF_CHECK_OK(session.Run({{x,testMatrix}},{doesNothing,conv,pool,maxPool},&outsTensor));


   cout<<"Some Conv and Pooling Layers (4 x 5 Kernel)"<<endl;
   cout<<endl;
   cout<<"Matrix: "<<endl;

   for (int j=0;j<matrixRows*matrixColumns;j++) {

    cout<<setprecision(3)<<outsTensor[0].flat<float>()(j)<<"    ";

    if((j+1)%matrixColumns==0)
     cout<<endl;

   }
   cout<<endl;


   cout<<"Convoluted Matrix: "<<endl;

   for (int j=0;j<64*25;j++) {

    cout<<setprecision(2)<<outsTensor[1].flat<float>()(j)<<"       ";

    if((j+1)%64==0)
     cout<<endl;

   }
   cout<<endl;



   cout<<"Average Pooling Matrix: "<<endl;

   for (int j=0;j<64*25;j++) {

    cout<<outsTensor[2].flat<float>()(j)<<"       ";

    if((j+1)%64==0)
     cout<<endl;

   }
   cout<<endl;


   cout<<"Max Pooling Matrix: "<<endl;

   for (int j=0;j<64*25;j++) {

    cout<<outsTensor[3].flat<float>()(j)<<"     ";

    if((j+1)%64==0)
     cout<<endl;

   }
   cout<<endl;


}
