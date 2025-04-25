//
// Created by bingho on 2025/3/11.
//

#ifndef BUCKET_HPP
#define BUCKET_HPP
#include "Zombi/zombi.hpp"
class bucket : public zombi {
public:
    bucket() :zombi(){
        bucket::SetHP(10);
        bucket::SetSpeed(1);
        bucket::Setattack(10);

        m_Walk.reserve(46);
        for (int i=0;i<46;i++) {
            m_Walk.push_back(RESOURCE_DIR"/zombi/bucket/walk/walk_" + std::to_string(i) + ".png");
        }
        m_iceWalk.reserve(46);
        for (int i=0;i<46;i++) {
            m_iceWalk.push_back(RESOURCE_DIR"/zombi/bucket/walk_1/walk_1_" + std::to_string(i) + ".png");
        }
        m_eat.reserve(39);
        for (int i=0;i<39;i++) {
            m_eat.push_back(RESOURCE_DIR"/zombi/bucket/eat/eat_" + std::to_string(i) + ".png");
        }
        m_iceeat.reserve(39);
        for (int i=0;i<39;i++) {
            m_iceeat.push_back(RESOURCE_DIR"/zombi/bucket/eat_1/eat_1_" + std::to_string(i) + ".png");
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
#endif //BUCKET_HPP
