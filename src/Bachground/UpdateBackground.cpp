//
// Created by bingho on 2025/3/14.
//
#include "Background/UpdateBackground.hpp"
#include "Util/Logger.hpp"
#include <iostream>
#include <algorithm>

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
    m_ChooseCardList->m_Transform.translation = {-600, 0};
    m_Adventure -> m_Transform.scale ={0.8,0.8};
    m_T_road = std::make_shared<T_road>();
}

void UpdateBackground::NextLevel() {
    if (m_level == 11) return;
    if(m_level==5){
        m_Cards_play.clear();
    }
    m_Background->NextLevel(++m_level);
    m_Adventure->NextLevel(m_level);
    m_Shovel->NextLevel(m_level);
    m_ShovelBlock->NextLevel(m_level);
    m_ChooseButton->SetOver(false);

    if (m_level != 0){
        m_Adventure->m_Transform.scale = {0.9, 0.9};
    }
    m_Adventure->m_Transform.translation=m_level==1?glm::vec2{-300, 315}:glm::vec2{-200, 315};
    if(m_level<=7) m_Cards = m_CardManager->SetCards(m_level);
    else{
        m_Cards_chose = m_CardManager->SetCards(m_level);
        m_Cards.clear();
        std::cout<<"clear m_Cards"<<std::endl;
    }
    m_ChooseCardList->SetVisible(m_level>7);
    if(m_level!=5)SetCardPos(false);
    for(auto& card : m_Cards) card->Reset();
    m_T_road->SetVisible(m_level==5);
    for(auto& card : m_Cards) card->SetVisible(m_level!=5);
    m_Adventure->SetVisible(m_level!=5);
    m_Shovel->SetVisible(m_level>4);
    m_ShovelBlock->SetVisible(m_level>4);

}

void UpdateBackground::SetCardPos(bool is_chose) {
    float spacing = 57;
    float startX;
    if(m_level==1)
        startX = -465;
    else
        startX = -365;
    if(!is_chose){
        for (size_t i = 0; i < m_Cards.size(); ++i){
            if(m_Cards[i]!=nullptr){
                m_Cards[i]->SetPos({startX + spacing * i, 315});
            }
        }
    }
    else{
        spacing=63;
        for (size_t i = 0; i < m_Cards_chose.size(); ++i){
            if(m_Cards_chose[i]!=nullptr){
                m_Cards_chose[i]->SetPos({-419 + spacing * i, 0});
                
            }
        }
    }
    ResetCardPos();
}

std::vector<std::shared_ptr<GameObject>> UpdateBackground::GetCards_chose() {
    std::vector<std::shared_ptr<GameObject>> result;
    for(auto& card : m_Cards_chose){
        result.push_back(card);
    }
    return result;
}

