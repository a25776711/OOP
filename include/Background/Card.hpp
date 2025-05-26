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
            SetZIndex(10);
            m_createPlant = GetNewPlant(index);
            if(m_createPlant) {
                m_cooldown = m_createPlant->GetTakeCD();
            }
            m_isCreate = true;
            m_image=RESOURCE_DIR "/Background/Card/card"+std::to_string(index)+".png";
            m_image_CD=RESOURCE_DIR "/Background/Card/card"+std::to_string(index)+"_CD.png";
      }

      std::shared_ptr<Plant> MakePlant() {
            if(!m_isCreate) return nullptr;
            m_createPlant=GetNewPlant(index);
            m_createPlant->SetZIndex(20);
            return m_createPlant;
      }
      void SetPos(glm::vec2 pos) {
            m_Transform.translation=pos;
            four_points={pos.x-30,pos.y-40,pos.x+30,pos.y+40};
      }
      void Reset(){
            auto temp=std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            temp->SetImage(RESOURCE_DIR "/Background/Card/card"+std::to_string(index)+".png");
            m_createPlant=GetNewPlant(index);
            m_cooldown=m_createPlant->GetTakeCD();
            m_isCreate=true;
      }
      Plant::PlantType GetType(){return m_createPlant->GetType();}
      void Create(){
            if(m_createPlant) {
                m_createPlant->SetZIndex(20);
                if(m_createPlant->GetTakeCD()==0)return;
                m_isCreate = false;
                auto temp=std::dynamic_pointer_cast<Util::Image>(m_Drawable);
                temp->SetImage(m_image_CD);
            }
      }
      bool IfCreate() {return m_isCreate;}
      int GetIndex(){return index;}
      int GetCost(int level){
            if(level==5&&index==4)return 0;
            return m_createPlant->GetCost();}
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
                  auto temp=std::dynamic_pointer_cast<Util::Image>(m_Drawable);
                  temp->SetImage(m_image);
            }
      }
      private:
      int index;
      int m_cooldown;
      bool m_isCreate=true;
      std::string m_image;
      std::string m_image_CD;
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
                  case 10:return std::make_shared<Play_wallnut_boom>();
                  default:return nullptr;
            }
      }
};

#endif // CARD_HPP
