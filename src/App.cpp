#include "App.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/Adventure.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <iostream>

void App::Start() {
    LOG_TRACE("Start");
    m_PRM = std::make_shared<UpdateBackground>();
    //m_PRM ->SetScale({2.0f, 2.0f});
    m_Root.AddChildren(m_PRM->GetChildren());

    // m_Root.AddChildren(m_PRM->GetCard());

    m_CurrentState = State::UPDATE;


}

void App::Update() {

    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        std::cout <<"X:"<< pos.x << std::endl;
        std::cout <<"Y:"<< pos.y << std::endl;

    }
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)){

            m_PRM ->NextLevel();
            m_Root.AddChildren(m_PRM->GetChildren());
        }
    }



    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        if (m_PRM ->GetLevel()==0) {
            if (m_PRM ->CheckHit(pos)) {
                // std::cout << "true" << std::endl;
                m_PRM ->NextLevel();
            }
        }
    }

    // m_normal = std::make_shared<normal>();
    // m_normal -> SetZIndex(5);
    // m_normal -> SetVisible(true);

    // m_normal ->SetLooping(true);
    // m_normal ->SetPlaying(true);
    // m_normal ->SetPosition({m_normal->GetPosition().x+30,m_normal->GetPosition().y+30,});
    // m_Root.AddChild(m_normal);



    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    m_Root.Update();

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
