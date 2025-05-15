//
// Created by bingho on 2025/3/11.
//
#include "Zombi/zombi.hpp"
#include "Plant/plant.hpp"

void zombi::HitCheck(std::shared_ptr<Plant> plant) {
    if (m_state != zombistate::ash && m_state != zombistate::die) {
        auto pos = plant->GetPosition();
        if((m_Transform.translation.x - pos.x <= 30) &&
           (abs(m_Transform.translation.y - pos.y) <= 40) &&
           (m_state != zombistate::eat && m_state != zombistate::coldeat)) {
            plant->Hurt();
            StartEat();
            if (plant ->GetHP() <=0){StartWalk();}
           }
        else if((m_Transform.translation.x - pos.x <= 30) &&
           (abs(m_Transform.translation.y - pos.y) <= 40) &&
           (m_state == zombistate::eat || m_state == zombistate::coldeat)){
            plant->Hurt();
            if (plant ->GetHP() <=0){StartWalk();}
           }

    }
}

void zombi::move(std::vector<std::shared_ptr<Car>> cars)  {
        std::vector<float> rolls = {220.0,110.0,10.0,-110.0,-250.0};
        m_Transform.translation.x = m_Transform.translation.x - z_speed;
        for (int i=0;i<rolls.size();i++) {
            if (m_Transform.translation.y==rolls[i]&&m_Transform.translation.x>=-450&&m_state!=zombistate::die) {
                if (cars[4-i]!=nullptr && cars[4-i]!=nullptr && cars[4-i] -> GetPosition().x+20 > m_Transform.translation.x
                && cars[4-i] -> GetPosition().x-20 < m_Transform.translation.x) {
                    Die();
                }
            }
        }
    }

