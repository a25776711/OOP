//
// Created by bingho on 2025/3/14.
//
#include "Background/UpdateBackground.hpp"
#include "Util/Logger.hpp"

UpdateBackground::UpdateBackground() {
    m_Background = std::make_shared<BackgroundImage>();
}

void UpdateBackground::NextLevel() {

    //std::cout <<m_level<<std::endl;
    if (m_level == 6) return;
    m_Background -> NextLevel(m_level++);

}
