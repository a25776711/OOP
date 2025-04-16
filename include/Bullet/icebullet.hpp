//
// Created by bingho on 2025/3/11.
//

#ifndef ICEBULLET_HPP
#define ICEBULLET_HPP
#include "bullet.hpp"
class IceBullet:public Bullet {
    IceBullet(glm::vec2 pos):Bullet(RESOURCE_DIR"/pee/icepea.png",Ice,pos){}
};

#endif //ICEBULLET_HPP
