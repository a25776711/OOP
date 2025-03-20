//
// Created by bingho on 2025/3/11.
//

#ifndef SUN_HPP
#define SUN_HPP
#include  "Plant/plant.hpp"
class Sun : public Plant {
    public:
    Sun(std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {

    }
    private:

};
#endif //SUN_HPP
