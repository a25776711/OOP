//
// Created by bingho on 2025/3/11.
//

#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include <string>

class zombi :public Util::GameObject {
public:
    zombi() {
        m_state = zombistate::walk;
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
    virtual void Gotice(bool ice) =0;



    zombistate GetState() {return m_state;}

    void SetSpeed(int speed) {z_speed = speed;}
    int GetSpeed() { return z_speed;}

    void SetHP(int HP) {z_HP = HP;}
    int GetHP() { return z_HP;}

    void Setattack(int HP) {z_attack = HP;}
    int Getattack() { return z_attack;}

protected:
    int z_speed;
    int z_HP;
    int z_attack;
    zombistate m_state;
};

#endif //ZOMBI_HPP
