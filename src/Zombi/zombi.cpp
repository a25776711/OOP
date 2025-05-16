//
// Created by bingho on 2025/3/11.
//
#include "Zombi/zombi.hpp"
#include "Plant/plant.hpp"

void zombi::HitCheck(std::shared_ptr<Plant> plant) {

    if (m_state == zombistate::ash || m_state == zombistate::die) return;

    if (plant->GetHP() <= 0) {
        // 如果植物已死但僵屍還在吃，強制轉回走路狀態
        if (m_state == zombistate::eat || m_state == zombistate::coldeat) {
            StartWalk();
        }
        return; // 不再對已死植物做任何行動
    }

    auto pos = plant->GetPosition();
    bool inRangeX = (m_Transform.translation.x - pos.x <= 30);
    bool inRangeY = (abs(m_Transform.translation.y - pos.y) <= 50);

    if (inRangeX && inRangeY) {
        plant->Hurt();

        if (m_state != zombistate::eat && m_state != zombistate::coldeat) {
            StartEat();
        }

        if (plant->GetHP() <= 0) {
            StartWalk();
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

