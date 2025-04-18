//
// Created by bingho on 2025/3/11.
//
#include "Plant/fastshooter.hpp"

bool Fastshooter::AttackCheck(glm::vec2 pos) {
    if(pos.x>m_Transform.translation.x&&pos.x-m_Transform.translation.x<500)return true;
    return false;
}
std::shared_ptr<Bullet> Fastshooter::Attack(glm::vec2 pos) {
    if(m_cooldown1>=90&&bcount==0) {
        //if(not AttackCheck(pos))return nullptr;
        glm::vec2 temp={m_Transform.translation.x,m_Transform.translation.y+20};
        bcount++;
        return std::make_shared<NormalBullet>(temp);
    }else if(bcount==1&&m_cooldown1>=110) {
        glm::vec2 temp={m_Transform.translation.x,m_Transform.translation.y+20};
        m_cooldown1=bcount=0;
        return std::make_shared<NormalBullet>(temp);
    }else {
        m_cooldown1++;
        return nullptr;
    }

}