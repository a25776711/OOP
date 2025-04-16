//
// Created by bingho on 2025/3/11.
//

#ifndef MINE_HPP
#define MINE_HPP
#include "Plant/plant.hpp"
class Mine : public Plant {
    public:
    Mine():Plant(m_Loader.mineIMG,100) {
        SetHP();SetCost(25);SetType(Boom);
    }
    private:
    int m_Cooldown;
};

#endif //MINE_HPP
