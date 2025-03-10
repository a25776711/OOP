//
// Created by a2577 on 25-3-10.
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
