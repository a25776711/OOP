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
void App::TakePlant(glm::vec2 click,int level) {
    for (int i=1;i<9&&i<level;i++) {
        if(CheckClick(m_cardPos[std::to_string(i)],click)) {
            std::cout << "Plant" << std::endl;
            m_holdingPlant=MakePlant(i);
            m_Root.AddChild(m_holdingPlant);
        }
    }
}
//放置植物判斷
void App::PutPlant(glm::vec2 m_click,int level){
        switch (level) {
            case 1:
                for (int j=0;j<block[std::to_string(2)].size();j++) {
                    auto check=block[std::to_string(2)][j];
                    if(CheckClick(check,m_click)&&m_Plants[2][j]==nullptr){
                        m_Plants[2][j]=m_holdingPlant;
                        m_holdingPlant->SetPosition({check[4],check[5]});
                        m_holdingPlant=nullptr;
                        LOG_INFO("PutPlant on {},{}",check[4],check[5]);
                    }
                }
            break;
            case 2:
                for(int i=1;i<4;i++) {
                    for (int j=0;j<block[std::to_string(i)].size();j++) {
                        auto check=block[std::to_string(i)][j];
                        if(CheckClick(check,m_click)&&m_Plants[i][j]==nullptr) {
                            m_Plants[i][j]=m_holdingPlant;
                            m_holdingPlant->SetPosition({check[4],check[5]});
                            m_holdingPlant=nullptr;
                            LOG_INFO("PutPlant on {},{}",check[4],check[5]);
                        }
                    }
                }
            break;
            default:
                for(int i=0;i<5;i++) {
                    for (int j=0;j<block[std::to_string(i)].size();j++) {
                        auto check=block[std::to_string(i)][j];
                        if(CheckClick(check,m_click)&&m_Plants[i][j]==nullptr) {
                            m_Plants[i][j]=m_holdingPlant;
                            m_holdingPlant->SetPosition({check[4],check[5]});
                            m_holdingPlant=nullptr;
                            LOG_INFO("PutPlant on {},{}",check[4],check[5]);
                        }
                    }
                }
            break;
        }
}


//點擊四個點確認
bool App::CheckClick(std::vector<float> block,glm::vec2 click) {
    //小x,小y,大x,大y
    return (click.x>block[0])&&(click.y>block[1])&&(click.x<block[2])&&(click.y<block[3]);
}
void App::CheckPlant() {
    for(int i=0;i<m_Plants.size();i++) {
        for(int j=0;j<m_Plants[i].size();j++) {
            if(m_Plants[i][j]!=nullptr) {
                auto check=m_Plants[i][j];
                auto bullet=check->Attack(check->GetPosition());
                switch (check->GetType()) {
                    case Plant::Shooter:
                    if(bullet!=nullptr) {
                        std::cout << "test";
                        bullet->SetZIndex(21);
                        m_Bullets.push_back(bullet);
                        m_Root.AddChild(m_Bullets.back());
                    }
                    break;
                    case Plant::Boom:
                        break;
                    case Plant::Closer:
                        break;
                    case Plant::Idle:
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
void App::CheckBullet() {
    for(int i=0;i<m_Bullets.size();i++) {
        auto check=m_Bullets[i];
        check->Move();
    }
}




//設定卡片及場地碰撞格
void App::SetPos() {
    float spacingx = 64;
    float startX = -568;
    for(int i=7;i>=0;i--) {
        glm::vec2 pos={startX +spacingx * (i),300};
        m_cardPos[std::to_string(i+1)]={pos.x,pos.y-80,pos.x + spacingx,pos.y};
    }
    spacingx = 80.8f;
    startX = -445;
    float startY = -260;
    float spacingy = 99;
    for(int i=0;i<5;i++) {
        for (int j=0;j<9;j++) {
            glm::vec2 pos={startX +spacingx * j,startY +spacingy *i};
            std::vector<float> temp= {
                pos.x,pos.y,pos.x+spacingx,pos.y+spacingy,pos.x+spacingx/2,pos.y+spacingy/2
            };
            block[std::to_string(i)].emplace_back(temp);
        }
    }

}
