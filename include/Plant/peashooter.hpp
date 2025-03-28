//
// Created by bingho on 2025/3/11.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include "plant.hpp"

class Peashooter : public Plant {
public:
    explicit Peashooter(int interval=100):Plant(m_Loader.peashooterIMG,60) {
        SetATK(10);
    }
    bool Attack (glm::vec2) {
        
    }
protected:
    int m_cooldown;
};

#endif //PEASHOOTER_HPP
