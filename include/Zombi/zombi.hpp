//
// Created by bingho on 2025/3/11.
//

#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Plant/plant.hpp"
#include <random>
#include <string>

class zombi :public Util::GameObject {
public:
    zombi() {
        m_state = zombistate::walk;
        SetPiov();
    };

    enum class zombistate {
        walk,
        coldwalk,
        eat,
        coldeat
    };

    void SetLoopingandPlay(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
        temp ->Play();
    }
    virtual void Gotice(bool ice) = 0;
    virtual void move() = 0;
    virtual void Eating() = 0;

    zombistate GetState() {return m_state;}

    void SetSpeed(int speed) {z_speed = speed;}
    int GetSpeed() { return z_speed;}

    void SetHP(int HP) {z_HP = HP;}
    int GetHP() { return z_HP;}

    void Setattack(int HP) {z_attack = HP;}
    int Getattack() { return z_attack;}

    void SetPiov() {
        int x = rand() % 5 + 1;
        switch (x) {
            case 1:
                m_Transform.translation = roll1;
                break;
            case 2:
                m_Transform.translation = roll2;
                break;
            case 3:
                m_Transform.translation = roll3;
                break;
            case 4:
                m_Transform.translation = roll4;
                break;
            case 5:
                m_Transform.translation = roll5;
                break;
            default:
                break;
        }
    }

    // [[nodiscard]] bool IfCollides(const std::shared_ptr<Plant>& other) const {
    //
    //     m_state = zombistate::eat;
    // }

protected:
    int z_speed;
    int z_HP;
    int z_attack;
    zombistate m_state;

    glm::vec2 roll1={234,175};
    glm::vec2 roll2 ={234,75};
    glm::vec2 roll3 = {234,-25};
    glm::vec2 roll4 = {234,-122};
    glm::vec2 roll5 = {234,-220};
};

#endif //ZOMBI_HPP
