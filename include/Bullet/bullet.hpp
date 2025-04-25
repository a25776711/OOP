//
// Created by bingho on 2025/3/11.
//

#ifndef BULLET_HPP
#define BULLET_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

enum bullet_type {
    Normal,
    Ice
};

class Bullet:public Util::GameObject {
    public:
    explicit Bullet(std::string path,bullet_type type,glm::vec2 startPos,int damage = 1):GameObject(std::make_unique<Util::Image>(path), 10) {
        m_ImagePath = path;
        m_Type = type;
        m_Transform.translation = startPos;
        m_ZIndex=21;
        SetVisible(true);
        m_Damage=damage;
    }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    glm::vec2 GetPosition() { return m_Transform.translation; }
    bullet_type GetType() { return m_Type; }
    int GetDamage() { return m_Damage; }
    void Move() {
        m_Transform.translation.x += 4;
    }
    bool HitCheck(glm::vec2 pos) {
        if(pos.x>m_Transform.translation.x&&pos.x-m_Transform.translation.x<20&&abs(pos.y-m_Transform.translation.y)<30)return true;
        return false;
    }

    private:
    std::string m_ImagePath;
    bullet_type m_Type;
    int m_Damage;
};

#endif //BULLET_HPP
