//
// Created by bingho on 2025/5/23.
//

#ifndef READY_HPP
#define READY_HPP
#include "GameObject.hpp"
#include "Util/Animation.hpp"
#include "string"
class Ready : public GameObject {
    public:
        Ready() {
            m_Image.reserve(4);
            m_Image.push_back(RESOURCE_DIR"/Background/ready.png");
            m_Image.push_back(RESOURCE_DIR"/Background/set.png");
            m_Image.push_back(RESOURCE_DIR"/Background/start.png");
            m_Image.push_back(RESOURCE_DIR"/Background/nothing.png");
            SetZIndex(100);
            SetVisible(true);
            m_Drawable = std::make_shared<Util::Animation>(m_Image, true, 500, true, 0);
        };

        bool IfAnimationEnds() const {
            if (!m_Drawable) {
                std::cerr << "[ERROR] m_Drawable is null." << std::endl;
                return false;
            }

            auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
            if (!temp) {
                std::cerr << "[ERROR] m_Drawable is not an Animation." << std::endl;
                return false;
            }
            return (temp->GetCurrentFrameIndex() == temp->GetFrameCount() - 1 );

        }

    private:
        std::vector<std::string> m_Image;
};

#endif //READY_HPP
