//
// Created by bingho on 2025/3/11.
//

#ifndef ICEBULLET_HPP
#define ICEBULLET_HPP
#include "bullet.hpp"
class IceBullet:public Bullet {
    public:
    explicit IceBullet(glm::vec2 pos):Bullet(RESOURCE_DIR"/plant/pee/icepea.png",Ice,pos) {
        m_Transform.translation = pos;
    }
};

#endif //ICEBULLET_HPP
