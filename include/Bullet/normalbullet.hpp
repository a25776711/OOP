//
// Created by bingho on 2025/3/11.
//

#ifndef NORMALBULLET_HPP
#define NORMALBULLET_HPP
#include "bullet.hpp"
class NormalBullet : public Bullet {
    NormalBullet():Bullet(RESOURCE_DIR"/pee/pea.png",Normal){}
};

#endif //NORMALBULLET_HPP
