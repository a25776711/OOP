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
    m_Root.AddChild(m_SunNB);
    m_Plants=std::vector<std::vector<std::shared_ptr<Plant>>>(5, std::vector<std::shared_ptr<Plant>>(9, nullptr));
    SetBlockPos(); //set card and block
    m_CurrentState = State::UPDATE;

}

void App::Update() {
    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        pos.y=-pos.y;
        std::cout <<"("<< pos.x <<","<<pos.y<<")"<< std::endl;
    }

    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        pos.y=-pos.y;
        if(CheckSun(pos)){m_Root.RemoveChild(CheckSun(pos));}
        if(m_holdingPlant==nullptr){TakePlant(pos,m_PRM->GetLevel()+1);}
        if(m_holdingPlant!=nullptr){PutPlant(pos,m_PRM->GetLevel());}
        if (m_PRM ->GetLevel()==0) {
            if (m_PRM -> CheckHit(pos)) {
                m_PRM ->NextLevel();
                m_Root.AddChildren(m_PRM->GetChildren());
                m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
            }
        }

    }
    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
            m_PRM ->NextLevel();
            m_CurrentZombiIndex =0;
            for (auto zombi : m_zombiManager -> GetZombies()) {
                m_Root.RemoveChild(zombi);
            }
            m_Root.AddChildren(m_PRM-> GetChildren());
            m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
            if (m_PRM -> GetLevel() ==11){ m_CurrentState = State::END;}
        }
    }

    if (m_PRM ->GetLevel() != 0) {
        bool isKPressed = Util::Input::IsKeyPressed(Util::Keycode::K);

        if (!m_KDown && isKPressed) {
            // 按下K當下觸發一次
            if (m_CurrentZombiIndex < m_zombiManager->GetZombies().size()) {
                m_zombiManager->SetLoop(m_CurrentZombiIndex++);
            }
        }
        m_KDown = isKPressed; // 更新鍵盤狀態

        bool isDPressed = Util::Input::IsKeyPressed(Util::Keycode::D);
        bool isSPressed = Util::Input::IsKeyPressed(Util::Keycode::S);

        if (!m_KDown && isDPressed) {
            m_zombiManager -> Die(false);
        }
        if (!m_KDown && isSPressed) {
            m_zombiManager -> Die(true);
        }

        for (auto zombi : m_zombiManager -> GetZombies()) {
            if (zombi -> IfAnimationEnds()) {
                m_Root.RemoveChild(zombi);
            }
        }
        m_zombiManager -> CheckWall();


        m_KDown = isKPressed;
        m_zombiManager -> move();
    }



    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        m_zombiManager ->Getice(true);
    }


    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    MoveSun();
    CheckPlant();
    CheckBullet();
    if(m_PRM->GetLevel()>0)SunClock++;
    if(SunClock>480&&m_PRM->GetLevel()>0) {
        SunClock=0;
        MakeSun(false,{0,0});
    }

    if(m_holdingPlant!=nullptr){
        glm::vec2 pos=Util::Input::GetCursorPosition();
        m_holdingPlant->m_Transform.translation={pos.x,-pos.y};
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
    Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}


void App::End(){ // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
