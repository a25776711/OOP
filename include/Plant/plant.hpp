//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"


class Plant: public Util::GameObject{
    public:

    Plant(std::vector<std::string>& Path,int interval):GameObject() {
        m_Drawable = std::make_shared<Util::Animation>(Path, false, interval, false, 0);
    }
    ~Plant() {}
    [[nodiscard]] bool GetVisibility() const { return m_Visible;}
    [[nodiscard]]const std::string& GetImagePath() const { return m_ImagePath; }
    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    virtual void Hurt(std::vector<std::shared_ptr<GameObject>>& collidedWith);

    protected:
    int ATK;

    private:
    std::string m_ImagePath;

};
#endif //PLANT_HPP