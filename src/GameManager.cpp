#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::PlantUpdate() {
    MoveSun();
    CheckPlant();
    
    CarMoveCheck();
    auto hitzombi=CheckBullet();
    if(m_PRM->GetLevel()>0)SunClock++;
    if(SunClock>480&&m_PRM->GetLevel()>0) {
        SunClock=0;
        MakeSun(false);
    }
    if(m_holdingPlant!=nullptr){
        glm::vec2 pos=Util::Input::GetCursorPosition();
        m_holdingPlant->m_Transform.translation={pos.x,-pos.y};
    }
}
void App::StartGameSet(){
    SetBlockPos();
    PlantLoader::GetInstance();
    m_SunNB->SetZIndex(20);
    m_Root.AddChild(m_SunNB);
    m_Plants=std::vector<std::vector<std::shared_ptr<Plant>>>(5, std::vector<std::shared_ptr<Plant>>(9, nullptr));
    m_PRM = std::make_shared<UpdateBackground>();
    m_zombiManager = std::make_shared<ZombiManager>();
    m_Root.AddChildren(m_PRM->GetChildren());
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

bool Is_Cant_move(std::vector<std::shared_ptr<zombi>> zombies,glm::vec2 pos){
    for(auto& zombi:zombies){
        if(zombi->m_Transform.translation.x==pos.x&&zombi->m_Transform.translation.y==pos.y){
            return true;
        }
    }
    return false;
}

void App::CameraMove(glm::vec2 pos,bool rightnow){
    if(rightnow){
        float distance=120-pos.x;
        LOG_INFO("distance: {}",distance);
        m_Root.Update(glm::vec2(-distance,0));
    }
    else{
        if(move_road){
            m_Root.Update(glm::vec2(1,0));
            road_count++;
            if(road_count==120){
                move_road=false;
                road_count=0;
                move_house=true;
            }
        }
        else if(move_house){
            m_Root.Update(glm::vec2(-1,0));
            house_count++;
            if(house_count==120){
                move_house=false;
                house_count=0;
            }
        }
    }
    auto temp=m_Root.GetChildren();
    for(auto& child:temp){
        LOG_INFO("child: {}",child->GetTransform().scale);
    }
}
void App::CameraUpdate(int type){
    if(type==0){
        CameraMove(m_PRM->GetChildren()[0]->m_Transform.translation,true);
    }
    else if(type==1){
        move_house=true;
        CameraMove(glm::vec2(0,0),false);
    }
    else if(type==2){
        move_road=true;
    }
    else{
        CameraMove(glm::vec2(0,0),false);
    }
}