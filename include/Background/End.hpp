//
// Created by bingho on 2025/5/31.
//

#ifndef END_HPP
#define END_HPP
#include "GameObject.hpp"
#include "Util/Image.hpp"
#include <string>
class end : public GameObject {
    public:
        end():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/losegame.png"), -10) {
            m_Transform.scale = glm::vec2(0.1f, 0.1f);
            SetZIndex(100);
        }
        void Big() {
            if (m_Transform.scale == glm::vec2(1.0f, 1.0f)) {return;}
            m_Transform.scale = glm::vec2(m_Transform.scale.x+ 0.1f, m_Transform.scale.y+0.1f);
        }
};
#endif //END_HPP
