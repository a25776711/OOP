//
// Created by bingho on 2025/3/11.
//
#include "Plant/fastshooter.hpp"

bool Fastshooter::AttackCheck(std::vector<glm::vec2> pos) {
    for(auto &p:pos){
        if(
        p.x>m_Transform.translation.x&&p.x-m_Transform.translation.x<800&&
        abs(p.y-m_Transform.translation.y)<50)return true;
    }
    return false;
}
std::shared_ptr<Bullet> Fastshooter::Attack(std::vector<glm::vec2> pos) {
    if(!AttackCheck(pos))return nullptr;
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