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
            
            if(m_CameraState==CameraState::idle){
                if(m_holdingPlant==nullptr&&CheckSunCollect(pos)){m_Root.RemoveChild(CheckSunCollect(pos));}
                if(m_holdingPlant!=nullptr){PutPlant(pos,m_PRM->GetLevel());}
                if(m_holdingPlant==nullptr){TakePlant(pos,m_PRM->GetLevel());}
            }
            else if(m_CameraState==CameraState::choose_card){
                TakePlant(pos,m_PRM->GetLevel());
            }
        }
        if (m_PRM ->GetLevel()==0) {
            if (m_PRM -> CheckHit(pos)) {
                m_PRM ->NextLevel();
                
                for (auto &z : m_PRM ->GetChildren()) {
                    m_Root.RemoveChild(z);
                }
                m_Root.AddChildren(m_PRM->GetChildren());
                m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
                m_Root.Update(glm::vec2(-100,0));
                ResetPlant(m_PRM -> GetLevel());
                m_PRM ->ResetCardPos();
                m_CameraState = CameraState::move_road;
            }
        }
    }
    if(m_C_Down && m_CameraState==CameraState::idle && m_PRM->GetLevel()!=0&&m_PRM->GetLevel()!=5){
        if(!Util::Input::IsKeyPressed(Util::Keycode::C)){
            auto cards=m_PRM->GetCards();
            for(auto& card:cards){
                if(!card->IfCreate()){
                    card->Reset();
                }
            }
        }
    }
    if (m_EnterDown&&m_CameraState==CameraState::idle&&m_PRM->GetLevel()!=0) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)){

            for (auto &z : m_PRM ->GetChildren()) {
                m_Root.RemoveChild(z);
            }
            m_PRM ->NextLevel();
            std::cout<<"next to level:"<<m_PRM->GetLevel()<<std::endl;
            m_CurrentZombiIndex = 0;
            zombicount = 0;
            for (auto zombi : m_zombiManager -> GetZombies()) {
                m_Root.RemoveChild(zombi);
            }
            m_Root.AddChildren(m_PRM-> GetChildren());

            m_Root.AddChildren(m_zombiManager->GetZombiesAsGameObjects(m_zombiManager ->GetZombi(m_PRM -> GetLevel())));
            if (m_PRM -> GetLevel() ==11){ m_CurrentState = State::END;}
            if(m_PRM->GetLevel()==1)m_Root.Update(glm::vec2(-100,0));

            ResetPlant(m_PRM -> GetLevel());
            m_CameraState = CameraState::move_road;

        }
    }

    if (m_PRM ->GetLevel() != 0 && m_CameraState==CameraState::idle) {

        if (m_ready -> IfAnimationEnds()) {m_Root.RemoveChild(m_ready);Checkready = true;}

        bool isKPressed = Util::Input::IsKeyPressed(Util::Keycode::K);

        if (!m_KDown && isKPressed) {
            // 按下K當下觸發一次
            // for(auto& z : m_zombiManager -> GetZombies()) {
            //     std::cout << z->GetPosition().x<<" "<<z->GetPosition().y << std::endl;
            // }
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

        for (auto zombi : m_zombiManager -> GetZombies()) {
            zombi -> HitCheck(m_Plants);
        }
        m_KDown = isKPressed;
        m_zombiManager -> move(m_Cars);
    }



    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        m_zombiManager ->Getice(true);
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);
    m_C_Down = Util::Input::IsKeyPressed(Util::Keycode::C);
    if(m_CameraState == CameraState::idle)PlantUpdate();






    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
    Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    GameObjectUpdate();
}


void App::End(){ // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}


