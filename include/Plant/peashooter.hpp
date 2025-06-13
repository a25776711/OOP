//
// Created by bingho on 2025/3/11.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include "plant.hpp"
#include "Bullet/normalbullet.hpp"
#include "Zombi/zombi.hpp"

class Peashooter : public Plant {
public:
    explicit Peashooter():Plant(m_Loader.peashooterIMG,60) {
        SetATK(1);
        SetHP();
        SetCost(100);
        SetTakeCD(450);
        SetType(Plant::T_Peashooter);
    }
    bool AttackCheck(std::vector<std::shared_ptr<zombi>> zom);
    std::shared_ptr<Bullet> Attack(std::vector<std::shared_ptr<zombi>> zom);
protected:
    int m_cooldown=90;
};

#endif //PEASHOOTER_HPP
