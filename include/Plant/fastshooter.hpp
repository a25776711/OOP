//
// Created by bingho on 2025/3/11.
//

#ifndef FASTSHOOTER_HPP
#define FASTSHOOTER_HPP
#include "Plant/plant.hpp"
#include "Bullet/normalbullet.hpp"

class Fastshooter:public Plant {
    public:
    explicit Fastshooter():Plant(m_Loader.fastshooterIMG,70) {
        SetHP();SetCost(200);SetType(T_Shooter);
    }
    bool AttackCheck(glm::vec2 pos);
    std::shared_ptr<Bullet> Attack(glm::vec2 pos) override;
    private:
    int m_cooldown1;
    int bcount=0;
};
#endif //ICESHOOTER_HPP
