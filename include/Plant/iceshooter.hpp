/
// Created by bingho on 2025/3/11.
//

#ifndef ICESHOOTER_HPP
#define ICESHOOTER_HPP
#include "Plant/plant.hpp"
class Iceshooter:public Plant {
    public:
    explicit Iceshooter():Plant(m_Loader.icepeashooterIMG){}

    private:
    int m_cooldown;

};
#endif //ICESHOOTER_HPP
