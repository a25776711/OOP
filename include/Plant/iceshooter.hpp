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
    bool AttackCheck(std::vector<glm::vec2> pos);
    std::shared_ptr<Bullet> Attack(std::vector<glm::vec2> pos);

    private:
    int m_cooldown=90;

};
#endif //ICESHOOTER_HPP
