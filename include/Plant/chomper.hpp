//
// Created by bingho on 2025/3/11.
//

#ifndef CHOMPER_HPP
#define CHOMPER_HPP
#include "Plant/plant.hpp"

class Chomper:public Plant {
    public:
    Chomper(int hp,std::vector<std::string>& Path,int interval=100):Plant(path,interval) {
        SetHP(hp);
    }
    private:
    int m_Cooldown;
    bool m_eating;

};
#endif //CHOMPER_HPP
