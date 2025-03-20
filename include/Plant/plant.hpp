//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"


class Plant: public Util::GameObject{
    public:

    Plant(std::vector<std::string>& Path,int interval,int atk):GameObject() {
        m_Drawable = std::make_shared<Util::Animation>(Path, false, interval, false, 0);
        m_ATK = atk;
        m_ImagePath=Path;
    }
    [[nodiscard]] bool GetVisibility() const { return m_Visible;}
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    virtual void Hurt(std::vector<std::shared_ptr<GameObject>>& collidedWith);

    protected:


    private:
    int m_ATK;
    std::vector<std::string> m_ImagePath;

};
#endif //PLANT_HPP