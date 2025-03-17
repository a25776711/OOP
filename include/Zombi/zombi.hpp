//
// Created by bingho on 2025/3/11.
//

#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class Zombi:public Util::GameObject {
public:
    Zombi(const std::vector<std::string>& Path,int interval):GameObject() {
        m_Drawable = std::make_shared<Util::Animation>(Path, false, interval, false, 0);
    }

    ~Zombi();
    [[nodiscard]] bool GetVisibility() const { return m_Visible;}
    [[nodiscard]]const std::string& GetImagePath() const { return m_ImagePath; }
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    void SetImage(const std::string& ImagePath);
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Zombi>& other) const {
        (void) other;
        return false;
    }

    void SetSpeed(int speed) {z_speed = speed;}
    int GetSpeed() { return z_speed;}

    void SetHP(int HP) {z_HP = HP;}
    int GetHP() { return z_HP;}

    void Setattack(int HP) {z_attack = HP;}
    int Getattack() { return z_attack;}

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }


private:
    std::string m_ImagePath;
    int z_speed;
    int z_HP;
    int z_attack;

};

#endif //ZOMBI_HPP
