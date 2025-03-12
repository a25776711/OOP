//
// Created by bingho on 2025/3/11.
//

#ifndef PLANT_HPP
#define PLANT_HPP
#include "Util/GameObject.hpp"

class Plant: public Util::GameObject{
    public:
        int hp;
        int maxhp;
        Plant(hp,const const std::vector<std::string>& Path,int interval):GameObject() {
                m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, interval, false, 0);
        }
        ~Plant();
    private:
        std::string m_ImagePath;
        //位置
        int x,y;

};
#endif //PLANT_HPP
