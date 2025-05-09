//
// Created by a2577 on 25-4-6.
//
#include "App.hpp"

void App::MakeSun(bool flower,glm::vec2 pos)  {
        auto temp=std::make_shared<Sun>(flower,pos);
        temp->SetZIndex(100);
        m_Suns.emplace_back(temp);
        m_Root.AddChild(m_Suns.back());
        temp->Play(true);
}

//太陽收集
std::shared_ptr<Sun> App::CheckSunCollect(glm::vec2 click) {
    for(auto& sun:m_Suns) {
        glm::vec2 pos = sun->GetPosition();
        if(glm::distance(pos,click)<(20*sqrt(2))) {
            sun->CollectAndMove(click);
            if(sun->GetMoveState()==MoveOver)return sun;
        }
    }
    return nullptr;
}
//太陽動作
void App::MoveSun() {
    m_Suns.erase(
        std::remove_if(m_Suns.begin(), m_Suns.end(), 
            [&](std::shared_ptr<Sun>& sun) {
                sun->Move();
                if(sun->GetMoveState()==MoveOver) {
                    m_Root.RemoveChild(sun);
                    Sunamount+=25;
                    m_SunNB->Change(Sunamount);
                    return true;  // 標記為要刪除
                }
                return false;  // 保留
            }
        ), 
        m_Suns.end()
    );
}

