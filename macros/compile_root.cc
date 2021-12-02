#include "TH1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "R3BCalifaGeometry.h"
#include "R3BCalifaGeometry.cxx"

#include "TVector3.h"
#include "TMath.h"
#include <iostream>
#include "Logger.h"

int main(){

   TApplication* theApp = new TApplication("App", 0, 0);


   TVector3 vec;
   R3BCalifaGeometry * geo = new R3BCalifaGeometry(2021);

   TCanvas *one_canvas = new TCanvas("one","two");

   for(int i = 0;i<2432;i++){

     vec=geo->GetAngles(i+1);
     std::cout<<" Crystal ID : "<<i+1<<" Angles : "<<TMath::RadToDeg()*vec.Theta()<<" "<<TMath::RadToDeg()*vec.Phi()<<std::endl;

   }


   theApp->Run();
   theApp->Terminate(1);


}
