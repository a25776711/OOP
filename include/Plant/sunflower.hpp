//
// Created by bingho on 2025/3/11.
//

#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP
#include "Plant/plant.hpp"
class SunFlower : public Plant {
public:
    SunSunFlower(int hp,std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {
        m_hp=m_maxhp=hp;
    }
private:
    int m_hp;
    int m_maxhp;
    int cooldown;
};
#endif //SUNFLOWER_HPP
