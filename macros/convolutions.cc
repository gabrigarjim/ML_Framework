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
#include <cstdlib>
#include <random>
#include <stdlib.h>
#include <time.h>
using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

int main() {

  // -------------------- SETTINGS AND DECLARATIONS --------------------- //

  vector<Tensor> outsTensor;
  srand(time(NULL));
  int matrixDim = 9;

  /* ----- Lets create some random matrix.... ------ */

  Tensor testMatrix(DT_FLOAT, TensorShape({1,matrixDim,matrixDim,1})); // Shape = {batch,height,width,channels (3 for a RGB image...)}

  /* ------ Initalizing Matrix ------ */

   for (int j=0; j<matrixDim;j++) {
    for (int i =0; i<matrixDim;i++) {

       testMatrix.tensor<float,4>()(0,j,i,0) = (rand() % 10);  // Second index means "Rows", Third index means "Columns"

     }
   }


  // ================ Things for convolutional Layers ================

  Tensor myFilter(DT_FLOAT,TensorShape({3,3,1,1}));   // Kernel

  for (int i = 0; i<matrixDim/3;i++) {
    for (int k = 0;k<matrixDim/3;k++) {

      myFilter.tensor<float,4>()(i,k,0,0)=1;

    }
  }

  int strides[4] = {1,3,3,1};   // Strides. It's common to use 0 and 3 elements as 1. 3 & 3 here means filter does not overlap

  string padding="SAME"; // Padding




   // ========== Things for Pooling Layers ===========
   int poolKernelSize[4]={1,3,3,1};

   cout <<"Matrix Shape : "<<testMatrix.shape()<<endl;


   // ======================= THE GRAPH ==========================

   Scope scope = Scope::NewRootScope();

   auto x = Placeholder(scope, DT_FLOAT);

   auto doesNothing = Identity(scope,x);                    // Identity Matrix

   auto conv = Conv2D(scope,x,myFilter,strides,padding);
   auto pool = AvgPool(scope,x,poolKernelSize,strides,padding);
   auto maxPool = MaxPool(scope,x,poolKernelSize,strides,padding);



   ClientSession session(scope);

   TF_CHECK_OK(session.Run({{x,testMatrix}},{doesNothing,conv,pool,maxPool},&outsTensor));


   cout<<"Some Conv and Pooling Layers (3 x 3 Kernel)"<<endl;
   cout<<endl;
   cout<<"Matrix: "<<endl;

   for (int j=0;j<matrixDim*matrixDim;j++) {

    cout<<outsTensor[0].flat<float>()(j)<<"   ";

    if((j+1)%matrixDim==0)
     cout<<endl;

   }
   cout<<endl;


   cout<<"Convoluted Matrix: "<<endl;

   for (int j=0;j<matrixDim;j++) {

    cout<<outsTensor[1].flat<float>()(j)<<"   ";

    if(j==2 || j==5 || j==8)
     cout<<endl;

   }
   cout<<endl;



   cout<<"Average Pooling Matrix: "<<endl;

   for (int j=0;j<matrixDim;j++) {

    cout<<outsTensor[2].flat<float>()(j)<<"   ";

    if(j==2 || j==5 || j==8)
     cout<<endl;

   }
   cout<<endl;

   cout<<"Max Pooling Matrix: "<<endl;

   for (int j=0;j<matrixDim;j++) {

    cout<<outsTensor[3].flat<float>()(j)<<"   ";

    if(j==2 || j==5 || j==8)
     cout<<endl;

   }
   cout<<endl;


}
