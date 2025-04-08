//
// Created by a2577 on 25-4-6.
//
#include "App.hpp"
std::shared_ptr<Sun> App::CheckSun(glm::vec2 click) {
    for(auto& sun:m_Suns) {
        glm::vec2 pos = sun->GetPosition();
        std::cout << pos.x << ", " << pos.y << std::endl;
        LOG_INFO("CheckSun:pos:(x:{},y:{})", pos.x, pos.y);
        sun->CollectAndMove(click);
        if(sun->GetMoveState()==MoveOver)return sun;
    }
    return nullptr;
}
void App::MoveSun() {
    m_Suns.erase(std::remove_if(m_Suns.begin(), m_Suns.end(), [&](std::shared_ptr<Sun>& sun) {
       sun->Move(); // 讓太陽移動
       if (sun->GetMoveState() == MoveOver) {
           m_Root.RemoveChild(sun); // 移除畫面中的sun
           Sunamount+=25;
           m_SunNB->Change(Sunamount);
           return true; // 返回true來標記這個元素為要刪除的
       }
       return false; // 否則不刪除
   }), m_Suns.end());
}
std::shared_ptr<Plant> App::CheckPlant(glm::vec2 click) {
    for (int i=1;i<9;i++) {
        
    }

}
void App::SetPos() {
    float spacing = 58;
    float startX = -542;
    for(int i=8;i>=0;i--) {
        glm::vec2 pos={startX +spacing * i,259};
        m_cardPos[std::to_string(i+1)]={{pos.x+27.5f,pos.y+40},{pos.x+27.5f,pos.y-40},{pos.x-27.5f,pos.y+40},{pos.x-27.5f,pos.y-40}};
    }
    std::cout << "test"<< std::endl;
    for (int i=1;i<9;i++) {
        std::vector<glm::vec2> temp=m_cardPos[std::to_string(i)];
        for(auto& pos:temp) {
            std::cout << pos.x << ", " << pos.y << std::endl;
        }
    }
    std::cout << "test"<< std::endl;
}
