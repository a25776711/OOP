//
// Created by bingho on 2025/3/11.
//

#ifndef HAT_HPP
#define HAT_HPP

//
// Created by bingho on 2025/3/11.
//


#include "Zombi/zombi.hpp"

class hat : public zombi {
public:
    hat() {
        hat::SetHP(100);
        hat::SetSpeed(0.05);
        hat::Setattack(10);

        m_Walk.reserve(21);
        for (int i=0;i<21;i++) {
            m_Walk.push_back(RESOURCE_DIR"/zombi/hat/walk/walk_" + std::to_string(i) + ".png");
        }
        m_iceWalk.reserve(21);
        for (int i=0;i<21;i++) {
            m_iceWalk.push_back(RESOURCE_DIR"/zombi/hat/walk_1/walk_1_" + std::to_string(i) + ".png");
        }
        m_eat.reserve(11);
        for (int i=0;i<11;i++) {
            m_eat.push_back(RESOURCE_DIR"/zombi/hat/eat/eat_" + std::to_string(i) + ".png");
        }
        m_iceeat.reserve(11);
        for (int i=0;i<11;i++) {
            m_iceeat.push_back(RESOURCE_DIR"/zombi/hat/eat_1/eat_1_" + std::to_string(i) + ".png");
        }
        SetImage(m_state);
    };

    void Gotice(bool ice) override {
        switch (m_state) {
            case zombistate::walk:
                m_state = zombistate::coldwalk; break;
            case zombistate::eat:
                m_state = zombistate::coldeat; break;
            default:
                break;
        }
        SetImage(m_state);
    }

    void SetImage(zombistate state) {

        switch (state) {
            case zombistate::walk:
                m_Images = m_Walk;
                break;
            case zombistate::coldwalk:
                m_Images = m_iceWalk;
                break;
            case zombistate::eat:
                m_Images = m_eat;
                break;
            case zombistate::coldeat:
                m_Images = m_iceeat;
                break;
        }
        m_Drawable = std::make_shared<Util::Animation>(m_Images, true, 100, true, 100);
    }

    std::vector<std::string> GetImages() {
        return m_Images;
    }

    void move() override {
        m_Pivot = {m_Pivot.x+0.05, m_Pivot.y};
    }



private:
    std::vector<std::string> m_Images;
    std::vector<std::string> m_Walk;
    std::vector<std::string> m_iceWalk;
    std::vector<std::string> m_eat;
    std::vector<std::string> m_iceeat;
    int reverse = 46;
};



#endif //HAT_HPP
