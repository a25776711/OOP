//
// Created by bingho on 2025/3/14.
//

#ifndef UPDATEBACKGROUND_HPP
#define UPDATEBACKGROUND_HPP

#include <iostream>

#include "Adventure.hpp"
#include "Background/background.hpp"
#include "GameObject.hpp"
#include "CardManager.hpp"

class UpdateBackground {
public:
    UpdateBackground ();

    void NextLevel();
    [[nodiscard]] std::vector<std::shared_ptr<GameObject>> GetChildren() const {
        std::vector<std::shared_ptr<GameObject>> result;
        result.push_back(m_Background);
        result.push_back(m_Adventure);
        if(m_level!=5){
            for (auto card : m_Cards) {
                result.push_back(card);
            }
        }
        result.push_back(m_Shovel);
        result.push_back(m_ShovelBlock);
        result.push_back(m_T_road);
        return result;
    }

    void SetCardPos();
    void ResetCardPos();
    std::shared_ptr<Card> PlayCard();
    void UpdatePlayCard();
    void RemovePlayCard(std::shared_ptr<Card> card);
    int GetLevel() {return m_level;}
    std::vector<std::shared_ptr<Card>> GetCards() {return m_Cards;}
    std::vector<std::shared_ptr<Card>> GetPlayCard() {return m_Cards_play;}
    std::shared_ptr<Shovel> GetShovel() {return m_Shovel;}
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
        glm::vec2 p1{114, -47};
        glm::vec2 p2{367, -65};
        glm::vec2 p3{360, -130};
        glm::vec2 p4{110, -101};
        std::vector<int> m_ShovelPos;
        std::vector<std::shared_ptr<Card>> m_Cards;
        std::vector<std::shared_ptr<Card>> m_Cards_play;
        std::shared_ptr<CardManager> m_CardManager;
        std::shared_ptr<BackgroundImage> m_Background;
        std::shared_ptr<adventure> m_Adventure;
        std::shared_ptr<ShovelBlock> m_ShovelBlock=nullptr;
        std::shared_ptr<Shovel> m_Shovel=nullptr;
        std::shared_ptr<T_road> m_T_road=nullptr;
        int m_level = 0;
        int m_play_clock = 0;

};

#endif //UPDATEBACKGROUND_HPP
