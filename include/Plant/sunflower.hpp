//
// Created by bingho on 2025/3/11.
//

#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP
#include "Plant/plant.hpp"
#include "sun.hpp"
class SunFlower : public Plant {
public:
    enum class Shine {
        Ing,
        No
    };
    SunFlower():Plant(m_Loader.sunflowerIMG,60) {
        SetHP();
        SetCost(50);
        SetType(Idle);
    }

    
private:
    int m_Cooldown;
};
#endif //SUNFLOWER_HPP
