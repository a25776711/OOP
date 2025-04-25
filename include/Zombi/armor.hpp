//
// Created by bingho on 2025/3/11.
//

#ifndef ARMOR_HPP
#define ARMOR_HPP
#include "Zombi/zombi.hpp"
class armor : public zombi {
public:
    armor() :zombi(){
        SetHP(10);
        SetSpeed(1);
        Setattack(10);

        m_die.clear();
        m_die.reserve(14);
        for (int i=0;i<14;i++) {
            m_die.push_back(RESOURCE_DIR"/zombi/armor/die/die_" + std::to_string(i) + ".png");
        }

        m_Walk.reserve(11);
        for (int i=0;i<11;i++) {
            m_Walk.push_back(RESOURCE_DIR"/zombi/armor/walk/walk_" + std::to_string(i) + ".png");
        }
        m_iceWalk.reserve(11);
        for (int i=0;i<11;i++) {
            m_iceWalk.push_back(RESOURCE_DIR"/zombi/armor/walk_1/walk_1_" + std::to_string(i) + ".png");
        }
        m_eat.reserve(10);
        for (int i=0;i<10;i++) {
            m_eat.push_back(RESOURCE_DIR"/zombi/armor/eat/eat_" + std::to_string(i) + ".png");
        }
        m_iceeat.reserve(10);
        for (int i=0;i<10;i++) {
            m_iceeat.push_back(RESOURCE_DIR"/zombi/armor/eat_1/eat_1_" + std::to_string(i) + ".png");
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
        z_speed = z_speed / 2;
        SetImage(m_state);
        SetLooping(true);
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
            case  zombistate::stand:
                m_Images = m_Walk;
                break;
            case zombistate::die:
                m_Images = m_die;
                break;
            default: std::cout << "==" << std::endl; break;
        }
        m_Drawable = std::make_shared<Util::Animation>(m_Images, false, 100, false, 100);
    }

    std::vector<std::string> GetImages() {
        return m_Images;
    }



    void Eating() override {
        m_state = zombistate::eat;
        SetImage(zombistate::eat);
    }


private:
    std::vector<std::string> m_Images;
    std::vector<std::string> m_Walk;
    std::vector<std::string> m_iceWalk;
    std::vector<std::string> m_eat;
    std::vector<std::string> m_iceeat;
    int reverse = 46;
};

#endif //ARMOR_HPP
