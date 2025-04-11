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

//生成植物
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
    m_GPlants[i-1]->SetZIndex(50);
    return m_GPlants[i-1];
}
//點擊卡片判斷
void App::CheckPlant(glm::vec2 click,int level) {
    for (int i=1;i<9&&i<level;i++) {
        std::cout << "test"<<std::endl;
        if(CheckClick(m_cardPos[std::to_string(i)],click)) {
            std::cout << "test"<<std::endl;
            std::cout << "Plant" << std::endl;
            m_holdingPlant=MakePlant(i);
            m_Root.AddChild(m_holdingPlant);
        }
    }
}
//放置植物判斷
void App::PutPlant(glm::vec2 m_click) {
    for (int i=0;i<5;i++) {
        for (int j=0;j<block.size();j++) {
            auto check=block[std::to_string(i)][j];
            if(CheckClick(check,m_click)) {
                m_Plants[i][j]=m_holdingPlant;
                m_holdingPlant->SetPosition(check[4]);
                std::cout << check[4].x<<check[4].y<<std::endl;
                m_holdingPlant=nullptr;
                std::cout<<"put sucsess"<<std::endl;
            }
        }
    }
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




//設定卡片及場地碰撞格
void App::SetPos() {
    float spacingx = 64;
    float startX = -542;
    for(int i=7;i>=0;i--) {
        glm::vec2 pos={startX +spacingx * (i),259};
        m_cardPos[std::to_string(i+1)]={{pos.x-27.5f,pos.y+40},{pos.x+27.5f,pos.y+40},{pos.x+27.5f,pos.y-40},{pos.x-27.5f,pos.y-40}};
    }
    for (int i=1;i<9;i++) {
        std::vector<glm::vec2> temp= m_cardPos[std::to_string(i)];
        for(auto& pos:temp) {
            std::cout << pos.x << ", " << pos.y << std::endl;
        }
    }
    spacingx = 79;
    startX = -405;
    float startY = -220;
    float spacingy = 97;
    for(int i=0;i<5;i++) {
        for (int j=0;j<9;j++) {
            glm::vec2 pos={startX+j*spacingx,startY+i*spacingy};
            std::vector<glm::vec2> temp= {
                {pos.x-spacingx/2,pos.y+spacingy/2},
                {pos.x+spacingx/2,pos.y+spacingy/2},
                {pos.x+spacingx/2,pos.y-spacingy/2},
                {pos.x-spacingx/2,pos.y-spacingy/2},pos};
            block[std::to_string(i)].emplace_back(temp);
        }
    }
    // for (int i = 0; i < 5; i++) {
    //     std::string key = std::to_string(i);
    //     std::cout << "Line " << key << ":" << std::endl;
    //     int idx = 0;
    //     for (auto& singleBlock : block[key]) {
    //         std::cout << "  Block " << idx++ << ":";
    //         for (auto& point : singleBlock) {
    //             std::cout << "(" << point.x << ", " << point.y << ")";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

}
