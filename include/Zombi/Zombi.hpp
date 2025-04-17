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
#include <iostream>

class zombi :public Util::GameObject {
public:
    zombi() {
        m_state = zombistate::stand;
        m_die.reserve(9);
        for (int i = 0; i < 9; i++) {
            m_die.push_back(RESOURCE_DIR"/zombi/die/die/die_" + std::to_string(i) + ".png");
        }
    };

    enum class zombistate {
        walk,
        coldwalk,
        eat,
        coldeat,
        stand,
        die
    };


    virtual void Gotice(bool ice) = 0;
    void move() {
        m_Transform.translation.x = m_Transform.translation.x - z_speed;
    };
    virtual void Eating() = 0;

    zombistate GetState() {return m_state;}

    void SetSpeed(float speed) {z_speed = speed;}
    int GetSpeed() { return z_speed;}

    void SetHP(int HP) {z_HP = HP;}
    int GetHP() { return z_HP;}

    void Setattack(int HP) {z_attack = HP;}
    int Getattack() { return z_attack;}

    void SetPiov(int level) {
        int x =0;
        if (level == 1){x=3;}
        else if (level == 2){x = rand()%3 + 1;}
        else (x=rand()%5 + 1);
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

    void SetLooping(bool looping) {
        m_state = zombistate::walk;
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
        temp->Play();
    }

    void Die() {
        m_state = zombistate::die;
        z_speed = 0;
        m_Drawable = std::make_shared<Util::Animation>(m_die, true, 100, true, 100);
    }
    bool IfAnimationEnds() const {
        if (!m_Drawable) {
            std::cerr << "[ERROR] m_Drawable is null." << std::endl;
            return false;
        }

        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        if (!temp) {
            std::cerr << "[ERROR] m_Drawable is not an Animation." << std::endl;
            return false;
        }
        return temp->GetCurrentFrameIndex() == temp->GetFrameCount() - 1;

    }


protected:
    float z_speed;
    float z_HP;
    float z_attack;
    zombistate m_state;

    std::vector<std::string> m_die;

    glm::vec2 roll1={450.0,175.0};
    glm::vec2 roll2 ={450.0,75.0};
    glm::vec2 roll3 = {450.0,-25.0};
    glm::vec2 roll4 = {450.0,-122};
    glm::vec2 roll5 = {450.0,-220};
};

#endif //ZOMBI_HPP
