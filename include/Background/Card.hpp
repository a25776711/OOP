#ifndef CARD_HPP
#define CARD_HPP

#include "GameObject.hpp"
#include "Util/Image.hpp"
#include "Plant/sunflower.hpp"
#include "Plant/mine.hpp"
#include "Plant/cherrybomb.hpp"
#include "Plant/wallnut.hpp"
#include "Plant/chomper.hpp"
#include "Plant/iceshooter.hpp"
#include "Plant/fastshooter.hpp"
#include "Plant/peashooter.hpp"
#include <string>
#include <memory>

class Card : public GameObject {
public:
      Card(const std::string& imagePath,int index) {
            auto image = std::make_shared<Util::Image>(imagePath);
            SetDrawable(image);
            this->index = index;
      }
      std::shared_ptr<Plant> MakePlant(int level) {
            std::vector<std::shared_ptr<Plant>>m_GPlants={
                  std::make_shared<Peashooter>(),
                      std::make_shared<SunFlower>(),
                      std::make_shared<Cherrybomb>(),
                      std::make_shared<Wallnut>(),
                      std::make_shared<Mine>(),
                      std::make_shared<Iceshooter>(),
                      std::make_shared<Chomper>(),
                      std::make_shared<Fastshooter>(),
                      std::make_shared<Play_wallnut>()
                  };
            if(index>8||index<1)return nullptr;
            if(level==5&&index==4){
                  return m_GPlants[8];
            }
            m_GPlants[index-1]->SetZIndex(50);
            return m_GPlants[index-1];
      }
      void SetPos(glm::vec2 pos) {
            m_Transform.translation=pos;
            four_points={pos.x-30,pos.y-40,pos.x+30,pos.y+40};
      }
      std::vector<float>GetFourPoints() {return four_points;}
      private:
      int index;
      std::vector<float> four_points;
};

#endif // CARD_HPP
