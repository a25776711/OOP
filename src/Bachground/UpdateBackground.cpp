//
// Created by bingho on 2025/3/14.
//
#include "Background/UpdateBackground.hpp"
#include "Util/Logger.hpp"
#include <iostream>
UpdateBackground::UpdateBackground() {
    m_Background = std::make_shared<BackgroundImage>();
    m_Adventure = std::make_shared<adventure>();
    m_Adventure -> SetPivot({100,100});
}

void UpdateBackground::NextLevel() {
    if (m_level == 6) return;
    m_Background -> NextLevel(m_level++);
    m_Adventure -> NextLevel(m_level++);
    m_Adventure -> SetPivot({350,-250});
    m_Adventure -> GetTransform().scale ={(m_Adventure -> GetTransform().scale.x)/2,(m_Adventure -> GetTransform().scale.y)/2};




}
