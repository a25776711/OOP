//
// Created by a2577 on 25-4-25.
//

#ifndef CAR_HPP
#define CAR_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Car:public Util::GameObject {
    public:
    enum class CarState {
        Idle,
        Move
    };
    Car(glm::vec2 pos,CarState state):Util::GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/car.png"),30) {
        m_Transform.translation = pos;
        m_State = state;
    }
    void Move() {
        m_Transform.translation.x += 6.0f;
    }
    bool IsTouch(glm::vec2 pos) {
        return m_Transform.translation.x < pos.x && m_Transform.translation.x + 25 >= pos.x &&abs(m_Transform.translation.y - pos.y) <= 30;
    }
    void SetPosition(glm::vec2 pos) {
        m_Transform.translation = pos;
    }
    CarState GetState() {
        return m_State;
    }
    void SetState(CarState state) {
        m_State = state;
    }
    private:
        CarState m_State;
};


#endif //CAR_HPP
