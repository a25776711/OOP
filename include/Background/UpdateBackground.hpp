//
// Created by bingho on 2025/3/14.
//

#ifndef UPDATEBACKGROUND_HPP
#define UPDATEBACKGROUND_HPP

#include <iostream>

#include "Adventure.hpp"
#include "Background/background.hpp"
#include "Util/GameObject.hpp"
#include "CardManager.hpp"

class UpdateBackground {
public:
    UpdateBackground ();

    void NextLevel();

    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<Util::GameObject>> result;
        m_Background ->SetPivot({0,0,});
        result.push_back(m_Background);
        result.push_back(m_Adventure);
        for (auto card : m_Cards) {
            result.push_back(card);
        }

        return result;
    }



    void SetCardPos();
    int GetLevel() {return m_level;}

    bool CheckHit(const glm::vec2& point) {
        // 計算點與每個邊的叉積
        bool result = false;
        bool b1 = CrossProduct(p1, p2, point) >= 0;
        bool b2 = CrossProduct(p2, p3, point) >= 0;
        bool b3 = CrossProduct(p3, p4, point) >= 0;
        bool b4 = CrossProduct(p4, p1, point) >= 0;
        // 檢查四個叉積是否都為正或都為負，這意味著點在四邊形內
        result = (b1 == b2) && (b2 == b3) && (b3 == b4);
        if (result) {m_Adventure -> ChangeImage();}
        return result;
    }

    float CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }






    protected:
        glm::vec2 m_hitX;
        glm::vec2 m_hitY;
        glm::vec2 p1{117, 47};
        glm::vec2 p2{367, 65};
        glm::vec2 p3{354, 130};
        glm::vec2 p4{110, 101};

        std::vector<std::shared_ptr<Card>> m_Cards;
        std::shared_ptr<CardManager> m_CardManager;

        std::shared_ptr<BackgroundImage> m_Background;
        std::shared_ptr<adventure> m_Adventure;
        int m_level = 0;


};


#endif //UPDATEBACKGROUND_HPP
