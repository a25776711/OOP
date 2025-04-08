//
// Created by bingho on 2025/3/11.
//

#ifndef ICESHOOTER_HPP
#define ICESHOOTER_HPP
#include "Plant/plant.hpp"
class Fastshooter:public Plant {
    public:
    explicit Fastshooter():Plant(m_Loader.fastshooterIMG){}

    private:
    int m_cooldown;

};
#endif //ICESHOOTER_HPP
