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
        SetHP();SetCost(200);SetType(Plant::T_FastShooter);SetTakeCD(450);
    }
    bool AttackCheck(std::vector<glm::vec2> pos);
    std::shared_ptr<Bullet> Attack(std::vector<glm::vec2> pos);
    private:
    int m_cooldown1=90;
    int bcount=0;
};
#endif //ICESHOOTER_HPP
