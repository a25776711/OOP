//
// Created by bingho on 2025/3/11.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP
#include "plant.hpp"
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
class play_wallnut:public Plant{
    public:
    play_wallnut():Plant(m_Loader.wallnutIMG,70){
        SetHP(72);
        SetCost(50);
        SetType(T_Play_Wallnut);
        m_rotationSpeed = 5.0f;  // 旋轉速度
        m_moveSpeed = 2.0f;      // 移動速度
        m_isMoving = false;      // 是否正在移動
    }

    void StartMoving() {
        m_isMoving = true;
    }

    void Update() {
        if (m_isMoving) {
            // 更新位置
            glm::vec2 currentPos = GetPosition();
            currentPos.x += m_moveSpeed;
            SetPosition(currentPos);

            // 更新旋轉
            float currentRotation = m_Transform.rotation;
            currentRotation += m_rotationSpeed;
            m_Transform.rotation = currentRotation;
        }
    }

    private:
    float m_rotationSpeed;    // 旋轉速度
    float m_moveSpeed;        // 移動速度
    bool m_isMoving;         // 移動狀態
};
#endif //WALLNUT_HPP
