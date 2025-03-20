#include "App.hpp"

#include "Background/UpdateBackground.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");



    m_PRM = std::make_shared<UpdateBackground>();
    //m_PRM ->SetScale({2.0f, 2.0f});
    m_Root.AddChild(m_PRM->GetChild());

    m_CurrentState = State::UPDATE;


}

void App::Update() {
    

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
<<<<<<< Updated upstream
            m_PRM ->NextLevel();
            m_Root.AddChild(m_PRM->GetChild());
=======
            m_PRM -> NextLevel();
            m_Root.AddChildren(m_PRM->GetChildren());
>>>>>>> Stashed changes
        }
    }

    m_normal = std::make_shared<normal>();
    m_normal -> SetZIndex(5);
    m_normal -> SetVisible(true);
    // m_normal ->SetLooping(true);
    // m_normal ->SetPlaying(true);
    m_normal ->SetPosition({m_normal->GetPosition().x+30,m_normal->GetPosition().y+30,});
    m_Root.AddChild(m_normal);



    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    m_Root.Update();

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
