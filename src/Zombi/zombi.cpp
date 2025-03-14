//
// Created by bingho on 2025/3/11.
//
#include "Zombi/zombi.hpp"

Zombi::Zombi(const std::vector<std::string>& AnimationPaths) {
    m_Drawable  = std::make_shared<Util::Animation>(AnimationPaths, false, 500, false, 0);
}

bool Zombi::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}