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
        m_Transform.translation.x += 4.0f;
    }
    bool IsTouch(glm::vec2 pos,int index) {
        std::vector<int> rolly = {170,90,10,-80,-170};
        if(pos.y == rolly[index]&&pos.x <= -440) {  
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
    private:
        CarState m_State;
};


#endif //CAR_HPP
