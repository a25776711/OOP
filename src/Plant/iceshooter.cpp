//
// Created by bingho on 2025/3/11.
//
#include "Plant/iceshooter.hpp"
bool Iceshooter::AttackCheck(std::vector<glm::vec2> pos) {
    for(auto &p:pos){
        if(
        p.x>m_Transform.translation.x&&p.x-m_Transform.translation.x<800&&
        abs(p.y-m_Transform.translation.y)<38)return true;
    }
    return false;
}
std::shared_ptr<Bullet> Iceshooter::Attack(std::vector<glm::vec2> pos) {
    if(!AttackCheck(pos))return nullptr;
    if(m_cooldown>=90) {
        glm::vec2 temp={m_Transform.translation.x,m_Transform.translation.y+20};
        m_cooldown=0;
        return std::make_shared<IceBullet>(temp);
    }else {
        m_cooldown++;
        return nullptr;
    }

}