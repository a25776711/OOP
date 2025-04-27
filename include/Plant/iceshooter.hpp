//
// Created by bingho on 2025/3/11.
//

#ifndef ICESHOOTER_HPP
#define ICESHOOTER_HPP
#include "Plant/plant.hpp"
#include "Bullet/icebullet.hpp"
class Iceshooter:public Plant {
    public:
    explicit Iceshooter():Plant(m_Loader.icepeashooterIMG,70) {
        SetHP();SetCost(175);SetType(T_Shooter);

    }
    bool AttackCheck(glm::vec2 pos);
    std::shared_ptr<Bullet> Attack(glm::vec2 pos) override;

    private:
    int m_cooldown;

};
#endif //ICESHOOTER_HPP
