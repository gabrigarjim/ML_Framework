#include "R3BCalifaTensorFilling.h"
#include "R3BCalifaNNHeaders.h"


R3BCalifaTensorFilling::R3BCalifaTensorFilling()
: FairTask("R3B CALIFA Tensor Filling")
, fOnline(0)
, fMatrixRows(0)
, fMatrixColumns(0)
, fChannels(0)
{}

R3BCalifaTensorFilling::~R3BCalifaTensorFilling() {

  LOG(INFO) << "R3BCalifaTensorFilling: Delete instance";

}


 void R3BCalifaTensorFilling::SetInputTensorDimension(Int_t batch, Int_t rows,Int_t columns, Int_t channels){

    fBatchSize      = batch;
    fMatrixRows     = rows;
    fMatrixColumns  = columns;
    fChannels       = channels;

 }

 void R3BCalifaTensorFilling::Exec(){}

 void R3BCalifaTensorFilling::Reset(){}


 InitStatus R3BCalifaTensorFilling::Init(){

   /* ----- Filling Mother Matrix ----- */
   califa_id_table = new ifstream(fTableFile);


   string line,temp;
   int j=0;

   vector<string> row;

   while (getline(*califa_id_table,line)) {

     row.clear();

     std::istringstream iss(line);

     while(std::getline(iss, temp,' '))
       row.push_back(temp);

     for(int i = 0; i < 64; i++)
        motherMatrix[j][i] = std::stoi(row.at(i));

    j++;

   }

    califaInputTensor = new Tensor(DT_FLOAT, TensorShape({fBatchSize,fMatrixRows,fMatrixColumns,fChannels}));


    return kSUCCESS;


 }

 InitStatus R3BCalifaTensorFilling::ReInit(){
   return kSUCCESS;

 }

 void R3BCalifaTensorFilling::Finish(){}
