//
// Created by a2577 on 25-3-21.
//

#ifndef PLANTLOADER_HPP
#define PLANTLOADER_HPP
#include <string>
#include <vector>

class PlantLoader{
  public:
  std::vector<std::string> sunflowerIMG;
  std::vector<std::string> sunflowerIMG_1;
  std::vector<std::string> sunIMG;
  std::vector<std::string> mineIMG;
  std::vector<std::string> peashooterIMG;
  std::vector<std::string> wallnutIMG;
  std::vector<std::string> wallnutIMG_1;
  std::vector<std::string> wallnutIMG_2;
  std::vector<std::string> icepeashooterIMG;
  std::vector<std::string> chomperIMG;
  std::vector<std::string> chomperIMG_1;
  std::vector<std::string> chomperIMG_2;
  std::vector<std::string> cherryIMG;
  std::string peaIMG;
  std::string icepeaIMG;
  void loadPlantImages(){
    std::string path=RESOURCE_DIR"/plant/";
    for(int i = 0; i < 24; i++)
      sunflowerIMG.emplace_back(path+"sunflower_" + std::to_string(i) + ".png");
    for(int i = 0; i < 24; i++)
      sunflowerIMG_1.emplace_back(path+"sunflower_1_" + std::to_string(i) + ".png");
    for(int i = 0; i < 12; i++)
      sunIMG.emplace_back(path+"sun_"+std::to_string(i) + ".png");
    for(int i = 0; i < 8; i++)
      mineIMG.emplace_back(path+"mine_" + std::to_string(i) + ".png");
    for(int i = 0; i < 24; i++)
      peashooterIMG.emplace_back(path+"peashooter_" + std::to_string(i) + ".png");
    for(int i = 0; i < 32; i++)
      wallnutIMG.emplace_back(path+"wallnut_" + std::to_string(i) + ".png");
    for(int i = 0; i < 11; i++)
      wallnutIMG_1.emplace_back(path+"wallnut_1_" + std::to_string(i) + ".png");
    for(int i = 0; i < 32; i++)
      wallnutIMG_2.emplace_back(path+"wallnut_2_" + std::to_string(i) + ".png");
    for(int i = 0; i < 15; i++)
      icepeashooterIMG.emplace_back(path+"iceshooter_" + std::to_string(i) + ".png");
    for(int i = 0; i < 13; i++)
      chomperIMG.emplace_back(path+"chomper_" + std::to_string(i) + ".png");
    for(int i = 0; i < 9; i++)
      chomperIMG_1.emplace_back(path+"chomper_1_" + std::to_string(i) + ".png");
    for(int i = 0; i < 6; i++)
      chomperIMG_2.emplace_back(path+"chomper_2_" + std::to_string(i) + ".png");
    for(int i = 0; i < 14; i++)
      cherryIMG.emplace_back(path+"cherrybomb_" + std::to_string(i) + ".png");
    peaIMG=path+"pee/pea.png";
    icepeaIMG=path+"pee/icepea.png";
  }
};
#endif //PLANTLOADER_HPP
