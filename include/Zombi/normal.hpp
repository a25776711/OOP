//
// Created by bingho on 2025/3/11.
//

#ifndef NORMAL_HPP
#define NORMAL_HPP
#include "Zombi/zombi.hpp"

class normal : public zombi {
public:
    normal() {
        SetImage();
        normal::SetHP(100);
        normal::SetSpeed(30);
        normal::Setattack(10);

    };

    void SetImage() {
        m_Images.reserve(reverse);
        for (int i=0;i<reverse;i++) {
            m_Images.push_back(RESOURCE_DIR"/zombi/normal/walk/walk_" + std::to_string(i) + ".png");
        }
        m_Drawable = std::make_shared<Util::Animation>(m_Images, true, 100, true, 100);
    }
    std::vector<std::string> GetImages() {
        return m_Images;
    }

    void move() override {
        m_Pivot = {m_Pivot.x+0.05, m_Pivot.y};
    }

    void Gotice(bool ice) override {}

private:
    std::vector<std::string> m_Images;
    int reverse = 46;
};

#endif //NORMAL_HPP
