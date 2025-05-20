//
// Created by bingho on 2025/3/11.
//
#include "Plant/wallnut.hpp"

void Wallnut::Hurt() {
    int hp=GetHP()-1;
    SetHP(hp);
    if(hp<2400&&1200>=hp) {
        m_Drawable=std::make_shared<Util::Animation>(m_Loader.wallnutIMG_1,true,70,true,0);
    }else if(hp<1200) {
        m_Drawable=std::make_shared<Util::Animation>(m_Loader.wallnutIMG_2,true,70,true,0);
    }

}


bool Play_wallnut::Update(std::vector<std::shared_ptr<zombi>> zom) {
    // 更新旋轉角度
    m_Transform.rotation += m_rotationSpeed;
    // 向右移動
    m_Transform.translation.x += m_moveSpeed;

    // 檢查是否碰撞到殭屍
    for(const auto& zombie : zom) {
        if(zombie->GetState()!=zombi::zombistate::die) {
            // 計算與殭屍的距離
            float dx = zombie->GetPosition().x - m_Transform.translation.x;
            float dy = zombie->GetPosition().y - m_Transform.translation.y;
            float distance = std::sqrt(dx*dx + dy*dy);
            
            // 如果距離小於20,視為碰撞
            if(distance < 50) {
                zombie->GetHeart(false,false,4);
                if(m_moveState==T_WallnutMove::Straight) {
                    m_moveState = rand()%2==0?T_WallnutMove::Up:T_WallnutMove::Down;

                }else if(m_moveState==T_WallnutMove::Up) {
                    m_moveState = T_WallnutMove::Down;
                }else if(m_moveState==T_WallnutMove::Down) {
                    m_moveState = T_WallnutMove::Up;
                }
                break;
            }
        }
    }
    if(m_moveState==T_WallnutMove::Up) {
        m_Transform.translation.y += m_moveSpeed;
        if(m_Transform.translation.y > 272) {
            m_moveState = T_WallnutMove::Down;
        }
    }else if(m_moveState==T_WallnutMove::Down) {
        m_Transform.translation.y -= m_moveSpeed;
        if(m_Transform.translation.y < -320) {
            m_moveState = T_WallnutMove::Up;
        }
    }
    // 如果超出螢幕範圍則消失
    if(m_Transform.translation.x > 600) {
        return true;
    }

    return false;
}
bool Play_wallnut_boom::Update(std::vector<std::shared_ptr<zombi>> zom) {
    
    
    // 檢查是否碰撞到殭屍
    if(m_boom_count==0) {
        // 更新旋轉角度
        m_Transform.rotation += m_rotationSpeed;
        // 向右移動
        m_Transform.translation.x += m_moveSpeed;
        for(const auto& zombie : zom) {
            if(zombie->GetState()!=zombi::zombistate::die) {
                // 計算與殭屍的距離
                float dx = zombie->GetPosition().x - m_Transform.translation.x;
                float dy = zombie->GetPosition().y - m_Transform.translation.y;
                float distance = std::sqrt(dx*dx + dy*dy);
                
                // 如果距離小於50,視為碰撞
                if(distance < 50) {
                    zombie->GetHeart(true,false,200);
                    m_Transform.rotation=0;
                    m_boom_count++;
                    auto temp=std::make_shared<Util::Animation>(m_Loader.cherryIMG_Boom,false,70,true,0);
                    m_Drawable=temp;
                    break;
                }
            }
        }
        // 如果超出螢幕範圍則消失
        if(m_Transform.translation.x > 600) {
            return true;
        }
    }
    else{
        m_boom_count++;
        if(m_boom_count>=30){
            return true;
        }
    }
    return false;
}
