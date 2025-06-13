//
// Created by bingho on 2025/3/11.
//
#include "Plant/peashooter.hpp"


bool Peashooter::AttackCheck(std::vector<std::shared_ptr<zombi>> zom) {
    for(auto &z:zom){
        auto p=z->GetPosition();
        if(
        z->GetState()!=zombi::zombistate::die&&
        z->GetState()!=zombi::zombistate::ash&&
        z->GetState()!=zombi::zombistate::stand&&
        p.x>m_Transform.translation.x&&p.x-m_Transform.translation.x<800&&
        abs(p.y-m_Transform.translation.y)<50)return true;
    }
    return false;
}
std::shared_ptr<Bullet> Peashooter::Attack(std::vector<std::shared_ptr<zombi>> zom) {
    if(!AttackCheck(zom))return nullptr;
    if(m_cooldown>90){
        glm::vec2 temp={m_Transform.translation.x,m_Transform.translation.y+20};
        m_cooldown=0;
        return std::make_shared<NormalBullet>(temp);
    }else {
        m_cooldown++;
        return nullptr;
    }

}


