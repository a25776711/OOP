//
// Created by bingho on 2025/3/11.
//

#ifndef FASTSHOOTER_HPP
#define FASTSHOOTER_HPP
#include "Plant/plant.hpp"

class Fastshooter:public Plant {
    public:
    explicit Fastshooter():Plant(m_Loader.fastshooterIMG,70) {
        SetHP();SetCost(200);SetType(Shooter);
    }

    private:
    int m_cooldown;

};
#endif //ICESHOOTER_HPP
