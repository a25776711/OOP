#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp"
#include "Util/Renderer.hpp"
#include "Zombi/zombi.hpp"
#include "zombi/normal.hpp"
#include "Plant/plant.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/Adventure.hpp"
#include "Plant/peashooter.hpp"
#include "Plant/sun.hpp"
#include "Util/Logger.hpp"
#include "Background/SunNB.hpp"

// IWYU pragma: export
inline std::vector<std::vector<int>> blockpos={
    {},
    {},
    {},
    {},
    {}};

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    enum class Phase {
            tital,
            oneroad,
            threeroad,
            fiveroad
    };
    void MakeSun(){m_Suns.emplace_back(std::make_shared<Sun>(false));m_Root.AddChild(m_Suns.back());}
    std::shared_ptr<Sun> CheckSun(glm::vec2 click) {
        for(auto& sun:m_Suns) {
            glm::vec2 pos = sun->GetPosition();
            std::cout << pos.x << ", " << pos.y << std::endl;
            LOG_INFO("CheckSun:pos:(x:{},y:{})", pos.x, pos.y);
            sun->CollectAndMove(click);
            if(sun->GetMoveState()==MoveOver)return sun;
        }
        return nullptr;
    }

    void MoveSun() {
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
private:
    //void ValidTask();
    int Sunamount=0;
    int SunClock=0;
    State m_CurrentState = State::START;
    Phase m_Phase = Phase::tital;
    Util::Renderer m_Root;
    std::shared_ptr<UpdateBackground> m_PRM;
    std::vector<std::shared_ptr<Sun>> m_Suns;
    std::vector<std::shared_ptr<Plant>> m_Plants;
    std::shared_ptr<SunNB> m_SunNB=std::make_shared<SunNB>();



    bool m_EnterDown = false;

};

#endif
