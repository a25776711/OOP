//
// Created by bingho on 2025/3/11.
//

#ifndef CHOMPER_HPP
#define CHOMPER_HPP
#include "Plant/plant.hpp"

class Chomper:public Plant {
    public:
    Chomper():Plant(m_Loader.chomperIMG,70) {
        SetHP();
        SetCost(150);
        SetType(T_Chomper);
    }
    private:
    int m_Cooldown;
    bool m_eating;

};
#endif //CHOMPER_HPP
