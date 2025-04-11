#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp"
#include "Util/Renderer.hpp"
#include "Zombi/ZombiManager.hpp"
#include "Plant/plant.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/Adventure.hpp"
#include "Plant/peashooter.hpp"
#include "Plant/sun.hpp"
#include "Util/Logger.hpp"
#include "Background/SunNB.hpp"
#include "Plant/sunflower.hpp"
#include "Plant/mine.hpp"
#include "Plant/cherrybomb.hpp"
#include "Plant/wallnut.hpp"
#include "Plant/chomper.hpp"
#include "Plant/iceshooter.hpp"
#include "Plant/fastshooter.hpp"
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
    void MakeSun(){m_Suns.emplace_back(std::make_shared<Sun>(false));m_Root.AddChild(m_Suns.back());}
    std::shared_ptr<Sun> CheckSun(glm::vec2 click);
    void MoveSun();
    void SetPos();
    std::shared_ptr<Plant> MakePlant(int i);
    //點擊四個點確認
    bool CheckClick(std::vector<glm::vec2> block,glm::vec2 click);
    float CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3);


    void CheckPlant(glm::vec2 click,int level);
    void PutPlant(glm::vec2 click);
private:
    //void ValidTask();
    std::map<std::string,std::vector<std::vector<glm::vec2>>> block;
    std::map<std::string,std::vector<glm::vec2>> m_cardPos;
    int Sunamount=0;
    int SunClock=0;
    std::shared_ptr<Plant> m_holdingPlant=nullptr;
    State m_CurrentState = State::START;
    Phase m_Phase = Phase::tital;
    Util::Renderer m_Root;
    std::shared_ptr<UpdateBackground> m_PRM;

    int m_CurrentZombiIndex = 0;
    std::shared_ptr<ZombiManager> m_zombiManager;

    std::vector<std::shared_ptr<Sun>> m_Suns;
    std::vector<std::vector<std::shared_ptr<Plant>>> m_Plants;
    std::shared_ptr<SunNB> m_SunNB=std::make_shared<SunNB>();

    bool m_EnterDown = false;
    bool m_KDown = false; // 初始設為 false

};

#endif
