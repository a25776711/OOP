//
// Created by bingho on 2025/3/11.
//
#include "Plant/sun.hpp"
void Sun::CollectAndMove(bool start,glm::vec2& des) {
    glm::vec2 pos=m_Transform.translation;
    if (start) {
        m_Transform.translation=glm::mix(pos,des,0.5f);
    }
}