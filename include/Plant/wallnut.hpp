//
// Created by bingho on 2025/3/11.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "plant.hpp"
class Wallnut : public Plant {
    public:
    explicit  Wallnut():Plant(m_Loader.wallnutIMG,70) {
        SetHP(72);
        SetCost(50);
        SetType(WallNut);
    }
    void Hurt() override;
    private:

};
#endif //WALLNUT_HPP
