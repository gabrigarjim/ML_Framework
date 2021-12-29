#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf

void create_califa_matrix(){

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

  




 }
