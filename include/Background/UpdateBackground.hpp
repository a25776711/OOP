//
// Created by bingho on 2025/3/14.
//

#ifndef UPDATEBACKGROUND_HPP
#define UPDATEBACKGROUND_HPP

#include "Adventure.hpp"
#include "Background/background.hpp"
#include "Util/GameObject.hpp"
#include "Card.hpp"

class UpdateBackground {
public:
    UpdateBackground ();

    void NextLevel();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        return {m_Background,m_Adventure};
    }
//    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetCard() const {
//        std::vector<std::shared_ptr<Util::GameObject>> result;
//        for (const auto& card : m_Cards) {
//            result.push_back(std::static_pointer_cast<Util::GameObject>(card));
//        }
//        return result;
//    }
//    void GetCard() {
//        auto temp = std::make_shared<Card>();
//        m_Cards = temp -> SetCards(m_level);
//    }


    int GetLevel() {return m_level;}


    bool CheckHit(const glm::vec2& point) {
        // 計算點與每個邊的叉積
        bool b1 = CrossProduct(p1, p2, point) > 0;
        bool b2 = CrossProduct(p2, p3, point) > 0;
        bool b3 = CrossProduct(p3, p4, point) > 0;
        bool b4 = CrossProduct(p4, p1, point) > 0;

        // 檢查四個叉積是否都為正或都為負，這意味著點在四邊形內
        return (b1 == b2) && (b2 == b3) && (b3 == b4);
    }

    float CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }

private:
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<adventure> m_Adventure;
    // std::vector<std::shared_ptr<Card>> m_Cards;
    int m_level = 0;
    glm::vec2 p1{115, -45};
    glm::vec2 p2{372, -59};
    glm::vec2 p3{356, -131};
    glm::vec2 p4{107, -100};

};


#endif //UPDATEBACKGROUND_HPP