void UpdateBackground::ResetCardPos() {
    for (size_t i = 0; i < m_Cards.size(); ++i) 
        m_Cards[i]->ResetFourPoints();
    for(auto& card : m_Cards_chose)
        card->ResetFourPoints();
}
std::shared_ptr<Card> UpdateBackground::PlayCard() {
    std::shared_ptr<Card> card_play=nullptr;
    if(m_play_clock==0) {
        card_play=rand()%4!=0?std::make_shared<Card>(RESOURCE_DIR "/Background/Card/wallnut_0cost.png",9):std::make_shared<Card>(RESOURCE_DIR "/Background/Card/wallnut_0cost_b.png",10);
        card_play->m_Transform.scale ={0.6,0.6};
        card_play->SetPos({-500,320});
        m_Cards_play.push_back(card_play);
        m_play_clock=300;
    }
    m_play_clock--;
    return card_play;
}
void UpdateBackground::UpdatePlayCard() {
    float moveSpeed = 1.0f;  // 移動速度
    float minDistance = 60.0f;  // 最小間距
    // 從左到右排序卡牌
    std::sort(m_Cards_play.begin(), m_Cards_play.end(), 
        [](const auto& a, const auto& b) {
            return a->m_Transform.translation.x < b->m_Transform.translation.x;
        });
    
    // 更新每張卡牌的位置
    for(size_t i = 0; i < m_Cards_play.size(); i++) {
        auto& checkcard = m_Cards_play[i];
        bool canMove = true;
        for(size_t j = i+1; j < m_Cards_play.size(); j++) {
            auto& x = m_Cards_play[j]->m_Transform.translation.x;
            if(x>checkcard->m_Transform.translation.x && x - checkcard->m_Transform.translation.x < minDistance) {
                canMove = false;        
                break;
            }
        }
        
        // 如果可以移動且未到達右邊界，則向前移動
        if(canMove && checkcard->m_Transform.translation.x < 140) {
            checkcard->m_Transform.translation.x += moveSpeed;
            checkcard->ResetFourPoints();
            // 確保不會超出右邊界
            if(checkcard->m_Transform.translation.x > 140) {
                checkcard->m_Transform.translation.x = 140;
            }
        }
    }
}
void UpdateBackground::RemovePlayCard(std::shared_ptr<Card> card) {
    m_Cards_play.erase(std::remove(m_Cards_play.begin(), m_Cards_play.end(), card), m_Cards_play.end());
}
std::shared_ptr<Card> UpdateBackground::ChooseCard(bool is_chose,std::shared_ptr<Card> card) {
    std::shared_ptr<Card> temp_card=nullptr;
    if(is_chose){
            temp_card=m_CardManager->GetCard(card->GetIndex());
            temp_card->SetVisible(true);
            temp_card->m_Transform.scale={0.4,0.4};
            m_Cards.push_back(temp_card);
        std::sort(m_Cards.begin(), m_Cards.end(),
            [](const auto& a, const auto& b) {
                return a->GetIndex() < b->GetIndex();
        });
        for(auto& chose_card : m_Cards_chose) {
            if(chose_card->GetIndex() == card->GetIndex()) {
                chose_card->SetVisible(false);
                break;
            }
        }
    }else{
        temp_card=card;
        m_Cards.erase(std::remove(m_Cards.begin(), m_Cards.end(), temp_card), m_Cards.end());
        std::sort(m_Cards.begin(), m_Cards.end(),
            [](const auto& a, const auto& b) {
                return a->GetIndex() < b->GetIndex();
        });
        for(auto& card:m_Cards_chose){
            if(card->GetIndex()==temp_card->GetIndex()){
                card->SetVisible(true);
                break;
            }
        }
    }
    SetCardPos(true);
    SetCardPos(false);
    ResetCardPos();
    return temp_card;
}
void UpdateBackground::ShowChoseCardList(bool show) {
    glm::vec2 pos = m_ChooseCardList->m_Transform.translation;
    if(show){
        m_ChooseCardList->m_Transform.translation = {-200, pos.y};
        m_ChooseButton->SetPoints();
    }
    else m_ChooseCardList->m_Transform.translation = {-800, pos.y};
    
}
std::vector<std::shared_ptr<GameObject>> UpdateBackground::GetChoseAsGameObject(bool is_chose){
    std::vector<std::shared_ptr<GameObject>> result;
    if(is_chose){
        
        result.push_back(m_ChooseCardList);
        for(auto& card : m_Cards_chose){
            result.push_back(card);
        }
        result.push_back(m_ChooseButton);
        
        result.push_back(m_Adventure);
        return result;
    }
    else{
        result.push_back(m_ChooseCardList);
        result.push_back(m_Adventure);
        for(auto& card : m_Cards_chose){
            result.push_back(card);
        }
        for(auto& card : m_Cards){
            result.push_back(card);
        }
        result.push_back(m_ChooseButton);
        return result;
    }
}
void UpdateBackground::ResetCardandCardListPos(){
    m_Adventure->m_Transform.translation=glm::vec2{-200, 315};
    SetCardPos(false);
    SetCardPos(true);
    ResetCardPos();
}
