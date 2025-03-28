//
// Created by bingho on 2025/3/11.
//

#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP
#include "Plant/plant.hpp"

class Cherrybomb:public Plant {
    public:
    explicit  Cherrybomb(int ATK,std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {
        SetATK(ATK);
    }

    private:
};
#endif //CHERRYBOMB_HPP
