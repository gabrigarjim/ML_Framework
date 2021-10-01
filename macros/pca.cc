#include "../headers/headers.h"
#include "../headers/statistical_functions.h"

using namespace std;

 int main(){

   float sepalLenght,sepalWidth,petalLenght,petalWidth;
   string name;

   vector<float> sLenghtVec;
   vector<float> sWidthVec;
   vector<float> pLenghtVec;
   vector<float> pWidthVec;

   ifstream *dataFile = new ifstream("iris.csv");

   if(dataFile) {

    while (*dataFile>>sepalLenght>>sepalWidth>>petalLenght>>petalWidth>>name) {

        sLenghtVec.push_back(sepalLenght);
        sWidthVec.push_back(sepalWidth);
        pLenghtVec.push_back(petalLenght);
        pWidthVec.push_back(petalWidth);
     }
   }

   else {
     cout<<"DATA FILE NOT FOUND!!!!!! "<<endl;
   }



  cout<<" Sepal Mean Length: "<<mean_value(sLenghtVec)<<endl;
  cout<<" Sepal Mean Width: "<<mean_value(sWidthVec)<<endl;
  cout<<" Petal Mean Length: "<<mean_value(pLenghtVec)<<endl;
  cout<<" Petal Mean Width: "<<mean_value(pWidthVec)<<endl;

  // Standarization

  for (int i =0; i<sLenghtVec.size();i++){

     sLenghtVec.at(i)=(sLenghtVec.at(i)-mean_value(sLenghtVec))/standard_deviation(sLenghtVec);
     sWidthVec.at(i)=(sWidthVec.at(i)-mean_value(sWidthVec))/standard_deviation(sWidthVec);
     pLenghtVec.at(i)=(pLenghtVec.at(i)-mean_value(pLenghtVec))/standard_deviation(pLenghtVec);
     pWidthVec.at(i)=(pWidthVec.at(i)-mean_value(pWidthVec))/standard_deviation(pWidthVec);




  }


  float covarianceMatrix[4][4];

  // Diagonal Elements
  covarianceMatrix[0][0] = covariance(pLenghtVec,pLenghtVec);
  covarianceMatrix[1][1] = covariance(pWidthVec,pWidthVec);
  covarianceMatrix[2][2] = covariance(sLenghtVec,sLenghtVec);
  covarianceMatrix[3][3] = covariance(sWidthVec,sWidthVec);

  covarianceMatrix[0][1] = covariance(pLenghtVec,pWidthVec);
  covarianceMatrix[0][2] = covariance(pLenghtVec,sLenghtVec);
  covarianceMatrix[0][3] = covariance(pLenghtVec,sWidthVec);

  covarianceMatrix[1][2] = covariance(pWidthVec,sLenghtVec);
  covarianceMatrix[1][3] = covariance(pWidthVec,sWidthVec);


  covarianceMatrix[3][2] = covarianceMatrix[2][3];

  covarianceMatrix[1][0] = covarianceMatrix[0][1];
  covarianceMatrix[2][0] = covarianceMatrix[0][2];
  covarianceMatrix[3][0] = covarianceMatrix[0][3];

  covarianceMatrix[2][1] = covarianceMatrix[1][2];
  covarianceMatrix[3][1] = covarianceMatrix[1][3];

  cout<<"COVARIANCE MATRIX: "<<endl;

  for(int  i = 0 ; i < 4; i++){

   for(int j= 0 ; j < 4 ; j++){

   cout<<covarianceMatrix[i][j]<<"      ";

   }
   cout<<endl;
}

}
