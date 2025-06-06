#include <glm/glm.hpp>
#include "Plant/sun.hpp"

#include <iostream>

#include "Util/Logger.hpp"

Sun::Sun(bool flower,glm::vec2 pos):Plant(m_Loader.sunIMG,60) {
    SetZIndex(9);
    m_flower=flower;
    if(!flower){
        m_Transform.scale={0.8,0.8};
        m_state=Droping;
        int X = rand()%(270-(-430)+1)+(-430);
        int Y = rand()%(180-(-250)+1)+(-250);
        m_drop={X,Y};
        m_Transform.translation={X,300};
        //LOG_INFO("Generated Sun at position: ({}, {})", X,200);
    }else {
        m_Transform.scale={0.8,0.8};
        m_state=Droping;
        m_drop = {pos.x + (rand() % 31 - 15), pos.y - 20};
        m_Transform.translation = {pos.x,pos.y+20};
        //LOG_INFO("Generated Sun at position: ({}, {})", pos.x,pos.y);
    }
}
void Sun::CollectAndMove(glm::vec2 click) {
    if(CheckHit(click)&&m_state!=CollectMoving) {
        LOG_INFO("Sun collided with hit!");
        m_state=CollectMoving;
        m_click=true;
    }
}
void Sun::Move() {
    glm::vec2 pos = m_Transform.translation;
    if(m_flower) {
        if(m_state==Droping&&!m_click&&m_state!=MoveOver){
            glm::vec2 direction = m_drop - pos;
            float distance = glm::length(direction);

            if (distance > 0.1f) {  // 當物體還未到達目標位置時
                direction = glm::normalize(direction); // 讓方向向量變為單位向量
                float maxSpeed = 1.0f;  // 固定的移動速度
                m_Transform.translation += direction * maxSpeed; // 按固定速度移動

            } else {
                m_Transform.translation = m_drop; // 確保物體精確到達目標位置
                m_state = Collectable;  // 移動完成
            }
        }else if (m_click&&m_state!=MoveOver) {
            const float duration = 2.0f; // 移動的總時間，根據需要調整
            float t = 0.0f; // 這是控制移動進度的時間變數

            t += 0.08f;
            if (t > duration) t = duration; // 防止時間超過最大值

            // 使用ease-out緩動函數，這裡用t * t來模擬
            float easing = 1 - (1 - t / duration) * (1 - t / duration); // ease-out

            // 根據緩動插值計算新的座標
            m_Transform.translation = glm::mix(pos, m_des, easing); // 使用glm::mix插值
            if(glm::length(m_des-m_Transform.translation)<0.8f)m_state=MoveOver;
        }
        p1 = {m_Transform.translation.x + 20, m_Transform.translation.y + 20};
        p2 = {m_Transform.translation.x - 20, m_Transform.translation.y + 20};
        p3 = {m_Transform.translation.x - 20, m_Transform.translation.y - 20};
        p4 = {m_Transform.translation.x + 20, m_Transform.translation.y - 20};
    }else{
    if(m_state==Droping&&!m_click&&m_state!=MoveOver){
        glm::vec2 direction = m_drop - pos;
        float distance = glm::length(direction);

        if (distance > 0.1f) {  // 當物體還未到達目標位置時
            direction = glm::normalize(direction); // 讓方向向量變為單位向量
            float maxSpeed = 1.8f;  // 固定的移動速度
            m_Transform.translation += direction * maxSpeed; // 按固定速度移動

        } else {
            m_Transform.translation = m_drop; // 確保物體精確到達目標位置
            m_state = Collectable;  // 移動完成
        }
    }else if (m_click&&m_state!=MoveOver) {
        const float duration = 2.0f; // 移動的總時間，根據需要調整
        float t = 0.0f; // 這是控制移動進度的時間變數

        t += 0.08f;
        if (t > duration) t = duration; // 防止時間超過最大值

        // 使用ease-out緩動函數，這裡用t * t來模擬
        float easing = 1 - (1 - t / duration) * (1 - t / duration); // ease-out

        // 根據緩動插值計算新的座標
        m_Transform.translation = glm::mix(pos, m_des, easing); // 使用glm::mix插值
        if(glm::length(m_des-m_Transform.translation)<0.8f)m_state=MoveOver;
    }
    p1 = {m_Transform.translation.x + 20, m_Transform.translation.y + 20};
    p2 = {m_Transform.translation.x - 20, m_Transform.translation.y + 20};
    p3 = {m_Transform.translation.x - 20, m_Transform.translation.y - 20};
    p4 = {m_Transform.translation.x + 20, m_Transform.translation.y - 20};
}
}
