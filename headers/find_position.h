#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf

void find_position(Int_t fCrystalId, Int_t *columnIndex, Int_t *rowIndex, Int_t idMatrix[][64]){

     for(int i = 0 ; i < 25 ; i++) {
      for(int j = 0 ; j < 64 ; j++) {

        if(idMatrix[i][j]==fCrystalId){
         *rowIndex = i;
         *columnIndex = j;
          break;

        }
        
      }
    }


 }
