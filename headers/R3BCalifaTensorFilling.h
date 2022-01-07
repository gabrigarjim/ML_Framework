#ifndef R3BCALIFATENSORFILLING_H
#define R3BCALIFATENSORFILLING_H

#include "R3BCalifaNNHeaders.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;


class R3BCalifaTensorFilling : public FairTask
{

 public :
  R3BCalifaTensorFilling();

  virtual ~R3BCalifaTensorFilling();

  virtual void Exec();

  virtual void Reset();

  virtual void SetMotherMatrix();

  virtual InitStatus Init();

  virtual InitStatus ReInit();

  virtual void Finish();

  void SetOnline(Bool_t option) { fOnline = option; }

  /* shape = {batch,height,width,channels (3 for a RGB image...)} */
  void SetInputTensorDimension(Int_t batch, Int_t rows,Int_t columns, Int_t channels);

  void SetCalifaTableFile(TString table) { fTableFile = table;}

  private:
    Int_t motherMatrix[25][64]={{0},{0}}; /* Mother matrix dimensions are fixed */

    std::ifstream *califa_id_table;

    Bool_t fOnline;

    Int_t fBatchSize;
    Int_t fMatrixRows;
    Int_t fMatrixColumns;
    Int_t fChannels;
    TString fTableFile;

    Tensor *califaInputTensor;

    friend class R3BCalifaNNTraining;

};

#endif
