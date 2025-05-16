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
enum T_WallnutType{
        Normal,
        Boom
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
        m_type=rand()%4==0?T_WallnutType::Boom:T_WallnutType::Normal;
        if(m_type==T_WallnutType::Boom){
            auto temp=std::make_shared<Util::Animation>(m_Loader.wallnutIMG_1,true,70,true,0);
        }
        m_rotationSpeed = -0.5f;  // 旋轉速度
        m_moveSpeed = 2.5f;      // 移動速度
    }

    bool Update(std::vector<std::shared_ptr<zombi>> zom);
    T_WallnutType GetType(){return m_type;}
    private:
    float m_rotationSpeed;    // 旋轉速度
    float m_moveSpeed;        // 移動速度
    T_WallnutMove m_moveState;
    T_WallnutType m_type;
};
class Play_wallnut_boom:public Plant{
    public:
    Play_wallnut_boom():Plant(m_Loader.wallnutIMG_Boom,70){
        SetHP(72);
        SetCost(50);
        SetType(T_Play_Wallnut);
        m_rotationSpeed = -0.5f;  // 旋轉速度
        m_moveSpeed = 2.5f;      // 移動速度
    }
    bool Update(std::vector<std::shared_ptr<zombi>> zom);
    private:
    float m_rotationSpeed;    // 旋轉速度
    float m_moveSpeed;        // 移動速度
    T_WallnutType m_type;
};
#endif //WALLNUT_HPP
