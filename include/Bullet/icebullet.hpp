//
// Created by bingho on 2025/3/11.
//

#ifndef ICEBULLET_HPP
#define ICEBULLET_HPP
#include "bullet.hpp"
class IceBullet:public Bullet {
    IceBullet():Bullet(RESOURCE_DIR"/pee/icepea.png",Ice){}
};

#endif //ICEBULLET_HPP
