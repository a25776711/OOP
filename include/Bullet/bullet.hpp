//
// Created by bingho on 2025/3/11.
//

#ifndef BULLET_HPP
#define BULLET_HPP
#include "Util/GameObject.hpp"
enum bullet_type {
    Normal,
    Ice
};

class Bullet:public Util::GameObject {
    public:
    Bullet(std::string path,bullet_type type) {
        m_ImagePath = path;
        m_Type = type;
    }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    glm::vec2 GetPosition() { return m_Transform.translation; }

    private:
    std::string m_ImagePath;
    bullet_type m_Type;
};

#endif //BULLET_HPP
