//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"


class Plant: public Util::GameObject{
    public:

    Plant(const std::vector<std::string>& Path,int interval):GameObject() {
        m_Drawable = std::make_shared<Util::Animation>(Path, false, interval, false, 0);
    }
    ~Plant();
    [[nodiscard]] bool GetVisibility() const { return m_Visible;}
    [[nodiscard]]const std::string& GetImagePath() const { return m_ImagePath; }
    [[nodiscard]] std::vector<int> GetPosition() const { return {x,y}; }

    private:
    std::string m_ImagePath;
    //位置
    int x,y;
};
#endif //PLANT_HPP