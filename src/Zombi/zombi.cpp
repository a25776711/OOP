//
// Created by bingho on 2025/3/11.
//
#include "Zombi/zombi.hpp"
#include "Plant/plant.hpp"

void zombi::HitCheck(std::vector<std::vector<std::shared_ptr<Plant>>> Plants) {
    bool plantAhead = false;
    if (m_state == zombistate::die || m_state == zombistate::ash) {return;}

    for (const auto &row : Plants) {
        for (const auto &plant : row) {
            if (!plant) continue;

            auto pos = plant->GetPosition();

            // 只判斷是否在同一橫排
            if (abs(m_Transform.translation.y - pos.y) > 45)
                continue;

            // 如果 x 軸上差距在攻擊範圍內，前面有植物
            if (m_Transform.translation.x - pos.x <= 40 && m_Transform.translation.x - pos.x >= -5 && m_state != zombistate::die) {
                plantAhead = true;

                if (m_state != zombistate::eat && m_state != zombistate::coldeat ) {
                    StartEat();
                }
                else {
                    plant -> Hurt();
                }

                return; // 找到就直接結束
            }
        }
    }

    // 如果整個前方都沒植物 → 繼續走
    if (!plantAhead && (m_state == zombistate::eat || m_state == zombistate::coldeat)) {
        StartWalk();
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

