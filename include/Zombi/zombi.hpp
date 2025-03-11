//
// Created by bingho on 2025/3/11.
//

#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "Util/GameObject.hpp"

class Zombi:public Util::GameObject {
    public:
        Zombi();
        ~Zombi();
    private:
        int x,y;
        int HP;
        int ATK;
};
#endif //ZOMBI_HPP
