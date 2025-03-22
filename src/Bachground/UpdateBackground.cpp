//
// Created by bingho on 2025/3/14.
//
#include "Background/UpdateBackground.hpp"
#include "Util/Logger.hpp"
#include <iostream>
UpdateBackground::UpdateBackground() {
    m_Background = std::make_shared<BackgroundImage>();
    m_Adventure = std::make_shared<adventure>();
    m_Adventure -> SetPivot({-300,100});
    m_Adventure -> m_Transform.scale ={0.8,0.8};

}

void UpdateBackground::NextLevel() {
    if (m_level == 6) return;
    m_Background -> NextLevel(++m_level);
    m_Adventure -> NextLevel(m_level);
    if (m_level !=0) m_Adventure -> m_Transform.scale ={0.9,0.9};
    m_Adventure -> SetPivot({430,-280});
}
