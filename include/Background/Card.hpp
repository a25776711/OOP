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
            m_Transform.scale = {0.45,0.45};
            
            m_createPlant = GetNewPlant(index);
            if(m_createPlant) {
                m_cooldown = m_createPlant->GetTakeCD();
            }
            m_isCreate = true;
      }

      std::shared_ptr<Plant> MakePlant(int level) {
            if(!m_isCreate) return nullptr;
            
            if(level==5 && index==4){
                  auto plant = GetNewPlant(9);
                  if(plant) {
                        plant->SetZIndex(20);
                        m_isCreate = false;
                        return plant;
                  }
                  return nullptr;
            }
            m_createPlant=GetNewPlant(index);
            if(m_createPlant) {
                m_createPlant->SetZIndex(20);

                m_isCreate = false;
                return m_createPlant;
            }
            
            return nullptr;
      }
      void SetPos(glm::vec2 pos) {
            m_Transform.translation=pos;
            four_points={pos.x-30,pos.y-40,pos.x+30,pos.y+40};
      }
      void Reset(){m_createPlant=GetNewPlant(index);m_cooldown=m_createPlant->GetTakeCD();m_isCreate=true;}
      Plant::PlantType GetType(){return m_createPlant->GetType();}
      void Create(){m_isCreate=false;}
      bool IfCreate() {return m_isCreate;}
      int GetCost(){return m_createPlant->GetCost();}
      std::vector<float>GetFourPoints() {return four_points;}
      void ResetFourPoints() {
            four_points={m_Transform.translation.x-25,m_Transform.translation.y-35,m_Transform.translation.x+25,m_Transform.translation.y+35};
      }
      void Update(){
            if(m_isCreate)return;
            m_cooldown--;
            if(m_cooldown<=0){
                  m_cooldown=m_createPlant->GetTakeCD();
                  m_isCreate=true;
            }
      }
      private:
      int index;
      int m_cooldown;
      bool m_isCreate=true;

      std::vector<float> four_points;
      std::shared_ptr<Plant> m_createPlant;
      std::shared_ptr<Plant> GetNewPlant(int index){
            switch(index){
                  case 1:return std::make_shared<Peashooter>();
                  case 2:return std::make_shared<SunFlower>();
                  case 3:return std::make_shared<Cherrybomb>();
                  case 4:return std::make_shared<Wallnut>();
                  case 5:return std::make_shared<Mine>();
                  case 6:return std::make_shared<Iceshooter>();
                  case 7:return std::make_shared<Chomper>();
                  case 8:return std::make_shared<Fastshooter>();
                  case 9:return std::make_shared<Play_wallnut>();
                  default:return nullptr;
            }
      }
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
};

#endif // CARD_HPP
