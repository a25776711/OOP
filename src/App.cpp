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
    m_zombiManager = std::make_shared<ZombiManager>();
    m_Root.AddChildren(m_PRM->GetChildren());
    m_SunNB->SetZIndex(20);
    m_Root.AddChild(m_SunNB);;
    m_CurrentState = State::UPDATE;

}

void App::Update() {
    // if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
    //     glm::vec2 pos=Util::Input::GetCursorPosition();
    //     pos.y=-pos.y;
    //     std::cout <<"X:"<< pos.x << std::endl;
    //     std::cout <<"Y:"<< pos.y << std::endl;
    // }

    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        pos.y=-pos.y;
        auto checksun=CheckSun(pos);
        if(checksun!=nullptr){m_Root.RemoveChild(checksun);}
        if (m_PRM ->GetLevel()==0) {
            if (m_PRM ->CheckHit(pos)) {
                // std::cout << "true" << std::endl;
                m_PRM ->NextLevel();
                m_Root.AddChildren(m_PRM->GetChildren());
            }
        }
    }
    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
            m_PRM ->NextLevel();
            std::cout << (m_zombiManager -> GetZombies().size()) << std::endl;
            for (auto zombi : m_zombiManager -> GetZombies()) {
                m_Root.RemoveChild(zombi);
            }
            m_Root.AddChildren(m_PRM-> GetChildren());
            m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
            if (m_PRM -> GetLevel() ==11){ m_CurrentState = State::END;}
        }
    }
    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        // m_Sun->CollectAndMove(pos,{200,50});
        if (m_PRM ->GetLevel()==0) {
            if (m_PRM ->CheckHit(pos)) {
                m_PRM ->NextLevel();
            }

        }
       m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
    };
    m_zombiManager -> move();


    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        m_zombiManager ->Getice(true);
    }


    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    MoveSun();
    SunClock++;
    if(SunClock>480) {
        SunClock=0;
        MakeSun();
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
    Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
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
std::shared_ptr<Plant> App::CheckPlant(glm::vec2 click) {

}
void App::SetPos() {
    m_cardPos["0"]={{},{},{},{}};
    for(int i=0;i<8;i++) {
        m_cardPos[std::to_string(i)]={{},{},{},{}};
    }
}

