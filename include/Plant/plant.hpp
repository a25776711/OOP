//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Plant/PlantLoader.hpp"
#include "Bullet/bullet.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

class Plant: public Util::GameObject{
    public:
    enum PlantType {
      T_SunFlower,
        T_WallNut,
        T_Shooter,
        T_Mine,
        T_Bomb,
        T_Chomper
    };
    explicit Plant(std::vector<std::string>& Path,int interval){
        SetZIndex(5);
        m_Drawable = std::make_shared<Util::Animation>(Path, false, interval, true, 0);
        
    }
    [[nodiscard]] bool GetVisibility() const { return m_Visible;}
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }
    void SetHP(int hp=5) {
        m_hp=hp;
    }
    int GetHP(){return m_hp;}
    void SetATK(int atk) { m_ATK = atk;}
    int GetATK(){return m_ATK;}
    void PLAY(bool play);
    virtual void Hurt() {
        m_hp--;
    }
    void SetCost(int cost){m_cost=cost;}
    int GetCost(){return m_cost;}
    void SetType(PlantType type){m_Type=type;}
    PlantType GetType(){return m_Type;}
    void Play(){
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Play();
    }
    void SetTakeCD(int cd){m_takeCD=cd;}
    int GetTakeCD(){return m_takeCD;}
    virtual std::shared_ptr<Bullet> Attack(std::vector<glm::vec2> pos){return nullptr;};
    virtual void Boomer(){};
    virtual bool CoolDown(){return false;};
    bool IfAnimationEnds() const {
        if (!m_Drawable) {
            std::cerr << "[ERROR] m_Drawable is null." << std::endl;
            return false;
        }

        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        if (!temp) {
            std::cerr << "[ERROR] m_Drawable is not an Animation." << std::endl;
            return false;
        }
        return (temp->GetCurrentFrameIndex() == temp->GetFrameCount() - 1 );
    }
    protected:
    PlantLoader m_Loader;
    private:

    PlantType m_Type;
    int m_hp;
    int m_ATK=0;
    int m_cost;
    int m_takeCD;

};
#endif //PLANT_HPP