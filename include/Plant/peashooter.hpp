//
// Created by bingho on 2025/3/11.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP
#include "plant.hpp"

class Peashooter : public Plant {
public:
    explicit Peashooter(int ATK,std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {
        SetATK(ATK);
    }
    bool Attack (glm::vec2) {
        
    }
protected:
    int m_cooldown;
};

#endif //PEASHOOTER_HPP
