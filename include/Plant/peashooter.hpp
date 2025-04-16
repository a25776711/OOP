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
        SetType(Shooter);
    }
    bool AttackCheck(glm::vec2 pos);
    std::shared_ptr<Bullet> Attack(glm::vec2 pos) override;
protected:
    int m_cooldown=0;
};

#endif //PEASHOOTER_HPP
