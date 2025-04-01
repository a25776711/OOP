//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"
#include "Plant/PlantLoader.hpp"
#include <ctime>
#include <cstdlib>

class Plant: public Util::GameObject{
    public:
    std::map<std::string,std::vector<glm::vec2>> block;
    explicit Plant(std::vector<std::string>& Path,int interval){
        m_Drawable = std::make_shared<Util::Animation>(Path, true, interval, true, 0);
    }
    [[nodiscard]] bool GetVisibility() const { return m_Visible;}
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    virtual void Hurt(std::vector<std::shared_ptr<GameObject>>& collidedWith);

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }
    void SetHP(int hp) {
        m_hp=m_maxhp=hp;
    }
    int GetHP(){return m_hp;}
    void SetATK(int atk) { m_ATK = atk;}
    void PLAY(bool play);
    virtual void Hurt() {
        m_hp--;
    }
    void SetBlock();
    protected:
    PlantLoader m_Loader;
    private:

    int m_hp;
    int m_maxhp;
    int m_ATK=0;

};
#endif //PLANT_HPP