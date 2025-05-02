#ifndef SUNNB_HPP
#define SUNNB_HPP

#include "GameObject.hpp"
#include "Util/Text.hpp"
#include <glm/gtx/string_cast.hpp> // for glm::to_string

class SunNB : public GameObject {
public:
    SunNB() : GameObject(
        std::make_unique<Util::Text>(
            RESOURCE_DIR "/Background/Font/Inkfree.ttf", 20,
            "0", Util::Color::FromName(Util::Colors::BLACK)),
        100) {
        m_Transform.translation = { -605, 220 };
    }

    void Change(int sunnb) {
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(std::to_string(sunnb));
    }
};

#endif // SUNNB_HPP
