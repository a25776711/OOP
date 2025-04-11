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
std::shared_ptr<Plant> App::MakePlant(int i) {
    std::vector<std::shared_ptr<Plant>>m_GPlants={
    std::make_shared<Peashooter>(),
        std::make_shared<SunFlower>(),
        std::make_shared<Cherrybomb>(),
        std::make_shared<Wallnut>(),
        std::make_shared<Mine>(),
        std::make_shared<Iceshooter>(),
        std::make_shared<Chomper>(),
        std::make_shared<Fastshooter>()
    };
    if(i>8||i<1)return nullptr;
    return m_GPlants[i-1];
}

std::shared_ptr<Plant> App::CheckPlant(glm::vec2 click,int level) {
    if(m_holding)return nullptr;
    for (int i=1;i<9&&i<level;i++) {
        if(CheckClick(m_cardPos[std::to_string(i)],click)) {
            std::cout << "Plant" << std::endl;
            auto plant=MakePlant(i);
            m_holding=true;
            return MakePlant(i);
        }
    }
    return nullptr;
}

//點擊四個點確認
bool App::CheckClick(std::vector<glm::vec2> block,glm::vec2 click) {
    // 計算點與每個邊的叉積
    bool b1 = CrossProduct(block[0], block[1], click) >= 0;
    bool b2 = CrossProduct(block[1], block[2], click) >= 0;
    bool b3 = CrossProduct(block[2], block[3], click) >= 0;
    bool b4 = CrossProduct(block[3], block[1], click) >= 0;
    // 檢查四個叉積是否都為正或都為負，這意味著點在四邊形內
    return (b1 == b2) && (b2 == b3) && (b3 == b4);
}
float App::CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}
void App::SetPos() {
    float spacing = 57;
    float startX = -542;
    for(int i=7;i>=0;i--) {
        glm::vec2 pos={startX +spacing * (i),259};
        m_cardPos[std::to_string(i+1)]={{pos.x-27.5f,pos.y+40},{pos.x+27.5f,pos.y+40},{pos.x+27.5f,pos.y-40},{pos.x-27.5f,pos.y-40}};
    }
    for (int i=1;i<9;i++) {
        std::vector<glm::vec2> temp=m_cardPos[std::to_string(i)];
        for(auto& pos:temp) {
            std::cout << pos.x << ", " << pos.y << std::endl;
        }
    }
    std::cout << "test"<< std::endl;
}
