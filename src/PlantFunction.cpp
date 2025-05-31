//
// Created by a2577 on 25-4-6.
//
#include "App.hpp"
//太陽生成
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
        if(glm::distance(pos,click)<(25*sqrt(2))) {
            sun->CollectAndMove(click);
            if(sun->GetMoveState()==MoveOver)return sun;
        }
    }
    return nullptr;
}
//太陽移動
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
    if(m_PRM->GetLevel()!=5&&m_CameraState==CameraState::idle){
    auto cards=m_PRM->GetCards();
    for(auto& card:cards) {
        if(card->IfCreate()&&
           CheckClick(card->GetFourPoints(),click)&&
           Sunamount>=card->GetCost(m_PRM->GetLevel())) {
            auto plant = card->MakePlant();
            if(plant) {  // 確保植物創建成功
                m_holdingPlant = plant;
                m_Root.AddChild(m_holdingPlant);
            }
        }
    }
    
    if(m_PRM->GetLevel()>4){
        auto shovel=m_PRM->GetShovel();
        if(CheckClick(shovel->GetFourPoints(), click)&&m_holdingPlant==nullptr) {
            m_holdingPlant=shovel;
            shovel->TakeShovel();
        }
    }
    }
    else if(m_CameraState==CameraState::choose_card){
        auto choose_button=m_PRM->GetChooseButton();
        auto cards=m_PRM->GetCards();
        auto cards_chose=m_PRM->GetCards_chose();
        if(cards.size()!=6)
            for(auto& card:cards_chose){
                if(card->GetVisible()){
                    auto temp=std::dynamic_pointer_cast<Card>(card);
                    if(CheckClick(temp->GetFourPoints(),click)){
                        m_Root.AddChild(m_PRM->ChooseCard(true,temp));
                        if(cards.size()==5){
                            choose_button->SetOver(true);
                        }
                        return;
                    }
                }
            }
        if(cards.size()!=0)
            for(auto& card:cards){
                if(CheckClick(card->GetFourPoints(),click)){
                    m_Root.RemoveChild(m_PRM->ChooseCard(false,card));
                    choose_button->SetOver(false);
                    return;
                }
            }
        if(cards.size()==6&&CheckClick(choose_button->GetFourPoints(),click)){
            m_PRM->ShowChoseCardList(false);
            m_CameraState=CameraState::hide_choose_card;
            CameraMoveHidden(3);
        }
    }
    else{
        auto cards=m_PRM->GetPlayCard();
        for(auto& card:cards){
            if(CheckClick(card->GetFourPoints(),click)){
                m_holdingPlant=card->MakePlant();
                m_PlayCard=card;
                m_Root.AddChild(m_holdingPlant);
            }
        }
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
                        for(auto& card:m_PRM->GetCards()){
                            if(card->GetType()==m_holdingPlant->GetType()){
                                card->Create();
                            }
                        }
                        m_holdingPlant=nullptr;
                        return;
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
                            for(auto& card:m_PRM->GetCards()){
                                if(card->GetType()==m_holdingPlant->GetType()){
                                    card->Create();
                                }
                            }
                            m_holdingPlant.reset();
                            return;
                        }
                    }
                }
            break;
            default:
                for(int i=0;i<5;i++) {
                    for (int j=0;j<block[std::to_string(i)].size();j++) {
                        auto check=block[std::to_string(i)][j];
                        if(CheckClick(check,m_click)&&m_Plants[i][j]==nullptr&&m_holdingPlant->GetType()!=Plant::T_Shovel) {
                            if(m_holdingPlant->GetType()==Plant::T_Play_Wallnut||m_holdingPlant->GetType()==Plant::T_Play_Wallnut_Boom) {
                                m_Play_Wallnut.push_back(m_holdingPlant);
                                auto m_play_wallnut=std::dynamic_pointer_cast<Play_wallnut>(m_holdingPlant);
                                m_holdingPlant->SetPosition({check[4],check[5]});
                                m_holdingPlant->Play(true);
                                m_holdingPlant=nullptr;
                                m_PRM->RemovePlayCard(m_PlayCard);
                                m_Root.RemoveChild(m_PlayCard);
                                m_PlayCard.reset();
                                return;
                            }
                            Sunamount-=m_holdingPlant->GetCost();
                            m_SunNB->Change(Sunamount);
                            m_Plants[i][j]=m_holdingPlant;
                            m_holdingPlant->Play(true);
                            m_holdingPlant->SetPosition({check[4],check[5]});
                            LOG_INFO("PutPlant {} on {},{}",m_holdingPlant->GetType(),check[4],check[5]);
                            for(auto& card:m_PRM->GetCards()){
                                if(card->GetType()==m_holdingPlant->GetType()){
                                    card->Create();
                                }
                            }
                            m_holdingPlant.reset();
                            return;
                        }
                        else if(m_holdingPlant->GetType()==Plant::T_Shovel) {
                            auto shovel=std::dynamic_pointer_cast<Shovel>(m_holdingPlant);
                            if(CheckClick(check,m_click)) {
                                if(m_Plants[i][j]!=nullptr) {
                                    m_Root.RemoveChild(m_Plants[i][j]);
                                    m_Plants[i][j].reset();
                                }
                                m_holdingPlant.reset();
                                shovel->UseShovel();
                                return;
                            }
                        }
                    }
                }

            break;
        }
        if(m_holdingPlant!=nullptr){
            if(m_holdingPlant->GetType()==Plant::T_Shovel){
                auto shovel=std::dynamic_pointer_cast<Shovel>(m_holdingPlant);
                shovel->UseShovel();
                m_holdingPlant.reset();
                return;
            }
            m_Root.RemoveChild(m_holdingPlant);
            m_holdingPlant.reset();
        }
}


