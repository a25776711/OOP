#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp"
#include "Util/Renderer.hpp"
#include "Zombi/ZombiManager.hpp"
#include "Plant/plant.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/Adventure.hpp"
#include "Util/Logger.hpp"
#include "Background/SunNB.hpp"

// IWYU pragma: export



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
    enum PlantType {
        type_SunFlower,
        type_Pea,
        type_Wallnut,
        type_Mine,
        type_IcePea,
        type_FastPea,
        type_Chomper,
        type_Cherry
    };
    enum class Phase {
            tital,
            oneroad,
            threeroad,
            fiveroad
    };
    void MakeSun(bool flower,glm::vec2 pos) {
        auto temp=std::make_shared<Sun>(flower,pos);
        temp->SetZIndex(100);
        m_Suns.emplace_back(temp);
        m_Root.AddChild(m_Suns.back());
    }
    std::shared_ptr<Sun> CheckSun(glm::vec2 click);
    void MoveSun();
    void SetBlockPos();
    void ResetSetCarPos();
    void CarMoveCheck();
    //點擊四個點確認
    bool CheckClick(std::vector<float> block,glm::vec2 click);


    std::shared_ptr<zombi> CheckZombi();
    void TakePlant(glm::vec2 click,int level);
    void CheckPlant();
    void PutPlant(glm::vec2 click,int level);
    std::vector<std::shared_ptr<zombi>> CheckBullet();
    std::vector<glm::vec2> GetZomdiPos();

private:
    //void ValidTask();
    std::map<std::string,std::vector<std::vector<float>>> block;
    
    std::shared_ptr<Plant> m_holdingPlant=nullptr;
    State m_CurrentState = State::START;
    Phase m_Phase = Phase::tital;
    Util::Renderer m_Root;
    std::shared_ptr<UpdateBackground> m_PRM;

    int m_CurrentZombiIndex = 0;
    int zombicount = 0;
    std::shared_ptr<ZombiManager> m_zombiManager;

    int Sunamount=0;
    int SunClock=0;
    
    std::vector<std::shared_ptr<Sun>> m_Suns;
    std::vector<std::vector<std::shared_ptr<Plant>>> m_Plants;
    std::shared_ptr<SunNB> m_SunNB=std::make_shared<SunNB>();
    std::vector<std::shared_ptr<Bullet>> m_Bullets;
    std::vector<std::shared_ptr<Car>> m_Cars;

    bool m_EnterDown = false;
    bool m_KDown = false; // 初始設為 false


};

#endif
