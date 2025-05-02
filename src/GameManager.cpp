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
