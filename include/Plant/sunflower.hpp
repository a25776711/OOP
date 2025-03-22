//
// Created by bingho on 2025/3/11.
//

#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP
#include "Plant/plant.hpp"
#include "sun.hpp"
class SunFlower : public Plant {
public:
    SunFlower(int hp,std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {

    }
    
private:
    int m_Cooldown;
};
#endif //SUNFLOWER_HPP
