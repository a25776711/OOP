//
// Created by bingho on 2025/3/11.
//

#ifndef CHOMPER_HPP
#define CHOMPER_HPP
#include "Plant/plant.hpp"

class Chomper:public Plant {
    public:
    enum class ChomperState {
        Idle,
        Eat,
        Eating
    };
    bool CoolDown()override {
        if(m_Cooldown>=450){
            m_Drawable=std::make_shared<Util::Animation>(m_Loader.chomperIMG_1,true,100,false,0);
            m_state=ChomperState::Eat;
            return true;
        }
        m_Cooldown++;return false;
    }
    Chomper():Plant(m_Loader.chomperIMG,70) {
        SetHP();
        SetCost(150);
        SetTakeCD(450);
        SetType(T_Chomper);
        m_state=ChomperState::Idle;
    }
    std::shared_ptr<zombi> Attack(std::vector<std::shared_ptr<zombi>> &zombis){
        if(m_Cooldown==0&&m_state==ChomperState::Eating){
            m_state=ChomperState::Idle;
            m_Drawable=std::make_shared<Util::Animation>(m_Loader.chomperIMG,true,100,true,0);
            m_z=nullptr;
            return nullptr;
        }
        else if(m_state==ChomperState::Eating){
            m_Cooldown--;
            return nullptr;
        }
        else if(m_state==ChomperState::Idle){
            for(auto &zombie:zombis){
                if(zombie->GetState()!=zombi::zombistate::die&&
                zombie->GetPosition().x-GetPosition().x<40&&
                abs(zombie->GetPosition().y-GetPosition().y)<50){
                    m_z=zombie;
                    m_state=ChomperState::Eat;
                    m_Drawable=std::make_shared<Util::Animation>(m_Loader.chomperIMG_1,true,100,false,0);
                    return nullptr;
                }
            }
            return nullptr;
        }else if(m_state==ChomperState::Eat){
            if(IfAnimationEnds()){
                auto temp = m_z;  // 保存殭屍指針
                m_state=ChomperState::Eating;
                m_Drawable=std::make_shared<Util::Animation>(m_Loader.chomperIMG_2,true,100,true,0);
                m_Cooldown=2400;
                m_z = nullptr;    // 清除殭屍指針
                return temp;      // 返回保存的指針
            }else{
                return nullptr;
            }
        }
    }
    private:
    int m_Cooldown=0;
    ChomperState m_state;
    std::shared_ptr<zombi> m_z=nullptr;

};
#endif //CHOMPER_HPP
