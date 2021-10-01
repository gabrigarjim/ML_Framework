////////////////////////////////////////////////////////////////////////////////
//                               Some Statistical Functions                   //
//                                   GGJ, September 2021                      //
////////////////////////////////////////////////////////////////////////////////

#include "headers.h"

using namespace std;


// -----------  Calculating mean of a given vector ----------

float mean_value(vector<float> values){

   float mean = accumulate(values.begin(),values.end(),0);

   mean = mean/values.size();

   return mean;

}


// ---------- Variance -----------

float variance(vector<float> values){

  float mean = mean_value(values);

  float var = 0.0;

  for(int i = 0; i < values.size(); i++)
   var = var + pow(values.at(i)-mean,2);

   return var/values.size();
}


// ---------------- Covariance -----------------

float covariance(vector<float> firstFeature, vector<float> secondFeature){

 if (firstFeature.size() != secondFeature.size()){

  cout<<"Dimensions don't match !!!!!!"<<endl;
  return -1;

 }

 else {

  float firstMean  = mean_value(firstFeature);
  float secondMean = mean_value(secondFeature);

   float cov=0.0;


   for(int j = 0 ; j<firstFeature.size(); j++)
       cov = cov + (firstFeature.at(j)-firstMean)*(secondFeature.at(j)-secondMean);


   return cov/(firstFeature.size()-1);

 }
}

// --------------- Standard Deviation ----------------

float standard_deviation(vector<float> values){

  return sqrt(variance(values));

}