//點擊四個點確認
bool App::CheckClick(std::vector<float> block,glm::vec2 click) {
    //小x,小y,大x,大y
    return (click.x>block[0])&&(click.y>block[1])&&(click.x<block[2])&&(click.y<block[3]);
}
//植物動作更新&血量確認
void App::CheckPlant(std::vector<std::shared_ptr<zombi>> m_zombis,std::vector<glm::vec2> m_zombiPos) {
    //一般關卡植物動作更新&血量確認
    if(m_PRM->GetLevel()!=5){
    for(int i=0;i<m_Plants.size();i++) {
        for(int j=0;j<m_Plants[i].size();j++) {
            if(m_Plants[i][j]!=nullptr&&m_Plants[i][j]->GetHP()<=0) {
                m_Root.RemoveChild(m_Plants[i][j]);
                m_Plants[i][j].reset();
            }
            if(m_Plants[i][j]!=nullptr){
                auto check=m_Plants[i][j];
                if (check->GetType() == Plant::T_Peashooter||check->GetType() == Plant::T_IceShooter||check->GetType() == Plant::T_FastShooter) {
                    
                    auto bullet=check->Attack(m_zombiPos);
                    if(bullet!=nullptr) {
                        bullet->SetZIndex(21);
                        m_Bullets.push_back(bullet);
                        m_Root.AddChild(m_Bullets.back());
                    }
                }
                else if (check->GetType() == Plant::T_Mine) {

                    auto m_mine=std::dynamic_pointer_cast<Mine>(check);
                    if(m_mine->Attack(m_zombis)){
                        m_Root.RemoveChild(m_mine);
                        m_Plants[i][j].reset();
                    }
                }
                else if (check->GetType() == Plant::T_Bomb) {
                    auto m_bomb=std::dynamic_pointer_cast<Cherrybomb>(check);
                    if(m_bomb->Attack(m_zombis)){
                        m_Root.RemoveChild(m_bomb);
                        m_Plants[i][j].reset();
                    }
                }
                else if (check->GetType() == Plant::T_Chomper) {
                    if(check!=nullptr){
                        auto m_chomper=std::dynamic_pointer_cast<Chomper>(check);
                        std::shared_ptr<zombi> z=m_chomper->Attack(m_zombis);
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
                    if(m_play_wallnut->Update(m_zombis)) {
                        m_Root.RemoveChild(check);
                        m_Plants[i][j].reset();
                    }
                }
            }
        }
    }
    }
    //娛樂關保齡球更新
    else{
        m_Play_Wallnut.erase(
            std::remove_if(m_Play_Wallnut.begin(), m_Play_Wallnut.end(),
                [&](auto& wallnut) {
                    if (!wallnut) return true;
                    if(wallnut->GetType()==Plant::T_Play_Wallnut_Boom){
                        auto m_wallnut = std::dynamic_pointer_cast<Play_wallnut_boom>(wallnut);
                        if (m_wallnut->Update(m_zombiManager->GetZombies())) {
                            m_Root.RemoveChild(wallnut);
                            wallnut.reset();
                            return true;
                        }
                    }
                    else{
                        auto m_wallnut = std::dynamic_pointer_cast<Play_wallnut>(wallnut);
                        if (m_wallnut->Update(m_zombiManager->GetZombies())) {
                            m_Root.RemoveChild(wallnut);
                            wallnut.reset();
                            return true;
                        }
                    }
                    return false;
                }
            ),m_Play_Wallnut.end()
        );
    }
}
//子彈動作
void App::CheckBullet() {
    m_Bullets.erase(
        std::remove_if(m_Bullets.begin(), m_Bullets.end(),
            [&](auto& check) {
                check->Move();
                if(check->GetPosition().x > 650) {
                    m_Root.RemoveChild(check);
                    return true;
                }
                for(auto& z : m_zombis) {
                    if(z->GetState() != zombi::zombistate::stand&&z->GetState() != zombi::zombistate::die&& check->HitCheck(z->GetTransform().translation)) {
                        z->GetHeart(false, check->GetType() == Ice, check->GetDamage());
                        m_Root.RemoveChild(check);
                        return true;
                    }
                }
                return false;
            }
        ),
        m_Bullets.end()
    );
}
//設定卡片及場地碰撞格
void App::SetBlockPos() {
    float spacingx = 97;
    float startX = -428;
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
    for(auto& z : m_zombis) {
        if(z->GetState() != zombi::zombistate::die&&z->GetState() != zombi::zombistate::stand) 
            result.push_back(z->GetPosition());
    }
    return result;
}
//車子位置初始化
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
    float baseY = -300.0f;
    float spacing = 125.0f;
    
    for(int i=0;i<5;i++) {
        for(auto& r : road) {
            if(i==r) {
                auto car=std::make_shared<Car>(glm::vec2(-450, baseY + i * spacing),Car::CarState::Idle);
                m_Cars[i]=car;
                m_Root.AddChild(car);
                break;
            }
        }
    }
}
//車子動作確認
void App::CarMoveCheck() {
    std::vector<glm::vec2> carpos;
    for(auto& car : m_Cars) {
        if(car!=nullptr) {
            carpos.push_back(car->GetPosition());
        }else{
            carpos.push_back({-999,0});
        }
    }
    for(auto& z : m_zombiPos) {
        for(int i=0;i<5;i++) {
            if(carpos[4-i]!=glm::vec2(-999,0)&&m_Cars[4-i]->IsTouch(z,i)) {
                int targetIndex = 4-i;
                if(targetIndex >= 0 && targetIndex < m_Cars.size() && m_Cars[targetIndex] != nullptr) {
                    m_Cars[targetIndex]->SetState(Car::CarState::Move);
                    
                    m_Cars[targetIndex]->SetZIndex(10);
                    if(m_Cars[targetIndex]->GetPosition().x > 650) {
                        m_Root.RemoveChild(m_Cars[targetIndex]);
                        m_Cars[targetIndex].reset();
                    }
                }
            }
        }
    }
    for(auto& car : m_Cars) {
        if(car!=nullptr&&car->GetState()==Car::CarState::Move)car->Move();
    }
}

