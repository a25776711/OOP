//
// Created by bingho on 2025/3/11.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include "plant.hpp"
#include "Bullet/normalbullet.hpp"

class Peashooter : public Plant {
public:
    explicit Peashooter():Plant(m_Loader.peashooterIMG,60) {
        SetATK(1);
        SetHP();
        SetType(T_Shooter);
    }
    bool AttackCheck(std::vector<glm::vec2> pos);
    std::shared_ptr<Bullet> Attack(std::vector<glm::vec2> pos);
protected:
    int m_cooldown=90;
};

#endif //PEASHOOTER_HPP
