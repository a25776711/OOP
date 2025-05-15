//
// Created by bingho on 2025/3/11.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "plant.hpp"
#include "Zombi/zombi.hpp"
class Wallnut : public Plant {
    public:
    
    explicit  Wallnut():Plant(m_Loader.wallnutIMG,70) {
        SetHP(3600);
        SetCost(50);
        SetTakeCD(1800);
        SetType(T_WallNut);
    }
    void Hurt() override;
    private:

};
class Play_wallnut:public Plant{
    public:
    enum T_WallnutMove{
        Straight,
        Up,
        Down
    };
    Play_wallnut():Plant(m_Loader.wallnutIMG,70){
        SetHP(72);
        SetCost(50);
        SetType(T_Play_Wallnut);
        m_moveState = T_WallnutMove::Straight;
        m_rotationSpeed = 0.5f;  // 旋轉速度
        m_moveSpeed = 3.0f;      // 移動速度
    }

    bool Update(std::vector<std::shared_ptr<zombi>> zom);

    private:
    float m_rotationSpeed;    // 旋轉速度
    float m_moveSpeed;        // 移動速度
    T_WallnutMove m_moveState;
};
#endif //WALLNUT_HPP
