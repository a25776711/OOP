//
// Created by bingho on 2025/3/11.
//

#include "Zombi/normal.hpp"

#include <iostream>
#include <ostream>

normal::normal(){
    MakeLoop();
}
normal::~normal() {};


int normal::Getreverse() {return reverse;}

void normal::MakeLoop() {
    m_ImagePaths.reserve(reverse);
    for (int i=0;i<reverse;i++) {

        m_ImagePaths.push_back(RESOURCE_DIR"/zombi/normal/walk/walk_"+std::to_string(i) +".png");
    }
    m_Drawable = std::make_shared<Util::Animation>(m_ImagePaths, true, 500, true, 0);
}

bool normal::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}