//點擊卡片判斷
void App::TakePlant(glm::vec2 click,int level) {
    auto cards=m_PRM->GetCards();
    for(auto& card:cards) {
        if(CheckClick(card->GetFourPoints(), click)&&m_holdingPlant==nullptr&&Sunamount>=card->MakePlant(level)->GetCost()) {
            m_holdingPlant=card->MakePlant(level);
            m_Root.AddChild(m_holdingPlant);
            LOG_INFO("Plant selected: {}, Cost: {}, Current Sun: {}", 
                m_holdingPlant->GetType(),
                m_holdingPlant->GetCost(), 
                Sunamount);
        }
    }
    auto shovel=m_PRM->GetShovel();
    if(m_PRM->GetLevel()>4&&CheckClick(shovel->GetFourPoints(), click)&&m_holdingPlant==nullptr) {
        m_holdingPlant=shovel;
        shovel->TakeShovel();
    }
}
//放置植物判斷
void App::PutPlant(glm::vec2 m_click,int level){
        LOG_INFO("Level:{}",level);
        switch (level) {
            case 1:
                for (int j=0;j<block[std::to_string(2)].size();j++) {
                    auto check=block[std::to_string(2)][j];
                    if(CheckClick(check,m_click)&&m_Plants[2][j]==nullptr){
                        Sunamount-=m_holdingPlant->GetCost();
                        m_SunNB->Change(Sunamount);
                        m_Plants[2][j]=m_holdingPlant;
                        m_holdingPlant->Play(true);
                        m_holdingPlant->SetPosition({check[4],check[5]});
                        LOG_INFO("PutPlant {} on {},{}",m_holdingPlant->GetType(),check[4],check[5]);
                        m_holdingPlant=nullptr;
                        
                    }
                }
            break;
            case 2:
                for(int i=1;i<4;i++) {
                    for (int j=0;j<block[std::to_string(i)].size();j++) {
                        auto check=block[std::to_string(i)][j];
                        if(CheckClick(check,m_click)&&m_Plants[i][j]==nullptr) {
                            Sunamount-=m_holdingPlant->GetCost();
                            m_SunNB->Change(Sunamount);
                            m_Plants[i][j]=m_holdingPlant;
                            m_holdingPlant->Play(true);
                            m_holdingPlant->SetPosition({check[4],check[5]});
                            LOG_INFO("PutPlant {} on {},{}",m_holdingPlant->GetType(),check[4],check[5]);
                            m_holdingPlant=nullptr;
                        }
                    }
                }
            break;
            default:
                for(int i=0;i<5;i++) {
                    for (int j=0;j<block[std::to_string(i)].size();j++) {
                        auto check=block[std::to_string(i)][j];
                        if(CheckClick(check,m_click)&&m_Plants[i][j]==nullptr&&m_holdingPlant->GetType()!=Plant::T_Shovel) {
                            Sunamount-=m_holdingPlant->GetCost();
                            m_SunNB->Change(Sunamount);
                            m_Plants[i][j]=m_holdingPlant;
                            m_holdingPlant->Play(true);
                            m_holdingPlant->SetPosition({check[4],check[5]});
                            LOG_INFO("PutPlant {} on {},{}",m_holdingPlant->GetType(),check[4],check[5]);
                            m_holdingPlant=nullptr;
                            return;
                        }
                        else if(m_holdingPlant->GetType()==Plant::T_Shovel) {
                            std::cout<<"use shovel"<<std::endl;
                            auto shovel=std::dynamic_pointer_cast<Shovel>(m_holdingPlant);
                            if(CheckClick(check,m_click)) {
                                std::cout<<"use shovel"<<std::endl;
                                if(m_Plants[i][j]!=nullptr) {
                                    m_Root.RemoveChild(m_Plants[i][j]);
                                    m_Plants[i][j]=nullptr;
                                }
                                std::cout<<"use shovel"<<std::endl;
                                m_holdingPlant=nullptr;
                                shovel->UseShovel();
                                return;
                            }
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
//植物動作血量確認
void App::CheckPlant() {
    for(int i=0;i<m_Plants.size();i++) {
        for(int j=0;j<m_Plants[i].size();j++) {
            if(m_Plants[i][j]!=nullptr&&m_Plants[i][j]->GetHP()<=0) {
                m_Root.RemoveChild(m_Plants[i][j]);
                m_Plants[i][j]=nullptr;
            }
            if(m_Plants[i][j]!=nullptr) {
                std::vector<glm::vec2> zpos;
                auto check=m_Plants[i][j];
                if (check->GetType() == Plant::T_Shooter) {
                    for(auto& z : m_zombiManager->GetZombies()) {
                        if(z->GetState() != zombi::zombistate::die&&z->GetState() != zombi::zombistate::stand) 
                            zpos.push_back(z->GetPosition());
                    }
                    auto bullet=check->Attack(zpos);
                    if(bullet!=nullptr) {
                        bullet->SetZIndex(21);
                        m_Bullets.push_back(bullet);
                        m_Root.AddChild(m_Bullets.back());
                    }
                }
                else if (check->GetType() == Plant::T_Mine) {
                    auto m_mine=std::dynamic_pointer_cast<Mine>(check);
                    if(m_mine->Attack(m_zombiManager->GetZombies())){
                        m_Root.RemoveChild(m_mine);
                        m_Plants[i][j].reset();
                    }
                }
                else if (check->GetType() == Plant::T_Bomb) {
                    auto m_bomb=std::dynamic_pointer_cast<Cherrybomb>(check);
                    if(m_bomb->Attack(m_zombiManager->GetZombies())){
                        m_Root.RemoveChild(m_bomb);
                        m_Plants[i][j].reset();
                    }
                }
                else if (check->GetType() == Plant::T_Chomper) {
                    if(check!=nullptr){
                        auto m_chomper=std::dynamic_pointer_cast<Chomper>(check);
                        std::shared_ptr<zombi> z=m_chomper->Attack(m_zombiManager->GetZombies());
                        if(z!=nullptr){
                            m_Root.RemoveChild(z);
                            z->GetHeart(false,false,100);
                        }
                    }
                }
                else if (check->GetType() == Plant::T_SunFlower) {
                    if(check->CoolDown()) {
                        MakeSun(true,check->GetPosition());
                    }
                }
                else if (check->GetType() == Plant::T_WallNut) {
                    // 保持空白的 WallNut case
                }
                else if (check->GetType() == Plant::T_Play_Wallnut) {
                    auto m_play_wallnut=std::dynamic_pointer_cast<Play_wallnut>(check);
                    if(m_play_wallnut->Update()) {
                        m_Root.RemoveChild(check);
                        m_Plants[i][j].reset();
                    }
                }
            }
        }
    }
}
//子彈動作
std::vector<std::shared_ptr<zombi>> App::CheckBullet() {
    std::vector<std::shared_ptr<zombi>> zom=m_zombiManager->GetZombies();
    std::vector<std::shared_ptr<zombi>> result;
    m_Bullets.erase(
        std::remove_if(m_Bullets.begin(), m_Bullets.end(),
            [&](auto& check) {
                check->Move();
                if(check->GetPosition().x > 650) {
                    m_Root.RemoveChild(check);
                    return true;
                }
                for(auto& z : zom) {
                    if(z->GetState() != zombi::zombistate::stand&&z->GetState() != zombi::zombistate::die&& check->HitCheck(z->GetTransform().translation)) {
                        z->GetHeart(false, check->GetType() == Ice, check->GetDamage());
                        m_Root.RemoveChild(check);
                        result.push_back(z);
                        return true;
                    }
                }
                return false;
            }
        ),
        m_Bullets.end()
    );
    
    return result;
}
//設定卡片及場地碰撞格
void App::SetBlockPos() {
    float spacingx = 98;
    float startX = -540;
    float startY = -340;
    float spacingy = 125;
    for(int i=0;i<5;i++) {
        for (int j=0;j<9;j++) {
            glm::vec2 pos={startX +spacingx * j,startY +spacingy *i};
            std::vector<float> temp= {
                pos.x,pos.y,pos.x+spacingx,pos.y+spacingy,pos.x+spacingx/2,pos.y+spacingy/2
            };
            block[std::to_string(i)].emplace_back(temp);
        }
        if(i==4) {
            auto check=block[std::to_string(i)];
            for(int j=0;j<check.size();j++) {
                check[j][3]-=20;
            }
            block[std::to_string(i)]=check;
        }
    }

}
//僵屍位置
std::vector<glm::vec2> App::GetZomdiPos() {
    std::vector<glm::vec2> result;
    for(auto zombi : m_zombiManager -> GetZombies()) {
        result.push_back(zombi -> GetPosition());
    }
    return result;
}
//車子位置
void App::ResetSetCarPos(int level) {
    for(auto car : m_Cars) {
        if(car!=nullptr)m_Root.RemoveChild(car);
    }
    std::vector<int> road;
    if(level==1)road={2};
    else if(level==2)road={1,2,3};
    else road={0,1,2,3,4};
    m_Cars.clear();
    m_Cars.resize(5,nullptr);
    
    // 根據第一個道路的索引計算起始位置
    float baseY = -235.0f;
    float spacing = 100.0f;
    std::vector<int> five_road={-235,-135,-35,65,165};
    
    for(int i=0;i<5;i++) {
        for(auto& r : road) {
            if(i==r) {
                auto car=std::make_shared<Car>(glm::vec2(-550, five_road[i]),Car::CarState::Idle);
                m_Cars[i]=car;
                m_Root.AddChild(car);
                break;
            }
        }
    }
}
//車子動作
void App::CarMoveCheck() {
    std::vector<glm::vec2> carpos ;
    for(auto& car : m_Cars) {
        if(car!=nullptr) {
            carpos.push_back(car->GetPosition());
        }else{
            carpos.push_back({-999,0});
        }
    }
    for(auto& z : GetZomdiPos()) {
        for(int i=0;i<5;i++) {
            if(carpos[4-i]!=glm::vec2(-999,0)&&m_Cars[4-i]->IsTouch(z,i)) {
                int targetIndex = 4-i;
                if(targetIndex >= 0 && targetIndex < m_Cars.size() && m_Cars[targetIndex] != nullptr) {
                    m_Cars[targetIndex]->SetState(Car::CarState::Move);
                    m_Cars[targetIndex]->Move();
                    m_Cars[targetIndex]->SetZIndex(10);
                    if(m_Cars[targetIndex]->GetPosition().x > 650) {
                        m_Root.RemoveChild(m_Cars[targetIndex]);
                        m_Cars[targetIndex].reset();
                    }
                }
            }
        }
    }
}
//重置植物方場地
void App::ResetPlant(int level) {
    ResetSetCarPos(level);
    for(auto& plant : m_Plants) {
        for(auto& p : plant) {
            if(p != nullptr) {
                m_Root.RemoveChild(p);
            }
        }
    }
    m_Plants.clear();
    // 重新初始化 m_Plants
    m_Plants = std::vector<std::vector<std::shared_ptr<Plant>>>(5, std::vector<std::shared_ptr<Plant>>(9, nullptr));
    
    for(auto& bullet : m_Bullets) {
        m_Root.RemoveChild(bullet);
    }
    m_Bullets.clear();
    if(m_holdingPlant != nullptr) {
        m_Root.RemoveChild(m_holdingPlant);
        m_holdingPlant = nullptr;
    }
    Sunamount=0;
    m_SunNB->Change(Sunamount);
    for(auto& sun : m_Suns) {
        m_Root.RemoveChild(sun);
    }
    m_Suns.clear();
}
