//
// Created by bingho on 2025/3/20.
//

#ifndef ADVENTURE_HPP
#define ADVENTURE_HPP

#include "GameObject.hpp"
#include "Util/Image.hpp"
#include <string>
#include "Plant/plant.hpp"


class adventure : public GameObject{
    public:
        explicit  adventure():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/Adventure_1.png"), -5){
            
        }
        void ChangeImage() {
            auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
                return temp -> SetImage(RESOURCE_DIR"/Background/Adventure.png");
        }
        void NextLevel(int level){
            auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            if (level==0) {
                temp -> SetImage(RESOURCE_DIR"/Background/Adventure_1.png");
            }
            else {
                temp -> SetImage(RESOURCE_DIR"/Background/list.png");
            }
        }
    private:
};
class ShovelBlock : public GameObject{
    public:
        explicit  ShovelBlock():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/ShovelBlock.png"), -4){
            SetVisible(false);
            m_Transform.scale={1.3f,1.3f};
        }
        void NextLevel(int level){
            if (level<=4) 
                SetVisible(false);
            else
                SetVisible(true);
        }
    private:
};
class Shovel : public Plant{
    public:
        explicit Shovel():Plant(m_Loader.shovelIMG){
            isTaken = false;
            SetType(T_Shovel);
            SetZIndex(-3);
            SetVisible(false);
            m_Transform.translation = {300, 280};

        }
        void ChangeImage(){
            if(isTaken)
                m_Drawable = std::make_shared<Util::Animation>(m_Loader.shovelIMG_1, false, 100, true, 100);
            else
                m_Drawable = std::make_shared<Util::Animation>(m_Loader.shovelIMG, false, 100, true, 100);
        }
        
        void TakeShovel(){
            isTaken = true;
            ChangeImage();
        }
        void SetPoints(){
            auto pos=GetPosition();
            SetFourPoints({pos.x-40,pos.y-20,pos.x+40,pos.y+20});
        }
        void UseShovel(){
            isTaken = false;
            m_Transform.translation = {410, 280};
            ChangeImage();
            SetPoints();
        }
        void NextLevel(int level){
            if (level<=4) 
                SetVisible(false);
            else
                SetVisible(true);
        }
    private:
        bool isTaken;
        
};

class T_road : public GameObject{
    public:
        explicit T_road():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/t_road.png"), -2){
            SetVisible(false);
            m_Transform.translation={-270,320};
            m_Transform.scale={1.3f,1.3f};
        }
        
};
#endif //ADVENTURE_HPP
