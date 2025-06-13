//
// Created by bingho on 2025/3/11.
//

#ifndef ICESHOOTER_HPP
#define ICESHOOTER_HPP
#include "Plant/plant.hpp"
#include "Bullet/icebullet.hpp"
#include "Zombi/zombi.hpp"
class Iceshooter:public Plant {
    public:
    explicit Iceshooter():Plant(m_Loader.icepeashooterIMG,70) {
        SetHP();SetCost(175);SetType(Plant::T_IceShooter);SetTakeCD(450);

    }
    bool AttackCheck(std::vector<std::shared_ptr<zombi>> zom);
    std::shared_ptr<Bullet> Attack(std::vector<std::shared_ptr<zombi>> zom);

    private:
    int m_cooldown=90;

};
#endif //ICESHOOTER_HPP
