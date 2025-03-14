//
// Created by bingho on 2025/3/11.
//
#include "Plant/plant.hpp"
void Plant::Hurt(std::vector<std::shared_ptr<GameObject> > &collidedWith) {

    glm::vec2& pos = m_Transform.translation;
    for (std::shared_ptr<GameObject> obj : collidedWith) {

    }

}

