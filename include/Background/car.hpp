//
// Created by a2577 on 25-4-25.
//

#ifndef CAR_HPP
#define CAR_HPP
#include "GameObject.hpp"
#include "Util/Image.hpp"
#include <string>
#include <iostream>

class Car:public GameObject {
    public:
    enum class CarState {
        Idle,
        Move
    };
    explicit Car(glm::vec2 pos,CarState state):GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/car.png"),-5) {
        m_Transform.translation = pos;
        m_State = state;
    }
    void Move() {
        m_Transform.translation.x += 4.0f;
    }
    bool IsTouch(glm::vec2 pos,int index) {
        std::vector<int> rolly = {190,100,10,-80,-200};
        if(pos.y == rolly[index]&&pos.x <= -430) {
            return true;
        }
        return false;
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
    glm::vec2 GetPosition() {
        return m_Transform.translation;
    }
    void Test(glm::vec2 pos) {
        std::cout << "car position: " << m_Transform.translation.x << std::endl;
        std::cout << "background position: " << pos.x << std::endl;
        std::cout << "distance: " << pos.x-m_Transform.translation.x << std::endl;
    }
    private:
    CarState m_State;
};


#endif //CAR_HPP
