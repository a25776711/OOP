//
// Created by bingho on 2025/3/11.
//

#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP
#include "Plant/plant.hpp"

class Cherrybomb:public Plant {
    public:
    explicit  Cherrybomb():Plant(m_Loader.cherryIMG,70) {
        SetATK(90);SetCost(150);SetType(T_Bomb);SetTakeCD(3000);
    }
    bool Attack(std::vector<std::shared_ptr<zombi>> &zombis){
        if(!showboom&&IfAnimationEnds()){
            m_Drawable=std::make_shared<Util::Animation>(m_Loader.cherryIMG_Boom,false,2000,false,100);
            for(auto &zombi:zombis){
                if(abs(zombi->GetPosition().x-GetPosition().x)<140&&abs(zombi->GetPosition().y-GetPosition().y)<150){
                    zombi->GetHeart(true,false,GetATK());
                }
            }
            showboom=true;
            showover=0;
        }
        else if(showboom&&showover>=30){
            return true;
        }
        else if(showboom){
            showover++;
        }
        return false;

    }
    

    private:
    bool showboom=false;
    int showover=false;
};
#endif //CHERRYBOMB_HPP
