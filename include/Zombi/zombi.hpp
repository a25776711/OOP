//
// Created by bingho on 2025/3/11.
//

#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
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
                m_Pivot = roll1;
                break;
            case 2:
                m_Pivot = roll2;
                break;
            case 3:
                m_Pivot = roll3;
                break;
            case 4:
                m_Pivot = roll4;
                break;
            case 5:
                m_Pivot = roll5;
                break;
            default:
                break;
        }
    }


protected:
    int z_speed;
    int z_HP;
    int z_attack;
    zombistate m_state;

    glm::vec2 roll1={-549,131};
    glm::vec2 roll2 ={-549,30};
    glm::vec2 roll3 = {-549,-92};
    glm::vec2 roll4 = {-549,-140};
    glm::vec2 roll5 = {-549,-240};
};

#endif //ZOMBI_HPP
