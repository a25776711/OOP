#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Context.hpp"
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

void App::CameraMoveHidden(int hidden){
    if(hidden==0){
        auto background_hidden=m_PRM->GetChildren();
        for(size_t i=1;i<background_hidden.size();i++){
            background_hidden[i]->SetVisible(false);
        }
        for(auto& car:m_Cars){
            if(car!=nullptr){
                car->SetVisible(false);
            }
        }
    }
    else if(hidden==1){
        auto background_hidden=m_PRM->GetChildren();
        for(size_t i=1;i<background_hidden.size();i++){
            background_hidden[i]->SetVisible(true);
        }
        for(auto& car:m_Cars){
            if(car!=nullptr){
                car->SetVisible(true);
            }
        }
    }
}

void App::CameraMove(){
        if (m_CameraState == CameraState::grass) {
            if(m_CameraStart){
                m_CameraStart=false;
            }
            CameraMoveHidden(0);
            m_CameraState = CameraState::move_road;
        }
    else{
        glm::vec2 moveAmount = {0,0};
        if(m_CameraState == CameraState::move_road){
            if(road_count<120){
                moveAmount = {1,0};
                road_count++;   
            }
            else if(road_count<200){
                road_count++;   
            }
            else{
                m_CameraState = CameraState::move_house;
                road_count=0;
            }
        }
        else if(m_CameraState == CameraState::move_house){
            if(house_count<120){
                moveAmount = {-1,0};
                house_count++;
            }
            else{
                CameraMoveHidden(1);
                m_CameraState = CameraState::idle;
                house_count=0;
            }
        }
        m_Root.Update(moveAmount);
    }
}
void App::ResizeWindow(int width, int height) {
    auto context = Core::Context::GetInstance();
    context->SetWindowWidth(width);
    context->SetWindowHeight(height);
    SDL_SetWindowSize(context->GetWindow(), width, height);
    
    // 更新渲染範圍，但保持投影矩陣不變
    glViewport(0, 0, width, height);
    
    // 強制重新計算投影矩陣
    PTSD_Config::WINDOW_WIDTH = width;
    PTSD_Config::WINDOW_HEIGHT = height;
}