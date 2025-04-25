//
// Created by a2577 on 25-4-25.
//

#ifndef CAR_HPP
#define CAR_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Car:public Util::GameObject {
    public:
    Car(glm::vec2 pos):Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/plant/car.png"),30) {
        m_Transform.translation = pos;
    }
    void Move() {
        m_Transform.translation.x += 6.0f;
    }
    bool IsTouch(glm::vec2 pos) {
        return m_Transform.translation.x < pos.x && m_Transform.translation.x + 30 > pos.x;
    }
};


#endif //CAR_HPP
