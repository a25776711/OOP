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
        m_Transform.translation = { -530, 280 };
    }

    void Change(int sunnb) {
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(std::to_string(sunnb));
    }
};

class NextText : public GameObject {
public:
    NextText() : GameObject(std::make_unique<Util::Text>(
            RESOURCE_DIR "/Background/Font/Inkfree.ttf", 50,
            "All Zombi are Die~ \n Press Enter To Next Level", Util::Color::FromName(Util::Colors::BLACK)),
        50) {
        m_Transform.translation = { 0, 0 };
        SetVisible(false);
    };
};
#endif // SUNNB_HPP
