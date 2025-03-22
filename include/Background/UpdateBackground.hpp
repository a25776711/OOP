//
// Created by bingho on 2025/3/14.
//

#ifndef UPDATEBACKGROUND_HPP
#define UPDATEBACKGROUND_HPP

#include <iostream>

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
<<<<<<< Updated upstream
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetCard() const {
        std::vector<std::shared_ptr<Util::GameObject>> result;
=======
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetCards() const {
        std::vector<std::shared_ptr<Util::GameObject>> result;
        result.reserve(m_Cards.size());
>>>>>>> Stashed changes
        for (const auto& card : m_Cards) {
            result.push_back(std::static_pointer_cast<Util::GameObject>(card));
        }
        return result;
    }
<<<<<<< Updated upstream
    void GetCard() {
        auto temp = std::make_shared<Card>();
        m_Cards = temp -> SetCards(m_level);
    }
=======

>>>>>>> Stashed changes


    int GetLevel() {return m_level;}


    bool CheckHit(const glm::vec2& point) {
        // 計算點與每個邊的叉積
        bool b1 = CrossProduct(p1, p2, point) >= 0;
        bool b2 = CrossProduct(p2, p3, point) >= 0;
        bool b3 = CrossProduct(p3, p4, point) >= 0;
        bool b4 = CrossProduct(p4, p1, point) >= 0;
        // 檢查四個叉積是否都為正或都為負，這意味著點在四邊形內

        return (b1 == b2) && (b2 == b3) && (b3 == b4);
    }

    float CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }

    void SetCardPos();
private:
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<adventure> m_Adventure;
    std::vector<std::shared_ptr<Card>> m_Cards;
<<<<<<< Updated upstream
    int m_level = 0;
    glm::vec2 p1{115, -45};
    glm::vec2 p2{372, -59};
    glm::vec2 p3{356, -131};
    glm::vec2 p4{107, -100};
=======
        int GetLevel() {return m_level;}


    bool Checkclck(glm::vec2 pos) {
            if ((m_hitX.x <= pos.x && m_hitX.y >= pos.x) && (m_hitY.x <= pos.x && m_hitY.y >= pos.y)) {
                return true;
            }
            else return false;
        }

    protected:

        glm::vec2 m_hitX;
        glm::vec2 m_hitY;
        std::shared_ptr<BackgroundImage> m_Background;
        std::shared_ptr<adventure> m_Adventure;
        int m_level = 0;
=======
    std::shared_ptr<Card> m_Card;
    int m_level = 0;
    glm::vec2 p1{117, 47};
    glm::vec2 p2{367, 65};
    glm::vec2 p3{354, 130};
    glm::vec2 p4{110, 101};
>>>>>>> Stashed changes

};


#endif //UPDATEBACKGROUND_HPP
