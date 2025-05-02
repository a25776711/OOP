//
// Created by bingho on 2025/3/11.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "plant.hpp"
class Wallnut : public Plant {
    public:
    explicit  Wallnut():Plant(m_Loader.wallnutIMG,70) {
        SetHP(3600);
        SetCost(50);
        SetTakeCD(1800);
        SetType(T_WallNut);
    }
    void Hurt() override;
    private:

};
class play_wallnut:public Plant{
    public:
    play_wallnut():Plant(m_Loader.wallnutIMG,70){
        SetHP(72);
        SetCost(50);
    }
};
#endif //WALLNUT_HPP
