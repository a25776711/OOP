//
// Created by bingho on 2025/3/11.
//
#include "Plant/peashooter.hpp"


bool Peashooter::AttackCheck(glm::vec2 pos) {
    if(pos.x>m_Transform.translation.x&&pos.x-m_Transform.translation.x<500)return true;
    return false;
}
std::shared_ptr<Bullet> Peashooter::Attack(glm::vec2 pos) {
    if(m_cooldown>90) {
        //if(not AttackCheck(pos))return nullptr;
        glm::vec2 temp={m_Transform.translation.x,m_Transform.translation.y+20};
        m_cooldown=0;
        return std::make_shared<NormalBullet>(temp);
    }else {
        m_cooldown++;
        return nullptr;
    }

}


