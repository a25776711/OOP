//
// Created by bingho on 2025/3/11.
//
#include "Plant/wallnut.hpp"

void Wallnut::Hurt() {
    int hp=GetHP()-1;
    SetHP(hp);
    if(hp<47&&24<=hp) {
        m_Drawable=std::make_shared<Util::Animation>(m_Loader.wallnutIMG_1,true,70,true,0);
    }else if(hp<24) {
        m_Drawable=std::make_shared<Util::Animation>(m_Loader.wallnutIMG_2,true,70,true,0);
    }

}

