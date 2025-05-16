//
// Created by a2577 on 25-3-21.
//

#ifndef PLANTLOADER_HPP
#define PLANTLOADER_HPP
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class PlantLoader{
  public:
  static PlantLoader& GetInstance() {
    static PlantLoader instance;
    return instance;
  }
  
  PlantLoader() {
    loadPlantImages();
  }

  // 預加載所有圖片資源
  void PreloadAllImages() {
    if (!m_IsPreloaded) {
      loadPlantImages();
      m_IsPreloaded = true;
    }
  }

  std::vector<std::string> sunflowerIMG;
  std::vector<std::string> sunflowerIMG_1;
  std::vector<std::string> sunIMG;
  std::vector<std::string> mineIMG;
  std::vector<std::string> mineIMG_1;
  std::vector<std::string> mineIMG_boom;
  std::vector<std::string> peashooterIMG;
  std::vector<std::string> fastshooterIMG;
  std::vector<std::string> wallnutIMG;
  std::vector<std::string> wallnutIMG_1;
  std::vector<std::string> wallnutIMG_2;
  std::vector<std::string> wallnutIMG_Boom;
  std::vector<std::string> icepeashooterIMG;
  std::vector<std::string> chomperIMG;
  std::vector<std::string> chomperIMG_1;
  std::vector<std::string> chomperIMG_2;
  std::vector<std::string> cherryIMG;
  std::vector<std::string> cherryIMG_Boom;
  std::vector<std::string> shovelIMG;
  std::vector<std::string> shovelIMG_1;

  private:
  bool m_IsPreloaded = false;

  void loadPlantImages(){
    std::string path=RESOURCE_DIR"/plant/";
    // 使用預分配的容量來減少重新分配
    sunflowerIMG.reserve(24);
    sunflowerIMG_1.reserve(24);
    sunIMG.reserve(12);
    mineIMG.reserve(8);
    peashooterIMG.reserve(24);
    fastshooterIMG.reserve(15);
    wallnutIMG.reserve(32);
    wallnutIMG_1.reserve(11);
    wallnutIMG_2.reserve(32);
    icepeashooterIMG.reserve(15);
    chomperIMG.reserve(13);
    chomperIMG_1.reserve(9);
    chomperIMG_2.reserve(6);
    cherryIMG.reserve(14);
    for(int i = 0; i < 24; i++)
      sunflowerIMG.emplace_back(path+"sunflower/sunflower_" + std::to_string(i) + ".png");
    for(int i = 0; i < 24; i++)
      sunflowerIMG_1.emplace_back(path+"sunflower_1/sunflower_1_" + std::to_string(i) + ".png");
    for(int i = 0; i < 12; i++)
      sunIMG.emplace_back(path+"sun/sun_"+std::to_string(i) + ".png");
    for(int i = 0; i < 8; i++)
      mineIMG.emplace_back(path+"mine/mine_" + std::to_string(i) + ".png");
    mineIMG_1.emplace_back(path+"mine_1.png");
    mineIMG_boom.emplace_back(path+"boom.png");
    for(int i = 0; i < 24; i++)
      peashooterIMG.emplace_back(path+"Peashooter/peashooter_" + std::to_string(i) + ".png");
    for(int i = 1; i < 16; i++)
      fastshooterIMG.emplace_back(path+"fastshooter/fastshooter_" + std::to_string(i) + ".png");
    for(int i = 0; i < 32; i++)
      wallnutIMG.emplace_back(path+"wallnut/wallnut_" + std::to_string(i) + ".png");
    for(int i = 0; i < 11; i++)
      wallnutIMG_1.emplace_back(path+"wallnut_1/wallnut_1_" + std::to_string(i) + ".png");
    for(int i = 0; i < 32; i++)
      wallnutIMG_2.emplace_back(path+"wallnut_2/wallnut_2_" + std::to_string(i) + ".png");
    wallnutIMG_Boom.emplace_back(path+"wallnut_B.png");
    for(int i = 0; i < 15; i++)
      icepeashooterIMG.emplace_back(path+"iceshooter/iceshooter_" + std::to_string(i) + ".png");
    for(int i = 0; i < 13; i++)
      chomperIMG.emplace_back(path+"chomper/chomper_" + std::to_string(i) + ".png");
    for(int i = 0; i < 9; i++)
      chomperIMG_1.emplace_back(path+"chomper_1/chomper_1_" + std::to_string(i) + ".png");
    for(int i = 0; i < 6; i++)
      chomperIMG_2.emplace_back(path+"chomper_2/chomper_2_" + std::to_string(i) + ".png");
    for(int i = 0; i < 14; i++)
      cherryIMG.emplace_back(path+"cherrybomb/cherrybomb_" + std::to_string(i) + ".png");
    cherryIMG_Boom.emplace_back(path+"explosion.png");
    shovelIMG.emplace_back(RESOURCE_DIR"/Background/Shovel.png");
    shovelIMG_1.emplace_back(RESOURCE_DIR"/Background/Shovel_take.png");
  }

  PlantLoader(const PlantLoader&) = delete;
  PlantLoader& operator=(const PlantLoader&) = delete;
};
#endif //PLANTLOADER_HPP
