//
// Created by bingho on 2025/3/11.
//

#ifndef NORMALBULLET_HPP
#define NORMALBULLET_HPP
#include "bullet.hpp"
class NormalBullet : public Bullet {
    public:
    NormalBullet(glm::vec2 pos):Bullet(RESOURCE_DIR"/plant/pee/pea.png",Normal,pos) {
        m_Transform.translation = pos;
    }
};

#endif //NORMALBULLET_HPP
