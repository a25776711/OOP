//
// Created by bingho on 2025/3/11.
//
#include "Zombi/zombi.hpp"
#include "Plant/plant.hpp"

void zombi::HitCheck(std::shared_ptr<Plant> plant) {
    auto pos = plant->GetPosition();
    if((m_Transform.translation.x - pos.x <= 30) && 
       (abs(m_Transform.translation.y - pos.y) <= 40) &&
       (m_state != zombistate::eat && m_state != zombistate::coldeat)) {
        StartEat();
    }
}

