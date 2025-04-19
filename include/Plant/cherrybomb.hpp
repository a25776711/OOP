//
// Created by bingho on 2025/3/11.
//

#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP
#include "Plant/plant.hpp"

class Cherrybomb:public Plant {
    public:
    explicit  Cherrybomb():Plant(m_Loader.cherryIMG,70) {
        SetATK(90);SetCost(150);SetType(Boom);
    }

    private:
};
#endif //CHERRYBOMB_HPP
