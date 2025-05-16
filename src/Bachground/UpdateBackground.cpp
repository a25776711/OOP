//
// Created by bingho on 2025/3/14.
//
#include "Background/UpdateBackground.hpp"
#include "Util/Logger.hpp"
#include <iostream>
UpdateBackground::UpdateBackground() {
    m_level = 0;
    m_CardManager = std::make_shared<CardManager>();
    m_Background = std::make_shared<BackgroundImage>();
    m_Adventure = std::make_shared<adventure>();
    m_Adventure->m_Transform.translation={300,-100};
    m_ShovelBlock = std::make_shared<ShovelBlock>();
    m_Shovel = std::make_shared<Shovel>();
    m_Shovel->SetFourPoints({370,260,450,300});
    m_ShovelBlock->m_Transform.translation = {300, 280};
    m_Adventure -> m_Transform.scale ={0.8,0.8};
    m_T_road = std::make_shared<T_road>();
}

void UpdateBackground::NextLevel() {
    if (m_level == 11) return;

    m_Background->NextLevel(++m_level); 
    m_Adventure->NextLevel(m_level);
    m_Shovel->NextLevel(m_level);
    m_ShovelBlock->NextLevel(m_level);

    if (m_level != 0){
        m_Adventure->m_Transform.scale = {0.9, 0.9};
    }
    m_Adventure->m_Transform.translation=m_level==1?glm::vec2{-300, 315}:glm::vec2{-200, 315};
    if(m_level==5)m_T_road->SetVisible(true);
    m_Cards = m_CardManager->SetCards(m_level);
    SetCardPos();
    for(auto& card : m_Cards) {
        card->Reset();
    }
}

void UpdateBackground::SetCardPos() {
    float spacing = 57;
    float startX;
    if(m_level==1)
        startX = -470;
    else
        startX = -370;
    float y = 315;

    for (size_t i = 0; i < m_Cards.size(); ++i) 
        m_Cards[i]->SetPos({startX + spacing * i, y});
}
void UpdateBackground::ResetCardPos() {
    for (size_t i = 0; i < m_Cards.size(); ++i) 
        m_Cards[i]->ResetFourPoints();
}

