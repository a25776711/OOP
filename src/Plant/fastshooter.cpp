//
// Created by bingho on 2025/3/11.
//
#include "Plant/fastshooter.hpp"

bool Fastshooter::AttackCheck(std::vector<std::shared_ptr<zombi>> zom) {
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
std::shared_ptr<Bullet> Fastshooter::Attack(std::vector<std::shared_ptr<zombi>> zom) {
    if(!AttackCheck(zom))return nullptr;
    if(m_cooldown1>=90&&bcount==0) {
        
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