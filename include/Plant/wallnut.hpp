//
// Created by bingho on 2025/3/11.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "plant.hpp"
class Wallnut : public Plant {
    public:
    explicit  Wallnut(int hp,std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {
        SetHP(hp);
    }
    private:

};
#endif //WALLNUT_HPP
