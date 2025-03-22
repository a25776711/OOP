//
// Created by bingho on 2025/3/11.
//

#ifndef MINE_HPP
#define MINE_HPP
#include "Plant/plant.hpp"
class Mine : public Plant {
    public:
    Mine(int hp,std::vector<std::string>& Path,int interval=100):Plant(path,interval) {

    }
    private:
    int m_Cooldown;
};

#endif //MINE_HPP
