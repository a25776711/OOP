//
// Created by a2577 on 25-4-6.
//
#include "App.hpp"


std::shared_ptr<Sun> App::CheckSun(glm::vec2 click) {
    for(auto& sun:m_Suns) {
        glm::vec2 pos = sun->GetPosition();
        //LOG_INFO("CheckSun:pos:(x:{},y:{})", pos.x, pos.y);
        sun->CollectAndMove(click);
        if(sun->GetMoveState()==MoveOver)return sun;
    }
    return nullptr;
}
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
        if(CheckClick(card->GetFourPoints(), click)) {
            m_holdingPlant=card->MakePlant();
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
                        m_holdingPlant->Play();
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
                            m_holdingPlant->Play();
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
                            m_holdingPlant->Play();
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
            if(m_Plants[i][j]!=nullptr&&m_Plants[i][j]->GetHP()<=0) {
                m_Root.RemoveChild(m_Plants[i][j]);
                m_Plants[i][j]=nullptr;
            }
            if(m_Plants[i][j]!=nullptr) {
                std::vector<glm::vec2> zpos;
                auto check=m_Plants[i][j];
                if(check->GetType()==Plant::T_Shooter) {
                    for(auto& z : m_zombiManager->GetZombies()) {
                        if(z->GetState() != zombi::zombistate::die&&z->GetState() != zombi::zombistate::stand) 
                            zpos.push_back(z->GetPosition());
                    }
                }
                auto bullet=check->GetType()==Plant::T_Shooter?check->Attack(zpos):nullptr;
                auto m_mine=check->GetType()==Plant::T_Mine?std::dynamic_pointer_cast<Mine>(check):nullptr;
                auto m_bomb=check->GetType()==Plant::T_Bomb?std::dynamic_pointer_cast<Cherrybomb>(check):nullptr;
                switch (check->GetType()) {
                    case Plant::T_Shooter:
                    if(bullet!=nullptr) {
                        bullet->SetZIndex(21);
                        m_Bullets.push_back(bullet);
                        m_Root.AddChild(m_Bullets.back());
                    }
                    break;
                    case Plant::T_Mine:
                        if(m_mine->Attack(m_zombiManager->GetZombies())){
                            m_Root.RemoveChild(m_mine);
                            m_Plants[i][j].reset();
                        }
                        break;
                    case Plant::T_Bomb:
                        if(m_bomb->Attack(m_zombiManager->GetZombies())){
                            m_Root.RemoveChild(m_bomb);
                            m_Plants[i][j].reset();
                        }
                        break;
                    case Plant::T_Chomper:

                        break;
                    case Plant::T_SunFlower:

                        if(check->CoolDown()) {
                            MakeSun(true,check->GetPosition());
                        }
                        break;
                    case Plant::T_WallNut:

                        break;
                    default:

                        break;
                }
            }
        }
    }
}
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
    float spacingx = 80.8f;
    float startX = -445;
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
        if(i==4) {
            auto check=block[std::to_string(i)];
            for(int j=0;j<check.size();j++) {
                check[j][3]-=20;
            }
            block[std::to_string(i)]=check;
        }
    }

}
std::vector<glm::vec2> App::GetZomdiPos() {
    std::vector<glm::vec2> result;
    for(auto zombi : m_zombiManager -> GetZombies()) {
        result.push_back(zombi -> GetPosition());
    }
    return result;
}
void App::ResetSetCarPos() {
    for(auto car : m_Cars) {
        m_Root.RemoveChild(car);
    }
    m_Cars.clear();
    float starty = -235.0f;
    for(int i=0;i<5;i++) {
        m_Cars.push_back(std::make_shared<Car>(glm::vec2(-450, starty),Car::CarState::Idle));
        starty += 100.0f;
        m_Root.AddChild(m_Cars.back());
    }

}
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
