//
// Created by bingho on 2025/5/1.
//

#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "GameObject.hpp"
#include "Util/Animation.hpp"
#include "Background/Car.hpp"
#include <random>
#include <string>
#include <iostream>
#include <memory>

// 前向聲明
class Plant;

class zombi :public GameObject {
public:
    zombi() {
        m_state = zombistate::stand;
        m_die.reserve(9);
        for (int i = 0; i < 9; i++) {
            m_die.push_back(RESOURCE_DIR"/zombi/die/die/die_" + std::to_string(i) + ".png");
        }
        m_ash.reserve(20);
        for (int i = 0; i < 20; i++) {
            m_ash.push_back(RESOURCE_DIR"/zombi/die/ash/ash_" + std::to_string(i) + ".png");
        }
        SetZIndex(100);
    };

    enum class zombistate {
        walk,
        coldwalk,
        eat,
        coldeat,
        stand,
        die,
        ash
    };

    virtual void  SetImage(zombistate state) = 0;


    virtual void Gotice(bool ice) = 0;
    void move(std::vector<std::shared_ptr<Car>> cars) ;
    zombistate GetState() {return m_state;}

    void SetSpeed(float speed) {z_speed = speed;}
    int GetSpeed() { return z_speed;}

    void SetHP(int HP) {z_HP = HP;}
    int GetHP() { return z_HP;}

    void Setattack(int HP) {z_attack = HP;}
    int Getattack() { return z_attack;}
    glm::vec2 GetPosition() { return m_Transform.translation;}
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
        // m_state = zombistate::walk;
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
        temp->Play();
    }

    void Die() {
        m_state = zombistate::die;
        z_speed = 0;
        m_Drawable = std::make_shared<Util::Animation>(m_die, true, 100, true, 100);
    }

    void Ash() {
        m_state = zombistate::ash;
        z_speed = 0;
        m_Drawable = std::make_shared<Util::Animation>(m_ash, true, 100, true, 100);
    }

    void StartEat() {
        switch (m_state) {
            case zombistate::coldwalk:
                m_state = zombistate::coldeat;
                z_speed = 0;
                SetImage(m_state);
                SetLooping(true);
                break;
            case zombistate::walk:
                m_state = zombistate::eat;
                z_speed = 0;
                SetImage(m_state);
                SetLooping(true);
                break;
            case zombistate::coldeat:
                break;
            case zombistate::eat:
                break;
            case zombistate::die:
                break;
            case zombistate::stand:
                break;
            case zombistate::ash:
                break;
            default:
                break;
        }
        z_speed = 0;
        SetImage(m_state);
        SetLooping(true);
    }

    void StartWalk() {
        switch (m_state) {
            case zombistate::coldeat:
                m_state = zombistate::coldwalk;
                break;
            case zombistate::eat:
                m_state = zombistate::walk;
                break;
            case zombistate::stand:
                m_state = zombistate::walk;
                break;
            case zombistate::walk:
                break;
            case zombistate::coldwalk:
                break;
            case zombistate::die:
                break;
            default:
                std::cout << "warmstate" << std::endl;
                break;
        };
        z_speed = 1;
        SetImage(m_state);
        SetLooping(true);
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
        return (temp->GetCurrentFrameIndex() == temp->GetFrameCount() - 1 && (m_state == zombistate::die || m_state == zombistate::ash));

    }
    void GetHeart(bool ash,bool ice,int attack) {
        if (ash) {
            z_HP = 0;
            this -> Ash();
        }
        else {
            z_HP -= attack;
            if (ice) {
                this -> Gotice(true);
            }
            if (z_HP <= 0)Die();
        }
    }
    void HitCheck(std::shared_ptr<Plant> plant);


protected:
    float z_speed;
    float z_HP;
    float z_attack;
    zombistate m_state;

    std::vector<std::string> m_die;
    std::vector<std::string> m_ash;

    glm::vec2 roll1={600.0,190.0};
    glm::vec2 roll2 ={600.0,100.0};
    glm::vec2 roll3 = {600.0,10.0};
    glm::vec2 roll4 = {600.0,-80};
    glm::vec2 roll5 = {600.0,-200};
};

#endif //ZOMBI_HPP
