#include "App.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/Adventure.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Core/Context.hpp"
#include <iostream>

using namespace Core;

void App::Start() {
    LOG_TRACE("Start");
    StartGameSet();
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    //FpsShow();

    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        pos.y=-pos.y;
        std::cout <<"("<< pos.x <<","<<pos.y<<")"<< std::endl;
    }
    if(Util::Input::IsKeyDown(Util::Keycode::J)) {
        Sunamount+=100;
        m_SunNB->Change(Sunamount);
    }

    if(Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        glm::vec2 pos=Util::Input::GetCursorPosition();
        pos.y=-pos.y;
        if(m_PRM->GetLevel()!=0){
            if(m_holdingPlant==nullptr&&CheckSunCollect(pos)){m_Root.RemoveChild(CheckSunCollect(pos));}
            if(m_holdingPlant==nullptr){TakePlant(pos,m_PRM->GetLevel()+1);}
            if(m_holdingPlant!=nullptr){PutPlant(pos,m_PRM->GetLevel());}
        }
        if (m_PRM ->GetLevel()==0) {
            if (m_PRM -> CheckHit(pos)) {
                m_PRM ->NextLevel();
                m_Root.AddChildren(m_PRM->GetChildren());
                m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
                ResetPlant(m_PRM -> GetLevel());
                m_CameraState = CameraState::grass;
                ResizeWindow(1100, 720);
            }
        }

    }
    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)){
            if(m_PRM->GetLevel()==0){
                ResizeWindow(1280, 720);
            }
            m_PRM ->NextLevel();
            m_CurrentZombiIndex = 0;
            zombicount = 0; 
            for (auto zombi : m_zombiManager -> GetZombies()) {
                m_Root.RemoveChild(zombi);
            }
            m_Root.AddChildren(m_PRM-> GetChildren());
            m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
            if (m_PRM -> GetLevel() ==11){ m_CurrentState = State::END;}
            ResetPlant(m_PRM -> GetLevel());
            m_CameraState = CameraState::grass;
        }
    }

    if (m_PRM ->GetLevel() != 0&&m_CameraState==CameraState::idle) {
        bool isKPressed = Util::Input::IsKeyPressed(Util::Keycode::K);

        if (!m_KDown && isKPressed) {
            // 按下K當下觸發一次
            for(auto& z : m_zombiManager -> GetZombies()) {
                std::cout << z->GetPosition().x<<" "<<z->GetPosition().y << std::endl;
            }
            if (m_CurrentZombiIndex < m_zombiManager->GetZombies().size()) {
                m_zombiManager->Startwalk(m_CurrentZombiIndex++);
            }
        }

        if (zombicount == 480) {
            int x = rand() % m_PRM -> GetLevel();
            if (m_CurrentZombiIndex + x < m_zombiManager->GetZombies().size()) {
                for (int i=0;i<x; i++){m_zombiManager->Startwalk(m_CurrentZombiIndex++);}
            }
            zombicount = 0;
        }
        else zombicount++;
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

        for (auto z : m_zombiManager -> GetZombies()) {
            for (auto plants : m_Plants) {
                for (auto plant : plants) {
                    if (plant) {
                        z -> HitCheck(plant);
                    }
                }
            }
        }
        m_KDown = isKPressed;
        m_zombiManager -> move(m_Cars);
    }



    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        m_zombiManager ->Getice(true);
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    if(m_CameraState == CameraState::idle)PlantUpdate();
    

    

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
    Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    CameraMove();
}


void App::End(){ // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}


