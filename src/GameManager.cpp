#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Context.hpp"
//植物&卡牌&太陽更新
void App::PlantUpdate() {
    m_zombis=m_zombiManager->GetZombies();
    m_zombiPos=GetZomdiPos();

    MoveSun();
    CheckPlant(m_zombis,m_zombiPos);
    
    CarMoveCheck();
    CheckBullet();
    if(m_PRM->GetLevel()>0&&m_PRM->GetLevel()!=5)SunClock++;
    if(SunClock>350&&m_PRM->GetLevel()>0&&m_PRM->GetLevel()!=5) {
        SunClock=0;
        MakeSun(false);
    }
    if(m_holdingPlant!=nullptr){
        glm::vec2 pos=Util::Input::GetCursorPosition();
        m_holdingPlant->m_Transform.translation={pos.x,-pos.y};
    }
    // 更新所有卡片的冷卻
    auto cards = m_PRM->GetCards();
    for(auto& card : cards) {
        card->Update();
    }
    if(m_PRM->GetLevel()==5&&m_ready==nullptr){
        auto play_cards = m_PRM->PlayCard();
        if(play_cards!=nullptr)m_Root.AddChild(play_cards);
        m_PRM->UpdatePlayCard();
    }
}
//遊戲初始化
void App::StartGameSet(){
    PlantLoader::GetInstance();

    int m_CurrentZombiIndex = 0;
    int zombicount = 0;
    int Sunamount=0;
    m_SunNB->Change(Sunamount);
    m_SunNB->SetVisible(false);
    int SunClock=0;
    int road_count=0;
    int house_count=0;
    SetBlockPos();
    m_SunNB->SetZIndex(20);
    m_Root.AddChild(m_SunNB);
    m_Plants=std::vector<std::vector<std::shared_ptr<Plant>>>(5, std::vector<std::shared_ptr<Plant>>(9, nullptr));
    m_PRM = std::make_shared<UpdateBackground>();
    m_zombiManager = std::make_shared<ZombiManager>();
    m_Root.AddChildren(m_PRM->GetChildren());
    m_zombis=m_zombiManager->GetZombies();
    m_zombiPos=GetZomdiPos();
}
void App::FpsShow(){
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoBackground);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::CameraMoveHidden(int hidden){
    if(hidden==0){
        m_SunNB->SetVisible(false);
        auto background_hidden=m_PRM->GetChildren();
        if(m_PRM->GetLevel()!=5)
            for(size_t i=1;i<background_hidden.size();i++)
                background_hidden[i]->SetVisible(false);
        else
            for(size_t i=2;i<background_hidden.size();i++)
                background_hidden[i]->SetVisible(false);
        
        for(auto& car:m_Cars){
            if(car!=nullptr){
                car->SetVisible(false);
            }
        }
        for(auto& card:m_PRM->GetCards())
            card->SetVisible(false);
        for(auto& card:m_PRM->GetCards_chose())
            card->SetVisible(false);
    }
    else if(hidden==1){
        m_SunNB->SetVisible(m_PRM->GetLevel()!=5);
        auto background_hidden=m_PRM->GetChildren();
        if(m_PRM->GetLevel()<5){
            for(size_t i=1;i<background_hidden.size()-5;i++)
                background_hidden[i]->SetVisible(true);
        }
        else if(m_PRM->GetLevel()==5){
            for(size_t i=2;i<background_hidden.size()-2;i++)
                background_hidden[i]->SetVisible(true);
        }
        else{
            for(size_t i=1;i<background_hidden.size()-3;i++)
                background_hidden[i]->SetVisible(true);
        }
        for(auto& car:m_Cars){
            if(car!=nullptr){
                car->SetVisible(true);
            }
        }
        for(auto& card:m_PRM->GetCards())
            card->SetVisible(true);
    }
    else if(hidden==2){
        auto choose_as_game_object=m_PRM->GetChoseAsGameObject(true);
        for(auto& game_object : choose_as_game_object){
            game_object->SetVisible(true);
        }
    }
    else if(hidden==3){
        auto choose_as_game_object=m_PRM->GetChoseAsGameObject(false);
        for(auto& game_object : choose_as_game_object){
            game_object->SetVisible(false);
        }
    }
}
//重置植物方場地
void App::ResetPlant(int level) {
    ResetSetCarPos(level);
    for(auto& plant : m_Plants) 
        for(auto& p : plant) 
            if(p != nullptr) 
                m_Root.RemoveChild(p);
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
    SunClock=0;
    m_SunNB->Change(Sunamount);
    m_SunNB->SetVisible(bool(m_PRM->GetLevel()!=5));
    for(auto& sun : m_Suns) {
        m_Root.RemoveChild(sun);
    }
    m_Suns.clear();
    if(m_PRM->GetLevel()==6){
        for(auto& nut:m_Play_Wallnut){
            m_Root.RemoveChild(nut);
        }
        m_Play_Wallnut.clear();
    }
}
//位移及相機狀態切換
void App::GameObjectUpdate(){
    glm::vec2 moveAmount = {0,0};
    if(m_CameraState == CameraState::move_road){
        CameraMoveHidden(0);
        if(road_count<90){
            moveAmount = {4,0};
            road_count++;
            if(road_count==90&&m_PRM->GetLevel()>7){
                m_CameraState = CameraState::show_choose_card;
                CameraMoveHidden(2);
            }
        }
        else if(m_CameraState!=CameraState::show_choose_card&&road_count<150){
            road_count++;
        }
        else{
            m_CameraState = CameraState::move_house;
            road_count=0;
        }
    }
    else if(m_CameraState==CameraState::show_choose_card){
        m_PRM->ShowChoseCardList(true);
        m_Root.AddChildren(m_PRM->GetCards_chose());
        m_PRM->ResetCardandCardListPos();
        m_CameraState=CameraState::choose_card;
    }
    else if(m_CameraState==CameraState::hide_choose_card){
        m_PRM->ShowChoseCardList(false);
        m_CameraState = CameraState::move_house;
        road_count=0;
        std::cout<<"hide_choose_card"<<std::endl;
    }
    else if(m_CameraState == CameraState::move_house){
        if(house_count<90){
            moveAmount = {-4,0};
            house_count++;
        }
        else{
            m_ready = std::make_shared<Ready>();
            m_Root.AddChild(m_ready);
            m_ready->SetVisible(true);
            m_ready->Play();
            CameraMoveHidden(1);
            m_PRM->ResetCardandCardListPos();
            m_CameraState = CameraState::idle;
            house_count=0;
        }
    }
    m_Root.Update(moveAmount);
    
}