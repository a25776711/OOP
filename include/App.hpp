#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp"
#include "Renderer.hpp"
#include "Zombi/ZombiManager.hpp"
#include "Plant/plant.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/ready.hpp"
#include "Background/End.hpp"
#include "Background/Adventure.hpp"
#include "Util/Logger.hpp"
#include "Background/SunNB.hpp"
#include "Plant/PlantLoader.hpp"

// IWYU pragma: export

class App {
public:
    enum class State {
        START,
        UPDATE,
        Next,
        END,
    };
    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void Next();

    void End(); // NOLINT(readability-convert-member-functions-to-static)
    enum class CameraState {
        idle,
        grass,
        move_road,
        move_house,
        show_choose_card,
        choose_card,
        hide_choose_card
    };
    enum class Phase {
            tital,
            oneroad,
            threeroad,
            fiveroad
    };
    void MakeSun(bool flower,glm::vec2 pos={0,0});
    std::shared_ptr<Sun> CheckSunCollect(glm::vec2 click);

    void MoveSun();
    void SetBlockPos();
    void ResetSetCarPos(int level);
    void ResetPlant(int level);
    void CarMoveCheck();



    void PlantUpdate();
    void StartGameSet();
    void FpsShow();
    void GameObjectUpdate();
    void CameraMoveHidden(int hidden);

    //點擊四個點確認
    bool CheckClick(std::vector<float> block,glm::vec2 click);

    void TakePlant(glm::vec2 click,int level);
    void CheckPlant(std::vector<std::shared_ptr<zombi>> m_zombis,std::vector<glm::vec2> m_zombiPos);
    void PutPlant(glm::vec2 click,int level);
    void CheckBullet();
    std::vector<glm::vec2> GetZomdiPos();


private:
    //void ValidTask();
    std::map<std::string,std::vector<std::vector<float>>> block;

    std::shared_ptr<Plant> m_holdingPlant=nullptr;
    State m_CurrentState = State::START;
    Phase m_Phase = Phase::tital;
    CameraState m_CameraState = CameraState::idle;
    Renderer m_Root;
    std::shared_ptr<UpdateBackground> m_PRM;

    int m_CurrentZombiIndex = 0;

    int zombicount = 0;
    std::shared_ptr<ZombiManager> m_zombiManager;
    std::vector<std::shared_ptr<zombi>> m_zombis;
    std::vector<glm::vec2> m_zombiPos;

    int Sunamount=0;
    int SunClock=0;
    int road_count=0;
    int house_count=0;
    bool Checkready = false;

    std::shared_ptr<end> m_End = std::make_shared<end>();
    std::shared_ptr<Ready> m_ready = nullptr;


    std::vector<std::shared_ptr<Sun>> m_Suns;
    std::vector<std::vector<std::shared_ptr<Plant>>> m_Plants;
    std::shared_ptr<SunNB> m_SunNB=std::make_shared<SunNB>();
    std::vector<std::shared_ptr<Bullet>> m_Bullets;
    std::vector<std::shared_ptr<Car>> m_Cars;

    std::vector<std::shared_ptr<Plant>> m_Play_Wallnut;


    std::shared_ptr<Card> m_PlayCard=nullptr;

    bool move_house=false;
    bool move_road=false;
    bool m_EnterDown = false;
    bool m_C_Down = false;
    bool m_KDown = false; // 初始設為 false
};

#endif
