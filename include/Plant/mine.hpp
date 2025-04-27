//
// Created by bingho on 2025/3/11.
//

#ifndef MINE_HPP
#define MINE_HPP
#include "Plant/plant.hpp"
#include "Zombi/zombi.hpp"
class Mine : public Plant {
    public:
    Mine():Plant(m_Loader.mineIMG_1,100) {
        SetHP();SetCost(25);SetType(T_Mine);
    }
    bool CoolDown()override {
        if(m_Cooldown>=600){
            if(!m_poob) {
                m_Drawable=std::make_shared<Util::Animation>(m_Loader.mineIMG,true,100,true,0);
            }

            m_poob=true;
            return true;}

        m_Cooldown++;return false;
    }
    bool Attack(std::vector<std::shared_ptr<zombi>> &zombis){
        if(CoolDown()&&!m_isActive){
            for(auto &zombie:zombis){
                if(!m_isActive&&
                zombie->GetState()!=zombi::zombistate::die&&
                abs(zombie->GetPosition().y-GetPosition().y)<50&&
                zombie->GetPosition().x<GetPosition().x+40){
                    zombie->GetHeart(false,false,100);
                    std::cout << "Mine" << std::endl;
                    m_isActive=true;
                }
            }
        }
        if(m_isActive&&m_time<120){
            m_Drawable=std::make_shared<Util::Animation>(m_Loader.mineIMG_boom,false,2000,false,100);
            m_time++;
            return false;
        }
        if(m_time>=120){
            return true;
        }
        return false;
    }
    private:
    int m_Cooldown=0;
    bool m_poob=false;
    bool m_isActive=false;
    int m_time=0;
};

#endif //MINE_HPP
