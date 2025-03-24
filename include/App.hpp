#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp"
#include "Util/Renderer.hpp"
#include "Zombi/zombi.hpp"
#include "zombi/normal.hpp"
#include "Plant/plant.hpp"
#include "Background/UpdateBackground.hpp"
#include "Background/Adventure.hpp"
#include "Plant/PlantLoader.hpp"


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

private:
    //void ValidTask();

    State m_CurrentState = State::START;
    Phase m_Phase = Phase::tital;
    Util::Renderer m_Root;
    PlantLoader m_PlantLoader;
    std::shared_ptr<UpdateBackground> m_PRM;

    std::shared_ptr<normal> m_normal;

    bool m_EnterDown = false;

};

#endif
