
  struct preamp_struct {

   Int_t crystalIds[14]={0};

 };



  void printPreamp (std::vector<preamp_struct> preamp_vector, Int_t preamp) {

      cout<<"Printing Preamp "<<preamp<<endl;
      cout<<preamp_vector.at(preamp-1).crystalIds[3]<<" "<<preamp_vector.at(preamp-1).crystalIds[2]<<" "<<preamp_vector.at(preamp-1).crystalIds[1]<<" "<<preamp_vector.at(preamp-1).crystalIds[0]<<endl;
      cout<<preamp_vector.at(preamp-1).crystalIds[7]<<" "<<preamp_vector.at(preamp-1).crystalIds[6]<<" "<<preamp_vector.at(preamp-1).crystalIds[5]<<" "<<preamp_vector.at(preamp-1).crystalIds[4]<<endl;
      cout<<preamp_vector.at(preamp-1).crystalIds[9]<<" "<<preamp_vector.at(preamp-1).crystalIds[8]<<endl;
      cout<<preamp_vector.at(preamp-1).crystalIds[11]<<" "<<preamp_vector.at(preamp-1).crystalIds[10]<<endl;
      cout<<preamp_vector.at(preamp-1).crystalIds[13]<<" "<<preamp_vector.at(preamp-1).crystalIds[12]<<endl;

      cout<<endl;

  }




  void get_id_matrix(){



    TString mappingFile = "../params/Califa_Mapping_3March2021.par";

    R3BCalifaMappingPar *califaMapPar;

    FairParAsciiFileIo *inputAscii = new FairParAsciiFileIo();

    FairRuntimeDb *rtdb = FairRuntimeDb::instance();

    califaMapPar = (R3BCalifaMappingPar *)rtdb->getContainer("califaMappingPar");

    inputAscii->open(mappingFile, "in");

    rtdb->setFirstInput(inputAscii);

    rtdb->initContainers(1);

    Int_t half, ring, preamp, channel;

    preamp_struct p;
    std::vector<preamp_struct> preamp_vector;

    for(int i = 0; i<16;i++)
     preamp_vector.push_back(p);


    for(int j = 1 ; j < 4864 ; j++){


      if(califaMapPar->GetInUse(j)){

       half = califaMapPar->GetHalf(j);
       ring = califaMapPar->GetRing(j);
       preamp = califaMapPar->GetPreamp(j);
       channel = califaMapPar->GetChannel(j);

       if(half == 2 && ring == 5 && preamp%2 == 0)
         preamp_vector.at(preamp-1).crystalIds[channel-1]=j;

        }
      }


     for(int i = 1; i<9;i++)
      printPreamp(preamp_vector,2*i);

}
